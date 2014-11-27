from pylab import *
import matplotlib.pyplot as plt
from matplotlib.dates import date2num


y = []
z = []
k = []
w = []


read_file = open('Page')
x=0
	
tick_params(axis='x', colors= '#072b57')
tick_params(axis='y', colors= '#072b57')
xlabel('PageRank', color= '#072b57')
ylabel('Pagina Web', color= '#072b57')
title('Pagerank', color='#072b57')
pos = arange(len(y)) + .5

colour=['salmon','goldenrod','peachpuff']

for line in read_file:
	value, value2, value3, value4 = line.strip().split('	')
	y.append(float(value))
	z.append(float(value2))
	k.append(float(value3))
	w.append(float(value4))

ax = plt.subplot(111)
for i in range(len(y)) :

	ax.bar(x-0.3+i+1, y[i],width=0.2,color='b',align='center')
	ax.bar(x-0.1+i+1, z[i],width=0.2,color='g',align='center')
	ax.bar(x+0.1+i+1, k[i],width=0.2,color='r',align='center')
	ax.bar(x+0.3+i+1, w[i],width=0.2,color='y',align='center')

ax.bar(x-0.3+i, 0,width=0.2,color='b',align='center',label='c=0.5')
ax.bar(x-0.1+i, 0,width=0.2,color='g',align='center',label='c=0.7')
ax.bar(x+0.1+i, 0,width=0.2,color='r',align='center',label='c=0.85')
ax.bar(x+0.3+i, 0,width=0.2,color='y',align='center',label='c=0.95')

plt.xlim(0.5, 6.5)
plt.ylim(0, 0.25)

legend()

grid(True)

plt.show()
