import networkx as nx

def get_q(G):
  V = G.nodes()
  E = G.edges()
  degree_sequence=sorted(nx.degree(G).values(),reverse=True)
  dmax = max(degree_sequence)
  q_prime = {}
  for k in range(dmax + 1):
    for node in V:
      neighbors = G.neighbors(node)
      for neighbor in neighbors:
        if(G.degree(neighbor) == k + 1 ):
          if(k in q_prime):
            q_prime[k] += 1
          else: q_prime[k] = 1

  q = {}
  for k in q_prime:
    q[k] = (q_prime[k] / float(sum(q_prime.values())))
  return q

def get_p(G):
  V = G.nodes()
  E = G.edges()
  degree_sequence=nx.degree(G).values()
  degree_counts = {}
  for degree in degree_sequence:
    if(degree in degree_counts):
      degree_counts[degree] += 1
    else:
      degree_counts[degree] = 1

  p = {}
  for degree in degree_counts:
    p[degree] = degree_counts[degree]/float(sum(degree_counts.values()))

  return p

def exp_excess_degree(q):
  exp_deg = 0
  for k in q:
    exp_deg += k * q[k]
  return exp_deg

def exp_degree(p):
  exp_deg = 0
  for k in p:
    exp_deg += k*p[k]
  return exp_deg
