import requests
import csv

url = "http://172.20.241.35/get_data.php"
response = requests.get(url)
data = response.json()


for row in data:
    print(
        row["timestamp"],
        row["sensorvalue_a"],
        row["sensorvalue_b"],
        row["sensorvalue_c"],
        row["sensorvalue_d"]
    )

with open("php_data.csv", "w", newline = "") as csvfile:
    fieldnames = ["timestamp","sensorvalue_a","sensorvalue_b","sensorvalue_c","sensorvalue_d"]
    writer = csv.DictWriter(csvfile,fieldnames = fieldnames)
    
    writer.writeheader()
    writer.writerows(data)
    
    
