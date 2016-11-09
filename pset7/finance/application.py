from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    
    #get user Iid
    user_id = session.get("user_id")
    
    total = 0.0
    
    # query database for user cach
    rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = user_id)
    cash = rows[0]["cash"]
    
    # query database for user shares   
    symbols = db.execute("SELECT symbol, sum_shares  FROM users_shares WHERE user_id = :user_id", user_id=user_id)
    
    # query data for esch symbol
    for symbol in symbols:
       symbolInfo = lookup(symbol["symbol"])
       if symbolInfo is None:
           symbol["name"] = "data is not available, try later"
           symbol["price"] = 0
       else:   
            symbol["name"] = symbolInfo["name"]
            symbol["price"] = symbolInfo["price"]
       symbol["total"] = symbol["price"] * symbol["sum_shares"]
       total += symbol["total"]
    
    total += cash
    
    return render_template("index.html", cash=cash, total=total, symbols = symbols)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        
        #get user Iid
        user_id = session.get("user_id")
        
        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol")

        # ensure shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide shares")
        
        # ensure stock exists
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("invalid shares")
        
        if shares <= 0:
            return apology("the number of shares must be positive")    
        
        # get symbol info
        symbolInfo = lookup(request.form.get("symbol"))
        
        # ensure symbol is correct
        if symbolInfo is None:
            return apology("invalid symbol")
           
        # query database for cach
        rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = user_id)
        cash = rows[0]["cash"]
        
        # do you have enough cash
        if (symbolInfo["price"] * shares) > cash :
            return apology("not enough money")

        # add transaction
        key = db.execute("INSERT INTO history (symbol, shares, user_id, price) VALUES (:symbol, :shares, :user_id, :price)", user_id = user_id, symbol = symbolInfo["symbol"], shares = shares, price = symbolInfo["price"])
        
        # chesk add transaction
        if key is None:
            return apology("Db error")
        
        key = db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash = cash - (symbolInfo["price"] * shares), user_id = user_id) 
        
        # TODO there is a bug if there is an error that free money for stock will not be charged
        
        # redirect user to index page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        symbols = db.execute("SELECT DISTINCT symbol FROM history")
        return render_template("buy.html", symbols = symbols)

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    
    #get user Iid
    user_id = session.get("user_id")
    
    # query database for user history   
    history = db.execute("SELECT symbol, date, price, abs(shares) AS shares, shares AS type_trans FROM history WHERE user_id = :user_id ORDER BY date", user_id=user_id)
    
    return render_template("history.html", history = history)
    
@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]
       
        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        
        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol")

        # get symbol info
        symbolInfo = lookup(request.form.get("symbol"))
        
        # ensure symbol is correct
        if symbolInfo is None:
            return apology("invalid symbol")

        # redirect user to index page
        return render_template("quoted.html", symbolInfo = symbolInfo)

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        symbols = db.execute("SELECT DISTINCT symbol FROM history")
        return render_template("quote.html", symbols = symbols)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    
    # forget any user_id
    session.clear()
    
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")
        
        # ensure confirm password was submitted
        elif not request.form.get("confirm_password"):
            return apology("confirm_password")    
        
        # ensure confirm password was submitted
        elif request.form.get("password") != request.form.get("confirm_password"):
            return apology("passwords do not match")    

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        
        # ensure username exists
        if len(rows) != 0 :
            return apology("username already exists")

        # add user
        key = db.execute("INSERT INTO users (username, hash, cash) VALUES (:username, :hash, :cash)", username = request.form.get("username"), hash = pwd_context.encrypt(request.form.get("password")), cash = 10000.00)
        
        # remember which user has logged in
        if key is None:
            return apology("Db error")
        
        # remember which user has logged in
        session["user_id"] = key
        
        # message for user    
        flash('You were successfully registred')
        
        # redirect user to login page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")
    

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        
        #get user Iid
        user_id = session.get("user_id")
        
        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol")

        # ensure shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide shares")
        
        # ensure stock exists
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("invalid shares")
        
        if   shares <= 0:
            return apology("the number of shares must be positive")
        
        # get symbol info
        symbolInfo = lookup(request.form.get("symbol"))
        
        # ensure symbol is correct
        if symbolInfo is None:
            return apology("invalid symbol")
           
        # TODO query database for shares
        rows = db.execute("SELECT sum_shares FROM users_shares WHERE user_id = :user_id AND symbol = :symbol", user_id = user_id, symbol = symbolInfo["symbol"])
        
        if not len(rows):
            return apology("you don't have such shares")
        
        if shares > rows[0]["sum_shares"]:
            return apology("you do not have such number of shares")
        
        # query database for cach
        rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session.get("user_id"))
        cash = rows[0]["cash"]
        
        # add transaction
        key = db.execute("INSERT INTO history (symbol, shares, user_id, price) VALUES (:symbol, :shares, :user_id, :price)", user_id = user_id, symbol = symbolInfo["symbol"], shares = -shares, price = symbolInfo["price"])
        
        # chesk add transaction
        if key is None:
            return apology("Db error")
        
        key = db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash = cash + (symbolInfo["price"] * shares), user_id = user_id) 
        
        # TODO there is a bug if there is an error that free money for stock will not be charged
        
        # redirect user to index page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        symbols = db.execute("SELECT DISTINCT symbol FROM history")
        return render_template("sell.html", symbols = symbols)

@app.route("/changePassword", methods=["GET", "POST"])
@login_required
def changePassword():
    """changePassword."""
    
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        #get user Iid
        user_id = session.get("user_id")
        
        # ensure username was submitted
        if not request.form.get("old_password"):
            return apology("must provide oldpassword")

        # ensure password was submitted
        elif not request.form.get("new_password"):
            return apology("must provide password")
        
        # ensure confirm password was submitted
        elif not request.form.get("confirm_password"):
            return apology("must confirm_password")    
        
        # ensure confirm password was submitted
        elif request.form.get("new_password") != request.form.get("confirm_password"):
            return apology("passwords do not match")    

        # query database for old passwopd
        rows = db.execute("SELECT hash FROM users WHERE id = :user_id", user_id = user_id)

        # ensure username exists and password is correct
        if not pwd_context.verify(request.form.get("old_password"), rows[0]["hash"]):
            return apology("invalid old password")
        
        
        # change Password
        key = db.execute("UPDATE users SET hash = :hash WHERE id = :user_id", hash = pwd_context.encrypt(request.form.get("new_password")), user_id = user_id)
        # remember which user has logged in
        
        if key is None:
            return apology("Db error")
        
        # message for user    
        flash('Password successfully change')
        
        # redirect user to login page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("changePassword.html")
