from iexfinance.stocks import Stock
import csv

# tsla = Stock('TSLA')
# tsla.get_price()

class Stocks:
    def __init__(self, ticker, number, buyPrice, spotPrice):
        self.ticker = ticker
        self.number = number
        self.buyPrice = buyPrice
        self.spotPrice = spotPrice

class User:
    def __init__(self, username, password, balance):
        self.username = username
        self.password = password
        self.balance = balance
        self.userStocks = []

with open('users.txt') as csvfile:
    allUsers = []
    readCSV = csv.reader(csvfile,delimiter=",")
    for row in readCSV:
        username = row[0]
        password = row[1]
        balance = row[2]
        tempUser = User(username, password, balance)
        allUsers.append(tempUser)
        sizeOfList = len(row)
        incrementer = 3
        while incrementer < sizeOfList:
            ticker = row[incrementer]
            number = row[incrementer+1]
            buyPrice = row[incrementer+2]
            spotPrice = row[incrementer+3]
            tempStock = Stocks(ticker, number, buyPrice, spotPrice)
            tempUser.userStocks.append(tempStock)
            incrementer += 4

for x in allUsers:
    numStocks = len(x.userStocks)
    for i in range(numStocks):
        tempStock = Stock(x.userStocks[i].ticker)
        x.userStocks[i].spotPrice = tempStock.get_price()

with open('users.txt', mode='w', newline='') as tempFile:
    temp_writer = csv.writer(tempFile, delimiter=',')
    for x in allUsers:
        rowString = []
        rowString.append(x.username)
        rowString.append(x.password)
        numStocks = len(x.userStocks)
        if (numStocks > 0):
            rowString.append(x.balance)
        else:
            rowString.append(x.balance)

        for i in range(numStocks):
            rowString.append(x.userStocks[i].ticker)
            rowString.append(x.userStocks[i].number)
            rowString.append(x.userStocks[i].buyPrice)
            if (i != numStocks):
                rowString.append(str(x.userStocks[i].spotPrice))
            else:
                rowString.append(x.userStocks[i].spotPrice)
        print (rowString)
        temp_writer.writerow(rowString)
