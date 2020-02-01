#We have 10000 jobs to do, each with some length l(i) and weight (importance) w(i).
#Our goal is to schedule these jobs in a way that minimizes the weighted sum of completion times.
#Using a greedy algorithm that schedules jobs in decreasing order of the difference (weight-length).
#To break ties, we schedule the job with the highest weight first. 

import operator

with open('jobs.txt','r') as f:
	lines = f.readlines()[1:]

length = 0
weight = 0
jobs = []

for i in lines:
	weight = (int)(i.split()[0])
	length = (int)(i.split()[1])
	jobs.append([weight,length,weight-length])

jobs.sort(key = operator.itemgetter(2,0), reverse = True)

sum = 0
totlength = 0
for i in jobs:
	totlength += i[1]
	sum += (totlength*i[0])

print(sum)

