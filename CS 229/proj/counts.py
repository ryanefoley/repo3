import csv

filename = 'Data-1.0.csv'
reader = csv.reader(open('Data-1.0.csv', 'rb'))
count_0 = 0
count_1 = 0
for row in reader:
    if row[0] == '0':
        count_0 += 1
    else:
        count_1 += 1

print count_0
print count_1
