from pylab import *

t = list(range(30))
s=[]
r=[]

read_file = open('Normas-HITS')

for line in read_file:
	sr, rr= line.strip().split('	')
	s.append(float(sr))
	r.append(float(rr))
plot(t, s, label="Vector de Peso X") 
plot(t, r, label="Vector de Peso Y")

legend()
xlabel('Iteraciones')
ylim(0.00001,1)
yscale('log')
ylabel('Diferencias de las Normas por Iteracion')
title('NotreDame Convergencia HITS')
grid(True)
show()
