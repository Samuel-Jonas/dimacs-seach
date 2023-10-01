import os
import ctypes

class Node(ctypes.Structure):
    _fields_ = [("identifier", ctypes.c_int), ("prox", ctypes.POINTER(Node))]

class Graph(ctypes.Structure):
    _fields_ = [("num_edges", ctypes.c_int), ("adj_lists", ctypes.POINTER(ctypes.POINTER(Node)))]

bfs_module = ctypes.CDLL('./bfs.so')

# Define the argument types and the return type
bfs_module.create_graph.argtypes = [ctypes.c_int]
bfs_module.create_graph.restype = ctypes.c_int

bfs_module.add_edge.argtypes = [ctypes.Structure, ctypes.c_int, ctypes.c_int]

def find_directory(folder, file_name):
    dir = os.path.dirname(os.path.abspath(__file__))
    file_path = os.path.join(dir, folder, file_name)

    return file_path

file_path_distance = find_directory('base', 'USA-road-d.NY.gr.txt')

print(file_path_distance)

#with open(file_path_distance, 'r') as file:
#   lines = file.readlines()

#for line in lines:
#    print(line.strip())