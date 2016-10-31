VALUES_OF_COINS = (25,10,5,1)#set of nominals
amountInCents = 0
coins = 0
while True:  
    while amountInCents<1:
        try:
            summa = input("hai! How much change is owed?: ")
            summa = float (summa)
            amountInCents = int(round(summa*100))
        except ValueError:
            pass
    break

for valueOfCoins in VALUES_OF_COINS:
    while amountInCents >= valueOfCoins:
        amountInCents -= valueOfCoins
        coins += 1
print(coins)

    
   
