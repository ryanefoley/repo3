import networkx as nx

def get_e(neighbors, G):
  e = 0
  for neighbor in neighbors:
    for other in neighbors:
      if(neighbor != other and (neighbor, other) in G.edges()):
        e += 1
  return e

def c_coef(node, G):
  k = G.degree(node)
  if(k  > 1):
    neighbors = G.neighbors(node)
    e = get_e(neighbors, G)
    c = (2*e)/float(k*(k-1))
    return c
  else:
    return "Nan"

graphs = [rw]

print "Getting averages..."
for g in graphs:
  c_list = []
  for node in g.nodes():
    c = c_coef(node, g)
    if(c != "Nan"):
      c_list.append(c)
  avg = sum(c_list)/float(len(c_list))
  print avg

