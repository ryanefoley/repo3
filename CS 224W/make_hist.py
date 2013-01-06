import matplotlib.pyplot as plt
import matplotlib
import networkx as nx
from random import *
import excess_degree as ed

def make_hist(gnm, sw, rw):
  degree_sequence1=sorted(nx.degree(gnm).values(),reverse=True)
  degree_sequence2=sorted(nx.degree(sw).values(),reverse=True)
  degree_sequence3=sorted(nx.degree(rw).values(),reverse=True)

  counts1 = {}
  counts2 = {}
  counts3 = {}
  for i in range(len(degree_sequence1)):
    if(i in counts1):
      counts1[i] += 1
    else: counts1[i] = 1

  for i in range(len(degree_sequence2)):
    if(i in counts2):
      counts2[i] += 1
    else: counts2[i] = 1

  for i in range(len(degree_sequence3)):
    if(i in counts3):
      counts3[i] += 1
    else: counts3[i] = 1

  counts = []
  for i in range(len(counts1)):
    counts.append(float(counts1[i]))

  p1, = plt.loglog(counts,'b-',marker='o')

  counts = []
  for i in range(len(counts2)):
    counts.append(float(counts2[i]))

  p2, = plt.loglog(counts,'r-',marker='o')

  counts = []

  for i in range(len(counts3)):
    counts.append(float(counts3[i]))

  p3, = plt.loglog(counts,'y-',marker='o')


  #p1, = plt.loglog(counts1,'b-',marker='o')
  #p2, = plt.loglog(counts2,'r-',marker='o')
  #p3, = plt.loglog(counts3,'y-',marker='o')
  plt.title("Degree rank plot")
  plt.ylabel("degree")
  plt.xlabel("rank")
  plt.legend([p1, p2, p3], ["Gnm", "Small-World", "Real-World"])
  plt.savefig("test3.png")
  plt.close()

