import networkx as nx
import matplotlib.pyplot as plt
import matplotlib
from sets import Set


#assigning votes and also turning all nodes into ints
def assign_votes(G):
  new_G = nx.Graph()
  for node in G.nodes():
    n = int(node) % 10
    if n >= 0 and n < 4:
      decision = 'A'
    elif n >= 4 and n < 8:
      decision = 'B'
    else:
      decision = 'U'
    new_G.add_node(int(node), vote = decision)

  for edge in G.edges():
    new_G.add_edge(int(edge[0]), int(edge[1]))

  return new_G

#A function to return a list of nodes that have undecided votes at the start
def get_undecided(G):
  undecided = []
  nodes_to_votes = nx.get_node_attributes(G, 'vote')
  for node in nodes_to_votes:
    if nodes_to_votes[node] == 'U':
      undecided.append(node)
  return undecided

def advert_effect(dollars, G):
  num_voters = (dollars/100)
  for voter in range(3000, 3000 + num_voters):
    G.add_node(voter, vote = 'A')
  return G

#A function to invert the dictionary of nodes to votes into votes to nodes
def get_votes_to_nodes(G):
  nodes_to_votes = nx.get_node_attributes(G, 'vote')
  votes_to_nodes = {}

  for node in nodes_to_votes:
    vote = nodes_to_votes[node]
    if vote not in votes_to_nodes:
      votes_to_nodes[vote] = []
    votes_to_nodes[vote].append(node)

  #Add in zero votes if no votes in particular type
  vote_types = ['A', 'B', 'U']
  for type in vote_types:
    if type not in votes_to_nodes:
      votes_to_nodes[type] = []

  return votes_to_nodes

def voting_round(G, round, undecided):
  nodes_to_votes = nx.get_node_attributes(G, 'vote')
  votes_to_nodes = get_votes_to_nodes(G)

  #Printing current standings
  for vote in votes_to_nodes:
    print len(votes_to_nodes[vote]), 'for', vote

  for undec in sorted(undecided):
    #count up votes of neighbors
    A_voters = 0
    B_voters = 0
    for neighbor in G.neighbors(undec):
      if nodes_to_votes[neighbor] == 'A':
        A_voters += 1
      if nodes_to_votes[neighbor] == 'B':
        B_voters += 1

    #Compute undeclared nodes new decision
    if A_voters == B_voters:
      if round % 2 == 0:
        if undec % 2 == 0:
          decision = 'B'
        else:
          decision = 'A'
      else:
        if undec % 2 == 1:
          decision = 'B'
        else:
          decision = 'A'

    elif A_voters > B_voters: decision = 'A'
    else: decision = 'B'

    #Add node back in to graph with updated decision
    G.add_node(undec, vote = decision)

  return G

def get_winner(G):
  votes_to_nodes = get_votes_to_nodes(G)
  if len(votes_to_nodes['A']) > len(votes_to_nodes['B']):
    return 'A'
  elif len(votes_to_nodes['A']) < len(votes_to_nodes['B']):
    return 'B'
  else:
    return 'U'

def with_ads(G, rounds, graph_number):
  G = assign_votes(G)
  x = []
  y = []
  for i in range(10):
    dollars = 1000*i
    x.append(dollars)
    G = advert_effect(dollars, G)
    undecided = get_undecided(G)
    for round in range(rounds):
      print 'Round', round
      G = voting_round(G, round, undecided)
    votes_to_nodes = get_votes_to_nodes(G)
    margin = len(votes_to_nodes['A']) - len(votes_to_nodes['B'])
    y.append(margin)

  #Making Plot
  plt.figure()
  plt.plot(x,y, 'ro')
  plt.title("Plot of Dollars Spent on Ads vs. Margin of Victory of A for G" + str(graph_number))
  plt.ylabel("Margin of Victory")
  plt.xlabel("Dollars Spent on Ads")
  plt.savefig("adspend_plot_" + str(graph_number) + ".png")
  plt.close()
  print x
  print y

def dictinvert(d):
  inv = {}
  for k, v in d.iteritems():
    keys = inv.setdefault(v, [])
    keys.append(k)
  return inv

def wining_and_dining(dollars, G):
  num_diners = dollars / 1000
  nodes_to_out_deg = G.degree(G.nodes())
  #invert out_degree
  out_deg_to_nodes = dictinvert(nodes_to_out_deg)

  #sort out degrees
  out_degs = sorted(list(Set(G.degree(G.nodes()).values())), reverse = True)

  #Getting diners
  diners = 0
  for deg in out_degs:
    if diners == num_diners:
      break
    for node in out_deg_to_nodes[deg]:
      print deg
      diners += 1
      G.add_node(node, vote = 'A')
      if diners == num_diners:
        break
  return G

def with_wining_and_dining(G, rounds, graph_number):
  G = assign_votes(G)
  x = []
  y = []
  for i in range(10):
    dollars = 1000*i
    x.append(dollars)
    G = wining_and_dining(dollars, G)
    undecided = get_undecided(G)
    for round in range(rounds):
      print 'Round', round
      G = voting_round(G, round, undecided)
    votes_to_nodes = get_votes_to_nodes(G)
    margin = len(votes_to_nodes['A']) - len(votes_to_nodes['B'])
    y.append(margin)

  #Making Plot
  plt.figure()
  plt.plot(x,y, 'ro')
  plt.title("Plot of Dollars Spent on Wining and Dining  vs. Margin of Victory of A for G" + str(graph_number))
  plt.ylabel("Margin of Victory")
  plt.xlabel("Dollars Spent on Wining and Dining")
  plt.savefig("winign_and_dining_plot_" + str(graph_number) + ".png")
  plt.close()
  print x
  print y

def no_spending(G1, G2, rounds):
  G1 = assign_votes(G1)
  undecided = get_undecided(G1)
  for round in range(rounds):
    print 'Round', round
    G1 = voting_round(G1, round, undecided)

  winner = get_winner(G1)
  votes_to_nodes = get_votes_to_nodes(G1)
  print 'The winner of G1 is', winner
  print 'Votes for A:', len(votes_to_nodes['A'])
  print 'Votes for B:', len(votes_to_nodes['B'])
  print 'Votes for U:', len(votes_to_nodes['U'])

  G2 = assign_votes(G2)
  undecided = get_undecided(G2)
  for round in range(rounds):
    print 'Round', round
    G2 = voting_round(G2, round, undecided)

  winner = get_winner(G2)
  votes_to_nodes = get_votes_to_nodes(G2)
  print 'The winner of G2 is', winner
  print 'Votes for A:', len(votes_to_nodes['A'])
  print 'Votes for B:', len(votes_to_nodes['B'])
  print 'Votes for U:', len(votes_to_nodes['U'])

if __name__ == '__main__':
  rounds = 10
  G1 = nx.read_adjlist('g1.edgelist')
  G2 = nx.read_adjlist('g2.edgelist')

  #no_spending(G1, G2, rounds)

  #with_ads(G1, rounds, 1)
  #with_ads(G2, rounds, 2)

  with_wining_and_dining(G1, rounds, 1)
  with_wining_and_dining(G2, rounds, 2)

