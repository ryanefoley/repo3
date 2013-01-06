import cPickle
import networkx as nx
from sets import Set

G = nx.barabasi_albert_graph(4, 2)

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

def betweenness(G):
  deltas = {}
  B = {}
  n = len(G.nodes())
  count = 1
  for s in G.nodes():
    print 'On node', count, 'of', n
    count += 1
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
      if e not in B:
        B[e] = 0
      if nx.has_path(G, s, e[0]):
        B[e] += get_delta(G, s, e, sigmas, successors)

  return B

import __builtin__

G = nx.barabasi_albert_graph(1000, 4)
#G = nx.Graph()
#G.add_edges_from([(0,3), (3,2), (2,4), (4,1), (1,3), (3,4)])
B1 = betweenness(G)
cPickle.dump(B1, open('B1.pkl', 'wb'))
__builtin__.B1 = B1
__builtin__.G = G





