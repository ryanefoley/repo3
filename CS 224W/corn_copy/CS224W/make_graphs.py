import networkx as nx
from random import *


#Problem 1a
n = 5242
m = 14496

#Gnm Graph
print "Creating Gnm Graph..."
gnm = nx.gnm_random_graph(n, m)

#Small world graph
def small_world():
  print "Creating small world..."
  sw = nx.Graph()
  #create ring
  for i in range(n):
      if(i == n-1):
          sw.add_edge(i, 0)
          sw.add_edge(i, 1)
      else:
          if(i == n-2):
              sw.add_edge(i, i+1)
              sw.add_edge(i, 0)
          else:
              sw.add_edge(i, i+2)
              sw.add_edge(i, i+1)

  iters = 4012
  iter = 0
  while(iter < iters):
      n1 = randint(0, n-1)
      n2 = randint(0, n-1)
      if(n1 != n2 and (n1,n2) not in sw.edges() and (n2,n1) not in sw.edges()):
          sw.add_edge(n1,n2)
          iter += 1
  return sw

sw = small_world()

#Real-World Collaboration Network
print "Reading Real-World graph..."
rw = nx.read_adjlist("ca-GrQc.txt")
