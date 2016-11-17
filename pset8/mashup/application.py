import os
import re
from flask import Flask, jsonify, render_template, request, url_for
from flask_jsglue import JSGlue
from random import shuffle, seed

from cs50 import SQL
from helpers import lookup

# configure application
app = Flask(__name__)
JSGlue(app)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///mashup.db")

@app.route("/")
def index():
    """Render map."""
    
    if not os.environ.get("API_KEY"):
        raise RuntimeError("API_KEY not set")
        
    return render_template("index.html", key=os.environ.get("API_KEY"))
    
@app.route("/articles")
def articles():
    """Look up articles for geo."""

    # validate parameters
    if not request.args.get("geo"):
        raise RuntimeError("missing geo")
        
    if not request.args.get("lang"):
        data = lookup(request.args.get("geo"))
    else:    
        data = lookup(request.args.get("geo"), request.args.get("lang"))
    
    if len(data) > 5:
        
        #choose five random news
        seed()
        shuffle(data)
        data = data[:5]
    
    return jsonify(data)

@app.route("/search")
def search():
    """Search for places that match query."""

    # validate parameters
    if not request.args.get("q"):
        raise RuntimeError("missing q")
        
    line = request.args.get("q")
    
    # get data from virtual table using full text searsh
    rows = db.execute("SELECT admin_name1, place_name, postal_code, latitude, longitude FROM vplaces WHERE vplaces MATCH :line LIMIT 10", line = line + '*')
    
    return jsonify(rows)
    
@app.route("/update")
def update():
    """Find up to 10 places within view."""
    
    # ensure parameters are present
    if not request.args.get("sw"):
        raise RuntimeError("missing sw")
    if not request.args.get("ne"):
        raise RuntimeError("missing ne")
    if not request.args.get("centr"):
        raise RuntimeError("missing centr")   

    # ensure parameters are in lat,lng format
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("sw")):
        raise RuntimeError("invalid sw")
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("ne")):
        raise RuntimeError("invalid ne")
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("centr")):
        raise RuntimeError("invalid centr")    

    # explode southwest corner into two variables
    (sw_lat, sw_lng) = [float(s) for s in request.args.get("sw").split(",")]

    # explode northeast corner into two variables
    (ne_lat, ne_lng) = [float(s) for s in request.args.get("ne").split(",")]
    
    # explode centr into two variables
    (centr_lat, centr_lng) = [float(s) for s in request.args.get("centr").split(",")]
    
    centr_rows = db.execute("""SELECT * FROM places
            WHERE ((:centr_lat - 0.001 < latitude) AND (:centr_lat + 0.001 > latitude)) AND ((:centr_lng - 0.001 < longitude) AND (:centr_lng + 0.001 > longitude))
            GROUP BY country_code, place_name, admin_code1""",
            centr_lat=centr_lat, centr_lng=centr_lng)
    
    if not len(centr_rows):
        centr_rows = [{"postal_code":""}]

    # find 10 cities within view, pseudorandomly chosen if more within view
    if (sw_lng <= ne_lng):

        # doesn't cross the antimeridian
        rows = db.execute("""SELECT * FROM places
            WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude AND longitude <= :ne_lng) AND (:index != postal_code) AND ( place_name != 'H++') 
            GROUP BY country_code, place_name, admin_code1
            ORDER BY RANDOM()
            LIMIT 10""",
            sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng, index=centr_rows[0]["postal_code"])

    else:

        # crosses the antimeridian
        rows = db.execute("""SELECT * FROM places
            WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude OR longitude <= :ne_lng) AND (:index != postal_code) AND ( place_name != 'H++')
            GROUP BY country_code, place_name, admin_code1
            ORDER BY RANDOM()
            LIMIT 10""",
            sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng, index=centr_rows[0]["postal_code"])

    # output places as JSON
    #return jsonify(rows + centr_rows)
    if centr_rows[0]["postal_code"] == "":
        return jsonify(rows)
    else:    
        return jsonify(rows + centr_rows)