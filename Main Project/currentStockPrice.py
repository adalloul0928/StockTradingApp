from iexfinance.stocks import Stock
import sys
import csv

myStock = str(sys.argv[1])

tempStock = Stock(myStock)
# print(tempStock.get_price())

with open('tempFile.txt', mode='w', newline='') as tempFile:
    temp_writer = csv.writer(tempFile)
    temp_writer.writerow([tempStock.get_price()])
