import networkx as nx
from sets import Set
import cPickle

G = nx.read_adjlist('email_network.txt', create_using=nx.DiGraph())
scc = nx.strongly_connected_components(G)
b_scc = scc[0]

nodes_in = Set()
for node in G.nodes():
  if len(nodes_in) % 10 == 0: print len(nodes_in), "InNodes Found"
  if node not in nodes_in and node not in b_scc:
    for other in b_scc:
      try:
        path = nx.shortest_path(G,node, other)
        if len(path) > 0:
          nodes_in.add(node)
          break
      except:
        place_holder = 0

print "Nodes in =", len(nodes_in)

cPickle.dump(nodes_in, open("nodes_in.pkl", 'wb'))
