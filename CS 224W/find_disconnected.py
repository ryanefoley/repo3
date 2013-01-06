import networkx as nx
from sets import Set
import cPickle

G = nx.read_adjlist('email_network.txt', create_using=nx.DiGraph())
print len(G.nodes())

scc = nx.strongly_connected_components(G)

b_scc = scc[0]
nodes_in = cPickle.load(open('nodes_in.pkl', 'rb'))
nodes_out = cPickle.load(open('nodes_out.pkl', 'rb'))

