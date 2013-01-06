import copy
import networkx as nx
from random import *
import matplotlib.pyplot as plt

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

def get_diameter(nodes, G):
  max_shortest_path = None
  for node in nodes:
    for otherNode in G.nodes():
      if nx.has_path(G, node, otherNode):
        path = nx.shortest_path(G, node, otherNode)
        if max_shortest_path == None:
          max_shortest_path = len(path) - 1
        elif max_shortest_path < len(path)-1:
          max_shortest_path = len(path)-1
  return max_shortest_path

def get_rand_nodes(G):
  rand_nodes = []
  g_nodes = G.nodes()
  shuffle(g_nodes)
  i = 0
  while(len(rand_nodes) < 20):
    new_node = g_nodes[i]
    if new_node not in rand_nodes:
      rand_nodes += [new_node]
    i += 1
  return rand_nodes

def failure(G, x):
  g_nodes = G.nodes()
  deleted = []
  while(len(deleted) < x):
    node = g_nodes[randint(0, len(g_nodes)-1)]
    if node not in deleted:
      deleted.append(node)
  G.remove_nodes_from(deleted)
  return G

def degrees_to_nodes(G):
  ds_nodes = {}
  for node in G.nodes():
    d = G.degree(node)
    if d not in ds_nodes:
      ds_nodes[d] = []
      ds_nodes[d] += [node]
    else:
      ds_nodes[d] += [node]
  return ds_nodes

def attack(G, x):
  d_to_n = degrees_to_nodes(G)
  degrees = sorted(d_to_n.keys(), reverse = True)
  deleted = []
  while(len(deleted) < x):
    max_d = degrees[0]
    for node in d_to_n[max_d]:
      if len(deleted) == x: break
      deleted.append(node)
    degrees.remove(max_d)
  G.remove_nodes_from(deleted)
  return G

def get_reduced_graph(G, type, x, y):
  if type == 'failure':
    original_size = len(G.nodes())
    while len(G.nodes()) > original_size*(1-(y/100.0)):
      print 'Graph size is', len(G.nodes()), 'and going to', original_size*(1-(y/100.0))
      G = failure(G, x)
  else:
    original_size = len(G.nodes())
    while len(G.nodes()) > original_size*(1-(y/100.0)):
      print 'Graph size is', len(G.nodes()), 'and going to', original_size*(1-(y/100.0))
      G = attack(G, x)
  return G

#For each graph reduce for each type of attack - gnm,d rw, pag
graphs = [gnm, rw, pag]
types = ['failure', 'attack']

i = 0
x = 10670/100
y = 50
for t in types:
  for g in graphs:
    print 'Working...'
    x_vals = []
    y_vals = []
    print 'Getting copy...'
    g = copy.deepcopy(g)
    original_size = len(g.nodes())
    print 'Getting rand nodes...'
    rand_nodes = get_rand_nodes(g)
    print 'Getting diameter...'
    d = get_diameter(rand_nodes, g)
    print d
    x_vals += [0]
    y_vals += [d]

    while len(g.nodes()) > original_size*(1-(y/100.0)):
      print len(g.nodes())
      if t == 'failure':
        g = failure(g, x)
      else:
        g = attack(g, x)
      rand_nodes = get_rand_nodes(g)
      d = get_diameter(rand_nodes, g)
      print d
      x_vals += [1 - len(g.nodes())/float(original_size)]
      y_vals += [d]

    plt.plot(x_vals, y_vals, 'ro')
    plt.ylabel('Approx. Diameter')
    plt.xlabel('Proportion of Nodes Removed')
    plt.savefig("prob4_"+str(i)+".png")
    plt.close()
    i += 1

x = 10670/1000
y = 2
for t in types:
  for g in graphs:
    x_vals = []
    y_vals = []
    g = copy.deepcopy(g)
    original_size = len(g.nodes())
    rand_nodes = get_rand_nodes(g)
    d = get_diameter(rand_nodes, g)
    print d
    x_vals += [0]
    y_vals += [d]

    while len(g.nodes()) > original_size*(1-(y/100.0)):
      print len(g.nodes())
      if t == 'failure':
        g = failure(g, x)
      else:
        g = attack(g, x)
      rand_nodes = get_rand_nodes(g)
      d = get_diameter(rand_nodes, g)
      print d
      x_vals += [1 - len(g.nodes())/float(original_size)]
      y_vals += [d]

    plt.plot(x_vals, y_vals, 'ro')
    plt.savefig("prob4_"+str(i)+".png")
    plt.close()
    i += 1
