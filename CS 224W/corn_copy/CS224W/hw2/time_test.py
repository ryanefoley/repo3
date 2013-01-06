from datetime import datetime

tstart = datetime.now()

temp = 0

for i in range(100000000):
  temp = i

tend = datetime.now()
print tend - tstart
