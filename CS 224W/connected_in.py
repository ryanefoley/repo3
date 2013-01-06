import networkx as nx
from sets import Set
from Queue import *

G = nx.read_adjlist('email_network.txt', create_using=nx.DiGraph())

scc = nx.strongly_connected_components(G)

print len(scc[0])

biggest_scc = scc[0]

def is_node_connected(node, scc):
  if node in scc:
    return True
  else:
    for neighbor in G.neighbors(node):
      if is_node_connected(neighbor, scc):
        return True
    return False

count = 0
for node in G.nodes():
  if count % 10 == 0:
    print count, 'connected nodes found.'
  if node not in biggest_scc:
    if is_node_connected(node, biggest_scc):
      count += 1

print count, 'connected nodes.'


