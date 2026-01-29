import socket
import csv

HOST = "172.20.241.9"  # The server's hostname or IP address
PORT = 20000  # The port used by the server

s= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.sendall(b'15\n')

chunks = []
while True:
    data = s.recv(1024)
    if len(data) == 0:
        break
    chunks.append(data.decode('utf-8'))
    
for i in chunks:
    print(i, end = '')

s.close()

data_text = "".join(chunks)

rows = data_text.strip().split("\n")

with open("socket_data.csv", "w", newline="") as csvfile:
    writer = csv.writer(csvfile)
    
    for r in rows:
        cols = r.split(",")
        writer.writerow(cols)
        