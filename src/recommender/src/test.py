#!/usr/bin/python2.7

import psycopg2 as pg2
import pandas as pd
import datetime

# connect to database
try:
	conn = pg2.connect("dbname = 'coffeeebot_db'")
except:
	print "Unable to establish connection to database"

# set up cursor to db
cur = conn.cursor()

def printList(listP):
	for i in listP:
		print i + " ",

def recommendation(userID):
	# recommendation list
	recommendation = []

	# pull drink information
	drinks_df = pd.read_sql("SELECT * FROM drinks", conn)

	# check if customer has consumed a lot of caffeinated drink today
	cur.execute("SELECT EXISTS (SELECT 1 FROM trx WHERE userID = %s AND timestamp >= now()::date);", [userID])

	cameToday = cur.fetchall()
	cameToday = cameToday[0][0]

	cur.execute("SELECT EXISTS (SELECT 1 FROM trx WHERE userID = %s);", [userID])
	repeatCus = cur.fetchall()
	repeatCus = repeatCus[0][0]


	if repeatCus:
		df = pd.read_sql("SELECT drink, COUNT(drink) FROM trx WHERE (userID = %s) GROUP BY drink ORDER BY COUNT(drink) DESC;", conn, params = [userID])
		df = pd.merge(df, drinks_df, how = 'left', on = 'drink')

		# check whether customer has consumed high dose of caffeine
		if cameToday:
			df_today = pd.read_sql("SELECT drink, COUNT(drink) FROM trx WHERE (userID = %s AND timestamp >= now()::date) GROUP BY drink;", conn, params = [userID])
			df_today = pd.merge(df_today, drinks_df, how = 'left', on = 'drink')
			
			# recommend decaf drinks
			if df_today[df_today.caffeinated == True].sum()['count'] >= 3:
				decaf_drinks = drinks_df[drinks_df.caffeinated == False].drink
				recommendation.extend(decaf_drinks.tolist())
				df = df[~df.drink.isin(decaf_drinks)]
		
		# recommend drinks in order of consumption pattern
		recommendation.extend(df.drink.tolist())
		printList(recommendation)
	else:
		# suggest similar choices
		print "new user"

		


		
	




