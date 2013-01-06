import networkx as nx
from random import *
from sets import Set

def get_graph():
  G = nx.complete_graph(10)

  for edge in G.edges():
    sign = randint(0,1) #get random edge label indicating negative - 0 - or positive - 1.
    G.add_edge(edge[0], edge[1], label = sign)
  return G

def get_triangle(G):
  edges = G.edges()

  #Get first edge
  edge1 = edges[randint(0, len(edges) - 1)]

  #Get other two edges of triangle
  while(True):
    n = randint(0, len(G.nodes()) - 1)
    if n != edge1[0] and n != edge1[1]: break

  edge2 = tuple([edge1[0], n])
  edge3 = tuple([edge1[1], n])

  triangle = [edge1, edge2, edge3]
  return triangle

def dyna_proc(G, triangle):
  #Counting number of negative edges
  num_neg = 0
  for edge in triangle:
    data = G.get_edge_data(edge[0], edge[1])
    if data['label'] == 0:
      num_neg += 1

  #If unbalanced, randomly flip sign of one edge
  if num_neg % 2 !=0:
    edge = triangle[randint(0,2)]
    data = G.get_edge_data(edge[0], edge[1])
    if data['label'] == 0:
      G.add_edge(edge[0], edge[1], label = 1)
    else:
      G.add_edge(edge[0], edge[1], label = 0)

  return G

def color_nodes(L, R, G, edge):
  #If conditions met then not balanced
  if edge[0] in L and edge[1] in L: return False
  if edge[0] in R and edge[1] in R: return False

  #Put nodes on either side of edge into appropriate sets
  if edge[0] in L:
    R.add(edge[1])
  elif edge[0] in R:
    L.add(edge[1])
  else:
    R.add(edge[0])
    L.add(edge[1])

  #recursive search
  for next_edge in G.edges(edge[1]):
    if color_nodes(L, R, G, new_edge) == False:
      return False

  return True

def is_balanced(G):
  #Recreate graph combining all nodes connected by positive edges into super nodes
  new_G = nx.Graph()
  pos_edges = []
  neg_edges = []
  for edge in G.edges():
    data = G.get_edge_data(edge[0], edge[1])
    if data['label'] == 1:
      pos_edges.append(edge)
    else: neg_edges.append(edge)

  #graph of only positive edges
  pos_G = nx.Graph()
  pos_G.add_edges_from(pos_edges)

  #combine nodes in connected components into super nodes
  for comp in nx.connected_components(G):
    super_node = ''
    for node in comp:
      super_node += str(node) + ','
    new_G.add_node(super_node)

  #Creating dictionary with original nodes to super nodes
  nodes_to_super = {}
  for node in G.nodes():
    for s_node in new_G:
      if str(node) in s_node:
        nodes_to_super[node] = s_node

  #Now putting in negative edges between super nodes in the new graph
  for neg_edge in neg_edges:
      s_node1 = nodes_to_super[neg_edge[0]]
      s_node2 = nodes_to_super[neg_edge[1]]
      new_G.add_edge(s_node1, s_node2)

  #Sorting nodes on either side of each edge of new graph to color nodes
  L = Set()
  R = Set()
  new_edges = new_G.edges()
  return color_nodes(L, R, G, new_edges[0])

if __name__ == '__main__':
#Run dynamic process
  times = 100
  iters = 1000000
  num_balanced = 0
  print "Working..."
  for time in range(times):
    print 'One time', time, 'of test.'
    G = get_graph()
    for iter in range(iters):
      if iter % 100000 == 0: print 'On iteration', iter, 'of dynamic process.'
      triangle = get_triangle(G)
      G = dyna_proc(G, triangle)
    if is_balanced(G):
      num_balanced += 1
      print 'Graph is balanced.'
    else: print 'Graph is not balanced.'

  print float(num_balanced) / float(times)

