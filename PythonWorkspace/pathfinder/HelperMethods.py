def distancesq(r1,r2): return (r2[0]-r1[0])**2 + (r2[1]-r1[1])**2

def addtup(i,j): return tuple(map(sum,zip(i,j)))

def eledivtup(i,j): return tuple(map((lambda x: x[0]/x[1]),zip(i,j)))

def scadivtup(t,s): return tuple(map((1./s).__mul__, t))