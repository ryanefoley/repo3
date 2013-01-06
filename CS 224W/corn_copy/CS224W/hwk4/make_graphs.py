import matplotlib.pyplot as plt
import matplotlib
import cPickle

B1 = cPickle.load(open('B1.pkl', 'rb'))
B2 = cPickle.load(open('B2.pkl', 'rb'))

b1 = []
b2 = []
for k in B1:
  b1.append(B1[k])

for k in B2:
  b2.append(B2[k])

b1 = sorted(b1, reverse = True)
b2 = sorted(b2, reverse = True)

plt.figure()
plt.plot(b1)
