from pylab import *

values = []

read_file = open('../psnr')

for line in read_file:
	value = line
	values.append(float(value))
	
	
values=[values[0:11], values[12:23], values[24:35], values[36:47]]
xlabel('Metodos', color= '#072b57')
ylabel('PSNR', color= '#072b57')
title('PSNR', color='#072b57')

boxplot(values)
grid(True)
show()
