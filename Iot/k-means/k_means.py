import numpy as np 
import matplotlib.pyplot as plt
import csv
import pandas as pd
from mpl_toolkits.mplot3d import Axes3D

mysql_data = pd.read_csv("mysql_data.csv")
data = mysql_data[["sensorvalue_a","sensorvalue_b","sensorvalue_c"]].to_numpy()

k = 6 #klusterien määrä
max_iters = 20

def init_centroids(data,k):
    indeksit = np.random.choice(len(data), k,replace=False)
    keskipisteet = data[indeksit]
    
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(keskipisteet[:,0],keskipisteet[:,1],keskipisteet[:,2], c = 'red', marker ='X', label ='keskipisteet')
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Z")
    ax.set_title("Random keskipisteet")
    ax.legend()
    plt.show()
    return keskipisteet


def count_distances(data,centroids):
    distance = np.linalg.norm(data[:,np.newaxis] - centroids, axis =2)
    return distance

  
def assign_clusters(data,centroids):
    distance = count_distances(data,centroids)
    nearest = np.argmin(distance,axis=1)
    return nearest


def update_centroids(data,labels,k):
    new_centroids = np.zeros((k,data.shape[1]))
    
    for i in range(k):
        cluster_points = data[labels == i]
        if len(cluster_points) > 0:
            new_centroids[i] = np.mean(cluster_points,axis=0)
        else:
            new_centroids[i] = data[np.random.choice(len(data))]
    return new_centroids


def k_means(data, k, max_iters=100):
    centroids = init_centroids(data,k)
    
    for iterations in range(max_iters):
        labels = assign_clusters(data,centroids)
        new_centroids = update_centroids(data,labels,k)
        
        if np.allclose(centroids,new_centroids):
            print(f"K-means konvergenssi {iterations+1} iteraatiossa")
            break
        centroids = new_centroids
        print(centroids)
        
    centroids_df = pd.DataFrame(centroids, columns=["x", "y", "z"])
    centroids_df.to_csv("centroids.csv", index=False)    
    return labels, centroids

labels, centroids = k_means(data,k) #ajellaan tosta
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.scatter(data[:,0],data[:,1],data[:,2], c = labels, cmap='viridis',s=40)
ax.scatter(centroids[:,0],centroids[:,1],centroids[:,2],c='red',s=120, marker= 'x')
ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")
plt.show()