import matplotlib.pyplot as plt
import matplotlib
import networkx as nx
from random import *
import excess_degree as ed

degree_sequence1=sorted(nx.degree(gnm).values(),reverse=True)
degree_sequence2=sorted(nx.degree(sw).values(),reverse=True)
degree_sequence3=sorted(nx.degree(rw).values(),reverse=True)
counts1 = {}
counts2 = {}
counts3 = {}
for degree in degree_sequence1:
  if(degree in counts1):
    counts1[degree] += 1
  else: counts1[degree] = 1

for degree in degree_sequence2:
  if(degree in counts2):
    counts2[degree] += 1
  else: counts2[degree] = 1

for degree in degree_sequence3:
  if(degree in counts3):
    counts3[degree] += 1
  else: counts3[degree] = 1

x = []
y = []
for degree in counts1:
  x.append(degree)
  y.append(counts1[degree])

p1, = plt.loglog(x, y,'bo')


x = []
y = []
for degree in counts2:
  x.append(degree)
  y.append(counts2[degree])

p2, = plt.loglog(x, y,'ro')

x = []
y = []
for degree in counts3:
  x.append(degree)
  y.append(counts3[degree])

p3, = plt.loglog(x, y,'yo')

plt.title("Degree rank plot")
plt.ylabel("log count")
plt.xlabel("log degree")
plt.legend([p1, p2, p3], ["Gnm", "Small-World", "Real-World"])
plt.savefig("test3.png")
plt.close()

