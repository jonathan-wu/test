import pylab
v=[2.75,2.5,2.0,1.5,1.25,1.05,0.9,0.8,0.7]
L=[15,20,30,40,50,60,70,80,90]
V=[]
for i in range(9):
    V.append(1/(4096*(v[i]/3.3)))
pylab.plot(L,V,'r')
a,b = pylab.polyfit(L,V,1)
fit = []
for i in range(9):
    fit.append(a*L[i]+b)
pylab.plot(L,fit,'b')
pylab.show()
print "1/v="+str(a)+"*R+"+str(b)
