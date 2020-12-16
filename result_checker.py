'''
Usage: read the file and check whether there is a cycle
Note: input file should be in the same format as the input file in PA3
Command: python3 result_checker.py [file]

For example:
python3 result_checker.py inputs/1.in
'''
import sys
import networkx as nx

thefile = sys.argv[1]
data = []
graph = []

f = open(thefile, "r")
directed = f.readline()
directed = False if directed == 'u' else True
trash = f.readline()
edges = f.readline()
for i in range(int(edges)):
    aline = f.readline().strip().split()
    data.append([int(i) for i in aline])
    graph.append((data[i][0], data[i][1]))
    if directed == False:
        graph.append((data[i][1], data[i][0]))

G = nx.Graph(graph)

try:
    has_cycle = nx.find_cycle(G)
    print("Cycle:")
    print(has_cycle)
except:
    print("No cycle!")



