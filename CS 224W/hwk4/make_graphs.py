import matplotlib.pyplot as plt
import matplotlib
import cPickle

#B1 = cPickle.load(open('B1.pkl', 'rb'))
#B2 = cPickle.load(open('B2.pkl', 'rb'))

b1 = sorted(B1, reverse = True)
b2 = sorted(B2, reverse = True)

plt.figure()
plt.plot(b1, color = 'green', label = 'Algo 1')
plt.plot(b2, color = 'magenta', label = 'Algo 2')
plt.legend(loc='upper right')
plt.show()
