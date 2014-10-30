from pylab import *

names = []
values = []

read_file = open('Tiempo')

for line in read_file:
	name, value = line.strip().split(';')
	names.append(name)
	values.append(float(value))
	
tick_params(axis='x', colors= '#072b57')
tick_params(axis='y', colors= '#072b57')
xlabel('Censo', color= '#072b57')
ylabel('Segundos', color= '#072b57')
title('Tiempos Censo', color='#072b57')
pos = arange(len(names)) + .5

bar(pos, values, align='center', color= '#b8ff5c')
xticks(pos, names, size='small')
grid(True)
show()
