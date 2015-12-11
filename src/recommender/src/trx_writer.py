#!/usr/bin/python2.7
# for stage 0 - push trx record to database

import rospy
from std_msgs.msg import String
import psycopg2

# connect to database
try:
	conn = psycopg2.connect("dbname = 'coffeeebot_db'")
	print "Connected to DB"
except:
	print "Unable to establish connection to database"

# set up cursor
cur = conn.cursor()

# find max userID (for stage 0 only)
cur.execute("SELECT MAX(userID) FROM trx;")
currentID = cur.fetchall()
currentID = currentID[0][0]


# subscriber
def callback(data):
	global currentID
	currentID += 1
	cur.execute("INSERT INTO trx (userID, drink) VALUES (%s, %s);", [currentID, data.data])
	conn.commit()
	#print "commited"
	
    
def listener():
	rospy.init_node('listener', anonymous = True)
	rospy.Subscriber("coffee", String, callback)
	rospy.spin()

if __name__ == '__main__':
	listener()



