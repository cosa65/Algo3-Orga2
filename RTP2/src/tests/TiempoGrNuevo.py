from pylab import *

t = [0.5,0.7,0.85,0.95]
s=[]
r=[]
g=[]
h=[]

read_file = open('Tiempo')

for line in read_file:
	sr, rr, gr, hr = line.strip().split('	')
	s.append(float(sr))
	r.append(float(rr))
	g.append(float(gr))
	h.append(float(hr))
plot(t, s, label="Censorship") 
plot(t, r, label="Movies")
plot(t, g, label="Notre-Dame")
plot(t, h, label="Stanford")

legend(loc='center right')

xlabel('c')
yscale('log')
ylabel('Tiempo (ciclos)')
title('Tiempos PageRank')
grid(True)
show()
