from pylab import *

t = list(range(101))
s=[]
r=[]
g=[]
h=[]

read_file = open('Normas-Page')

for line in read_file:
	sr, rr, gr, hr = line.strip().split('	')
	s.append(float(sr))
	r.append(float(rr))
	g.append(float(gr))
	h.append(float(hr))
plot(t, s, label="PageRank 0.5") 
plot(t, r, label="PageRank 0.7")
plot(t, g, label="PageRank 0.85")
plot(t, h, label="PageRank 0.95")

legend()
xlabel('Iteraciones')
ylim(0.00001,1)
yscale('log')
ylabel('Diferencias de las Normas por Iteracion')
title('Cens Convergencia PageRank')
grid(True)
show()
