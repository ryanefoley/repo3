import networkx as nx
from sets import Set
from Queue import *
import cPickle

G = nx.read_adjlist('email_network.txt', create_using=nx.DiGraph())

scc = nx.strongly_connected_components(G)

print len(scc[0])

biggest_scc = scc[0]

nodes_out = Set()
nodes_q = Queue()
#Initialize queue:
for node in biggest_scc:
  nodes_q.put(node)

#Find nodes out of queue.
nodes_out = Set()
while(nodes_q.qsize() != 0):
  print "Queue size =", nodes_q.qsize()
  node = nodes_q.get()
  neighbors = G.neighbors(node)
  for neighbor in neighbors:
    if neighbor not in biggest_scc and neighbor not in nodes_out:
      nodes_out.add(neighbor)
      nodes_q.put(neighbor)

print "Nodes out size:", len(nodes_out)

cPickle.dump(nodes_out, open('nodes_out.pkl', 'wb'))
