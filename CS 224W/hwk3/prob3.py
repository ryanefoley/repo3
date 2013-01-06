import csv
import matplotlib
import matplotlib.pyplot as plt

reader = csv.reader(open('mobydick.txt', 'rb'))
md = []
for row in reader:
    md.append(row[0])

reader = csv.reader(open('donquijote.txt', 'rb'))
dq = []
for row in reader:
    dq.append(row[0])

def get_freqs(lst):
    freqs = {}
    for item in lst:
        if item in freqs:
            freqs[item] += 1
        else:
            freqs[item] = 1
    return freqs

md_freqs = get_freqs(md)
dq_freqs = get_freqs(dq)

def inv_dict(d):
    new = {}
    for key in d:
        if d[key] in new:
            new[d[key]].append(key)
        else:
            new[d[key]] = []
            new[d[key]].append(key)
    return new

def get_plots(freqs, name):
    freqs_words = inv_dict(freqs)
    freq_vals = sorted(freqs.values())
    x = freq_vals
    y = []
    for val in freq_vals:
        y += [len(freqs_words[val])]
    plt.loglog(x,y, 'ro')
    plt.savefig("prob3_plot"+name+".png")
    plt.close()

#get_plots(md_freqs, '1')
#get_plots(md_freqs, '2')

writer = csv.writer(open('md_freq.txt', 'wb'))
for key in md_freqs:
  writer.writerow([md_freqs[key]])

writer = csv.writer(open('dq_freq.txt', 'wb'))
for key in dq_freqs:
  writer.writerow([dq_freqs[key]])

