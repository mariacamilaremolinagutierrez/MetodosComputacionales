import matplotlib.pyplot as plt
from numpy import *
import sys

try:
    n=int(sys.argv[1])
except IndexError:
    sys.exit("Se tiene que usar asi: python difusion_solar_central.py, donde n es el numero de fotones a propagar.")
except ValueError:
    sys.exit("El numero n de iteraciones debe ser un entero.")

R=10**5
pasos=ones(n)
xs=ones(n)
ys=ones(n)
zs=ones(n)

#Tengo que distribuir los puntos en la esfera
num=n
num2=0
for i in range(num):
    x=(0.5-random.random())*R
    y=(0.5-random.random())*R
    z=(0.5-random.random())*R
    if(sqrt(x**2+y**2+z**2)<=R):
        xs[num2]=x
        ys[num2]=y
        zs[num2]=z
        num2+=1
    else:
        num+=1

#Con las posiciones x,z,y de cada punto empiezo
r=1
for i in range(n):
    num=0
    x=xs[i]
    y=ys[i]
    z=zs[i]
    d=sqrt(x**2+y**2+z**2)
    while(d<R):
        teta=random.random()*2*pi
        fi=random.random()*pi
        x+=r*sin(teta)*cos(fi)
        y+=r*sin(teta)*sin(fi)
        z+=r*cos(fi)
        d=sqrt(x**2+y**2+z**2)
        num+=1
    pasos[i]=num

#Ahora hay que hacer el histrograma

filename = 'histo_difusion_solar_homogenea_'+str(n)

plt.figure()

plt.hist(pasos,bins=80)
plt.title("Histograma Difusion Solar")
plt.xlabel("Pasos")
plt.ylabel("Numero de Fotones")

plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)

plt.close()
