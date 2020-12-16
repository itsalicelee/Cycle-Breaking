'''
This file should not be put in any folders!! 

Usage: generate random sample to the directory ./inputs
File name will be: test_[edgeNum]
can customize undirected/directed, vertex, edge

Command:
python3 gen_sample.py
'''


import random
import networkx as nx
directed = False  # can be modified
vertex = 100  # can be modified
edge = 1000  # can be modified

filename = "./inputs/test_" + str(edge) + ".in"
f = open(filename, "w")

f.write('u\n')  if directed == False else f.write('d\n') 

f.write(str(vertex)+'\n')
f.write(str(edge)+'\n')
cnt = 0
edges = []
aline = []

while cnt < edge:
    start = random.randint(0,vertex)
    end = random.randint(0,vertex)
    weight = random.randint(-100,100)
    if start != end:
        f.write(str(start) + " " + str(end) +  " " + str(weight) + "\n")
        cnt += 1
        edges.append((start,end))

if directed == False:
    G = nx.Graph(edges)
else:
    G = nx.diGraph(edges)


has_cycle = nx.find_cycle(G)
if has_cycle != []:
    f.write("Cycle:\n")
    f.write(str(has_cycle))
else:
    f.write("No cycle!")
f.close()


