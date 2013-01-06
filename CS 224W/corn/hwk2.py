import matplotlib.pyplot as plt
import matplotlib
import networkx as nx
from random import *
import excess_degree as ed


#Problem 1a
n = 5242
m = 14496

#Gnm Graph
print "Creating Gnm Graph..."
gnm = nx.gnm_random_graph(n, m)

#Small world graph
def small_world():
  print "Creating small world..."
  sw = nx.Graph()
  #create ring
  for i in range(n):
      if(i == n-1):
          sw.add_edge(i, 0)
          sw.add_edge(i, 1)
      else:
          if(i == n-2):
              sw.add_edge(i, i+1)
              sw.add_edge(i, 0)
          else:
              sw.add_edge(i, i+2)
              sw.add_edge(i, i+1)

  iters = 4012
  iter = 0
  while(iter < iters):
      n1 = randint(0, n-1)
      n2 = randint(0, n-1)
      if(n1 != n2 and (n1,n2) not in sw.edges() and (n2,n1) not in sw.edges()):
          sw.add_edge(n1,n2)
          iter += 1
  return sw

sw = small_world()

#Real-World Collaboration Network
print "Reading Real-World graph..."
rw = nx.read_adjlist("ca-GrQc.txt", create_using=nx.DiGraph())

print "Plotting..."
degree_sequence=sorted(nx.degree(gnm).values(),reverse=True) # degree sequenc
p1, = plt.loglog(degree_sequence,'b-',marker='o')
degree_sequence=sorted(nx.degree(sw).values(),reverse=True) # degree sequenc
p2, = plt.loglog(degree_sequence,'r-',marker='o')
degree_sequence=sorted(nx.degree(rw).values(),reverse=True) # degree sequenc
p3, = plt.loglog(degree_sequence,'y-',marker='o')
plt.title("Degree rank plot")
plt.ylabel("degree")
plt.xlabel("rank")
plt.legend([p1, p2, p3], ["Gnm", "Small-World", "Real-World"])
plt.savefig("degree_histogram.png")
plt.close()

#from collections import Counter
degree_sequence1=sorted(nx.degree(gnm).values(),reverse=True)
degree_sequence2=sorted(nx.degree(sw).values(),reverse=True)
degree_sequence3=sorted(nx.degree(rw).values(),reverse=True)
counts1 = Counter(degree_sequence1)
counts2 = Counter(degree_sequence2)
counts3 = Counter(degree_sequence3)
p1, = plt.loglog(counts1.items(),'b-',marker='o')
p2, = plt.loglog(counts2.items(),'r-',marker='o')
p3, = plt.loglog(counts3.items(),'y-',marker='o')
plt.title("Degree rank plot")
plt.ylabel("degree")
plt.xlabel("rank")
plt.legend([p1, p2, p3], ["Gnm", "Small-World", "Real-World"])
plt.savefig("degree_histogram.png")
plt.close()

counts1 = {}
counts2 = {}
counts3 = {}
for i in range(len(degree_sequence1)):
  if(i in counts1):
    counts1[i] += 1
  else: counts1[i] = 1

for i in range(len(degree_sequence1)):
  if(i in counts1):
    counts1[i] += 1
  else: counts1[i] = 1

for i in range(len(degree_sequence1)):
  if(i in counts1):
    counts1[i] += 1
  else: counts1[i] = 1

p1, = plt.loglog(counts1,'b-',marker='o')
p2, = plt.loglog(counts2,'r-',marker='o')
p3, = plt.loglog(counts3,'y-',marker='o')
plt.title("Degree rank plot")
plt.ylabel("degree")
plt.xlabel("rank")
plt.legend([p1, p2, p3], ["Gnm", "Small-World", "Real-World"])
plt.savefig("test3.png")
plt.close()


#1b - getting excess degree histograms

q = ed.excess_degree(gnm)
p1, = plt.loglog(q,'b-',marker='o')
q = ed.excess_degree(sw)
p2, = plt.loglog(q,'r-',marker='o')
q = ed.excess_degree(rw)
p3, = plt.loglog(q,'y-',marker='o')
plt.title("Excess Degree Distribution")
plt.ylabel("excess degree")
plt.xlabel("k")
plt.legend([p1, p2, p3], ["Gnm", "Small-World", "Real-World"])
plt.savefig("excess_degree_histogram.png")
plt.close()
