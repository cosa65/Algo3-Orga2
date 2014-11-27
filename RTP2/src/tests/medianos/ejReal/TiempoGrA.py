from pylab import *
import matplotlib.pyplot as plt
from matplotlib.dates import date2num


y = []
z = []
k = []
w = []


read_file = open('Hub')
x=0
	
tick_params(axis='x', colors= '#072b57')
tick_params(axis='y', colors= '#072b57')
xlabel('Pagina Web', color= '#072b57')
ylabel('Puntaje', color= '#072b57')
title('Hits (Hub)', color='#072b57')
pos = arange(len(y)) + .5

colour=['salmon','goldenrod','peachpuff']

for line in read_file:
	y.append(float(line))

ax = plt.subplot(111)
for i in range(len(y)) :

	ax.bar(x+i+1, y[i],width=0.4,color='b',align='center')

ax.bar(x-0.3+i, 0,width=0.2,color='b',align='center')

plt.xlim(0.5, 14.5)

legend()

grid(True)

plt.show()
