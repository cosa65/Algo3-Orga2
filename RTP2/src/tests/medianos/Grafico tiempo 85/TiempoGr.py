from pylab import *

names = []
values = []

read_file = open('tiempo.txt')

for line in read_file:
	name, value = line.strip().split(';')
	names.append(name)
	values.append(float(value))
	
tick_params(axis='x', colors= '#072b57')
tick_params(axis='y', colors= '#072b57')
xlabel('C 0.85', color= '#072b57')
ylabel('Ciclos', color= '#072b57')
yscale('log')
title('Tiempos (Ciclos) Comparacion', color='#072b57')
pos = arange(len(names)) + .5

colour = ['lawngreen', 'lawngreen', 'lawngreen', 'lawngreen', 'lawngreen']

bar(pos, values, align='center', color = colour)#color= '#b8ff5c')
xticks(pos, names, size='small')
grid(True)
show()
