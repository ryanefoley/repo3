def excess_degree(G):
  V = G.nodes()
  E = G.edges()
  degree_sequence=sorted(nx.degree(G).values(),reverse=True)
  dmax=max(degree_sequence)
  q = []
  for k in range(dmax):
    for node in V:
      neighbors = G.neighbors(node)
      for neighbor in neighbors:
        if(neighbor.degree() > k):
          q[k] += 1

  return q
