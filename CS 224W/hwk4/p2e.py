import cPickle
import networkx as nx
from sets import Set
from random import *

#getting all shortest paths from root to all other nodes
def get_sigma(G, s, v, shortest):
  if s == v:
    return 1

  l = shortest[(s,v)]
  sigma_v = 0
  for u in G.neighbors(v):
    if shortest[(s,u)] < l:
      sigma_v += get_sigma(G, s, u, shortest)
  return sigma_v

def get_shortest_lens(G):
    shortest = {}
    for n1 in G:
        for n2 in G:
            t = (n1, n2)
            shortest[t] = nx.shortest_path_length(G, n1, n2)
    return shortest

def get_longest_shortest(G):
    l_s = {}
    for n in G:
        l_s[n] = nx.shortest_path_length(G, n)
    return l_s

def get_sigma_dict(G, shortest):
    dic1 = {}
    for n1 in G:
        dic2 = {}
        for n2 in G:
            dic2[n2] = get_sigma(G, n1, n2, shortest)
        dic1[n1] = dic2
    return dic1

def get_delta(G, s, e, sigmas, l_s, shortest):
  d_s1 = shortest[(s,e[0])]
  d_s2 = shortest[(s,e[1])]

  if d_s1 == d_s2:
      return 0
  if d_s1 == l_s[s]:
      return sigmas[e[1]]/float(sigmas[e[0]])
  if d_s2 == l_s[s]:
      return sigmas[e[0]]/float(sigmas[e[1]])

  if d_s1 < d_s2:
    v = e[1]
    w = e[0]
    lv = d_s2
  else:
    v = e[0]
    w = e[1]
    lv = d_s1

  sigma_sv = sigmas[v]
  sigma_sw = sigmas[w]
  summation = 0
  for n in G.neighbors(v):
      if shortest[(n,s)] > lv:
        summation += get_delta(G, s, (v, n), sigmas, l_s, shortest)
  return  sigma_sv/float(sigma_sw) *(1 + summation)

def btwn(G, v, w, node_sigmas, l_s, shortest):
    b = 0
    for node in G:
        b += get_delta(G, node, (v, w), node_sigmas[node], l_s, shortest)
    return b

def all_btwn(G, node_sigmas, l_s, shortest):
    B = []
    for e in G.edges():
        B.append(btwn(G, e[0], e[1], node_sigmas, l_s, shortest))
    return B

import __builtin__

G = nx.barabasi_albert_graph(1000, 4)
shortest = get_shortest_lens(G)
l_s = get_longest_shortest(G)
node_sigmas = get_sigma_dict(G, shortest)

B1 = all_btwn(G, node_sigmas, l_s, shortest)
cPickle.dump(B1, open('B1.pkl', 'wb'))
__builtin__.B1 = B1
__builtin__.G = G


def btwn2(G, v, w, c, k, node_sigmas, l_s, shortest):
    ran_nodes = sample(G.nodes(), k)
    b = 0
    n = len(G)
    for node in ran_nodes:
        if b < c*n:
            b += get_delta(G, node, (v, w), node_sigmas[node], l_s, shortest)
    return float(n)/k*b

def all_btwn2(G, c, k, node_sigmas, l_s, shortest):
    b = []
    for edge in G.edges():
        v = edge[0]
        w = edge[1]
        b.append(btwn2(G, v, w, c, k, node_sigmas, l_s, shortest))
    return b

c = 5
k = len(G.nodes())/10
B2 = all_btwn2(G, c, k, node_sigmas, l_s, shortest)
B2 = sorted(B2)
__builtin__.B2 = B2




