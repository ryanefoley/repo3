import networkx as nx
import matplotlib.pyplot as plt
import matplotlib

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


#Expected Excess Degree for 3 graphs:
print "Expected Excess Degree for 3 graphs:"
q1 = get_q(gnm)
#print exp_excess_degree(q1)
q2 = get_q(sw)
#print exp_excess_degree(q2)
q3 = get_q(rw)
#print exp_excess_degree(q3)

x = []
y = []
for i in q1:
  x.append(i)
  y.append(q1[i])
p1, = plt.loglog(x,y,'b',marker='o')

x = []
y = []
for i in q2:
    x.append(i)
    y.append(q2[i])
p2, = plt.loglog(x,y,'r',marker='o')

x = []
y = []
for i in q3:
    x.append(i)
    y.append(q3[i])
p3, = plt.loglog(x,y,'y',marker='o')

plt.title("Excess Degree Distribution")
plt.ylabel("excess degree")
plt.xlabel("k")
plt.legend([p1, p2, p3], ["Gnm", "Small-World", "Real-World"])
plt.savefig("excess_degree_histogram3.png")
plt.close()


#Expected Degree for the 3 graphs:
#print "Expected Degree for the 3 graphs:"
#p = get_p(gnm)
#print exp_degree(p)
#p = get_p(sw)
#print exp_degree(p)
#p = get_p(rw)
#print exp_degree(p)

