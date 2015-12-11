import psycopg2
import pandas as pd
import datetime

# connect to database
try:
	conn = psycopg2.connect("dbname = 'coffeeebot_db'")
except:
	print "Unable to establish connection to database"

# set up cursor to db
cur = conn.cursor()

def writeTrx(userID, drink):
	sql_query = "INSERT INTO trx (userID, drink) VALUES (" + str(userID) + ", " + drink + ");"
	cur.execute(sql_query)
