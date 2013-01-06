import networkx as nx
from math import *
from random import *
from numpy.random import binomial
import cPickle
import matplotlib.pyplot as plt

hT = 10
b = 2
k = 5
N = int(pow(b, hT))
alphas = []
for i in range(1,101):
  alphas.append(i/10.0)

#Create mapping of keywords to their paths up to the root.
def get_node_paths(N, hT, b):
  node_paths = {}
  for node in range(N):
    node_paths[node] = []

  for d in range(hT):
    #Calculate the number of nodes under each parent
    n = int(pow(b, d + 1))
    for node in range(N):
      parent = node / n
      node_paths[node].append(parent)
  return node_paths

def h(n1, n2, node_paths):
  path1 = node_paths[n1]
  path2 = node_paths[n2]
  for i in range(len(path1)):
    if(path1[i] == path2[i]):
      return i + 1

def get_z(n1, N, b, alpha, node_paths):
  z = 0
  for n2 in range(N):
    if(n1 != n2):
      z += pow(b, -alpha * h(n1, n2, node_paths))
  return z

def prob_of_edge(n1, n2, b, alpha, z, node_paths):
  return pow(b, -alpha * h(n1,n2, node_paths)) / z

def get_graph(hT, b, k, alpha, N, node_paths):
  G = nx.DiGraph()
  print "Making graph with", N, "nodes..."
  for node in range(N):
    z = get_z(node, N, b, alpha, node_paths) #get z for normalizing prob now to avoid unnecessary computation
    G.add_node(node)
    print node-1, "nodes have had their edges added"
    num_edges = 0
    while(num_edges < k):
      #select random node
      otherNode = randint(0, N-1)
      if node != otherNode:
        #generate bernoulli trial  with probability p
        p = prob_of_edge(node, otherNode, b, alpha, z, node_paths)
        trial = binomial(1,p)
        if trial == 1: #success! create an edge!
          G.add_edge(node, otherNode)
          num_edges += 1
  return G

def get_graphs(alphas, hT, b, k, N):
  node_paths = get_node_paths(N, hT, b)
  graphs = []
  for alpha in alphas:
    G = get_graph(hT, b, k, alpha, N, node_paths)
    graphs.append(G)
  cPickle.dump(graphs, open("graphs.pkl", 'wb'))

#Function performs search and reports back 0 steps for failure or number of steps to success.
def decentralized_search(s,t, G, node_paths):
  steps = 0
  while(True):
    print 'S =', s
    print 'T =', t
    s_neighbors = G.neighbors(s)
    if t in s_neighbors: #know that s != t, but if t in s neighbors, then search succeeds in one step.
      steps +=1
      return steps

    #in nodes neighbors find next closest node.
    closest = s
    for u in s_neighbors:
      if h(u, t, node_paths) < h(closest,t, node_paths):
        #print "s=", s
        #print "closest=", closest
        #print "h(u,t) = ",  h(u, t, node_paths)
        #print "h(closest,t) = ",  h(closest, t, node_paths)
        closest = u

    if s == closest: #did not find a closer node so failed search.
      steps = 0
      return 0
    else: #found closer node so take step and continue search
      steps += 1
      s = closest

def test(graphs, alphas, node_paths):
  avg_steps_by_alpha = []
  prob_success_by_alpha = []
  #for each given alpha find avg number of steps and probability of success.
  for i in range(len(graphs)):
    print 'Working on graph', i, '...'
    G = graphs[i]
    alpha = alphas[i]
    steps_list = []
    iter = 0
    while(iter < 1000):
      print 'On iteration', iter,'for graph', i, '.'
      #pick two random nodes:
      s = randint(0, len(G.nodes())-1)
      t = randint(0, len(G.nodes())-1)
      if(s != t): #check nodes different, otherwise try again.
        iter += 1
        steps = decentralized_search(s,t, G, node_paths) #get search results from s to t
        if steps != 0: #success in search
          steps_list.append(steps)

    #get avg steps:
    if len(steps_list) != 0:
      avg_steps = sum(steps_list)/float(len(steps_list))
    else:
      avg_steps = 0
    avg_steps_by_alpha.append(avg_steps)

    #get probability of successful search
    p = len(steps_list) / float(1000)
    prob_success_by_alpha.append(p)

  cPickle.dump(avg_steps_by_alpha, open("avg_steps_by_alpha.pkl", 'wb'))
  cPickle.dump(prob_success_by_alpha, open("prob_success_by_alpha", "wb"))
  plt.plot(alphas, avg_steps_by_alpha, 'co')
  plt.savefig('avg_steps_by_alpha.png')
  plt.close()
  plt.plot(alphas, prob_success_by_alpha, 'mo')
  plt.savefig('prob_success_by_alpha.png')

print 'Getting graphs...'
node_paths = get_node_paths(N, hT, b)
graphs = cPickle.load(open('graphs.pkl', 'rb'))

print 'Testing...'
test(graphs, alphas, node_paths)


