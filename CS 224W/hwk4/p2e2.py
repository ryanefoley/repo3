import cPickle
from random import *
import networkx as nx
from sets import Set

#G = nx.barabasi_albert_graph(4, 2)

#getting all shortest paths from root to all other nodes
def get_sigma(G, s, v, predecessors):
  if s == v:
    return 1

  l = nx.shortest_path_length(G,s,v)
  sigma_v = 0
  for u in G.neighbors(v):
    if nx.shortest_path_length(G,s,u) < l:
      predecessors.add(u)
      sigma_v += get_sigma(G, s, u, predecessors)
  return sigma_v

def get_delta(G, s, e, sigmas, successors):
  d_s1 = nx.shortest_path_length(G,s,e[0])
  d_s2 = nx.shortest_path_length(G,s,e[1])
  if d_s1 == d_s2: return 0
  elif d_s1 < d_s2:
    w = e[1]
    v = e[0]
  else:
    w = e[0]
    v = e[1]

  sigma_sv = sigmas[v]
  sigma_sw = sigmas[w]
  summation = sigma_sv/float(sigma_sw)

  if w in successors:
    for x in successors[w]:
      delta = get_delta(G, s, (w, x), sigmas, successors)
      summation += (sigma_sv/float(sigma_sw))*delta
  return summation

def get_successors(preds):
  succs = {}
  for n in preds:
    for otherN in preds[n]:
      if otherN not in succs:
        succs[otherN] = [n]
      else:
        succs[otherN].append(n)
  return succs

def approx_betweenness(G, c, m):
  n = len(G.nodes())
  deltas = {}
  big_delta = {}
  nodes = sample(G.nodes(), m)
  count = 1
  total = len(nodes)
  for s in nodes:

    print 'On node', count, 'of', total
    count +=1

    sigmas = {}
    delta_s = {}
    preds = {}
    #get sigmas of s for each v:
    for v in G.nodes():
      if nx.has_path(G, s, v):
        pred_set = Set()
        sigmas[v] = get_sigma(G, s, v, pred_set)
        preds[v] = pred_set
      else:
        sigmas[v] = 0
    #get successors for use in finding delta:
    successors = get_successors(preds)

    #get deltas of s for each edge in E:
    for e in G.edges():
      if e not in big_delta:
        big_delta[e] = 0
      if big_delta[e] < c*n:
        if nx.has_path(G, s, e[0]):
          big_delta[e] += get_delta(G, s, e, sigmas, successors)
  B = {}
  for e in big_delta:
    B[e] = big_delta[e] * n/float(m)
  return B

import __builtin__
#G = nx.barabasi_albert_graph(1000, 4)
m = len(G.nodes())/10
c = 5

B2 = approx_betweenness(G, c, m)
cPickle.dump(B2, open('B2.pkl', 'wb'))
__builtin__.B2 = B2






