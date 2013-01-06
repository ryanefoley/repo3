import __builtin__
import networkx as nx
from random import *

#Gnm Graph
n = 10670
m = 22002

print "Creating Gnm Graph..."
gnm = nx.gnm_random_graph(n, m)
print len(gnm.nodes())
print len(gnm.edges())


#Real World Autonomous System Network
print "Reading Real-World graph..."
rw = nx.read_adjlist("oregon1_010331.txt.gz")
print len(rw.nodes())
print len(rw.edges())

#Graph with preferential attachment
print 'Creating preferential attachment graph...'
pag = nx.complete_graph(40)

new_node = 40 #labeling for first node to be added
num_edges = len(pag.edges())
edges = pag.edges()
while(len(pag.nodes())< 10670):
  if len(pag.nodes()) % 100 == 0: print len(pag.nodes())
  for i in range(2): #creating two new edges
    #get random edge from graph
    rand_edge = edges[randint(0, len(edges)-1)]

    #get random endpoint from the selected edge
    node = rand_edge[randint(0,1)]

    #make edge between node and endpoint
    pag.add_edge(new_node, node)
    edges += [(new_node, node)]
  new_node += 1

print len(pag.nodes())
print len(pag.edges())

__builtin__.gnm = gnm
__builtin__.rw = rw
__builtin__.pag = pag
