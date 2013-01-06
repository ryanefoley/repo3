import workerpool
import __builtin__

counts = {}
__builtin__.counts = counts

sentences = [['this', 'is', 'a', 'test'], ['test', 'test']]

class DownloadJob(workerpool.Job):
    def __init__(self, s):
        self.s = s
    def run(self):
        for word in self.s:
            if word in counts:
                counts[word] += 1
            else:
                counts[word] = 1

# Initialize a pool, 5 threads in this case
pool = workerpool.WorkerPool(size=2)

# Loop over urls.txt and create a job to download the URL on each line
for sentence in sentences:
    job = DownloadJob(sentence)
    pool.put(job)

# Send shutdown jobs to all threads, and wait until all the jobs have been completed
pool.shutdown()
pool.wait()

print counts
