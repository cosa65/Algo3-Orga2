from pylab import *

t = 0.5, 1, 2, 2.5, 5, 10
s = 223.142,13.774, 0.893, 0.38, 0.037,0.009
r = nan, 462.923, 13.245, 4.374, 0.153, 0.062
plot(t, r)
plot(t, s)

xlabel('granularidad (m)')
ylabel('tiempo (s)')
title('Tiempo test1')
grid(True)
savefig("test.png")
show()


