import mysql.connector
import csv
from db_conf import DB_CONFIG

conn = mysql.connector.connect(**DB_CONFIG)
cursor = conn.cursor(dictionary=True)
cursor.execute("SELECT timestamp, sensorvalue_a, sensorvalue_b, sensorvalue_c, sensorvalue_d FROM rawdata ORDER BY timestamp DESC")
data = cursor.fetchall()

with open("mysql_data.csv", "w", newline ="") as csvfile:
    fieldnames = ["timestamp", "sensorvalue_a","sensorvalue_b","sensorvalue_c","sensorvalue_d"]
    writer = csv.DictWriter(csvfile,fieldnames = fieldnames)
    
    writer.writeheader()
    writer.writerows(data)
    
cursor.close()
conn.close()

print("data fetched")
