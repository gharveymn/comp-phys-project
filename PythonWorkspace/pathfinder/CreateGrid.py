import numpy as np
from scipy import interpolate

def densityGrid():
	# Provides x and y coordinates associated with one random z coordinate
	x = np.linspace(0, 1, 5)
	y = np.linspace(0, 1, 5)
	x, y = np.meshgrid(x, y)
	
	z = np.random.rand(x.size).reshape(x.shape)
	z /= z.sum()
	
	f = interpolate.interp2d(x, y, z, 'cubic')
	x2 = np.linspace(0, 1, 1000)
	y2 = np.linspace(0, 1, 1000)
	z2 = f(x2, y2)
	z2 /= z2.sum()
	x2, y2 = np.meshgrid(x2, y2)
	
	#zero out negative indices from interpolation
	z2[z2 < 0] = 0
	
	return x2,y2,z2
pass

def createGraphDict(x,y,z):
	"""Creates a dictionary of adjacent indices and associated density.
	Since x,y should be a linspace, we let each density be found
	with D(x+dx,y+dy,x,y) = abs(z(x+dx,y+dx)-z(x,y))dxdy, where dx, dy is the distance
	between each x and y in the grid, respectively."""
	
	dx = x[0, 1] - x[0, 0]
	dy = y[1, 0] - y[0, 0]
	dxdy = dx * dy
	D = lambda x1,y1,x2,y2:abs(z[x2,y2]-z[x1,y1])*dxdy
	
	xsz = x[0].size
	ysz = y[0].size
	
	#We maintain two lists---one for the actual values, the other for indices. This is so we can access z easily.
	xinds = range(xsz)
	yinds = range(ysz)
	allInds = [[(i,j) for i in xinds] for j in yinds]
	
	xlist = x[:1].flatten().tolist()
	ylist = y.T[:1].flatten().tolist()
	allPoints = [[(i,j) for i in xlist] for j in ylist]
	gdict = {j:{} for i in allPoints for j in i}
	
	indPtsMap = dict(zip([i for j in allInds for i in j],[i for j in allPoints for i in j]))
	#fill adjacent nodes in x direction
	#{(x_i,y_j):{(x_{i+1},y_j):D(x_{i+1},y_j,x_i,y_j)},...}
	for j in yinds:
		
		#looks like [([((0, 0), (1, 0)),((1, 0), (2, 0)),((2, 0), (3, 0)),...]
		compInds = list(zip(allInds[j][:-1],allInds[j][1:]))
		for p in compInds:
			gdict[indPtsMap[p[0]]][indPtsMap[p[1]]] = D(*p[0],*p[1])
		pass
	pass

	#Note that this is only in one direction, ie. we just did xdist(1->2) but we wont do xdist(2->1).
	#This is because it is taken care of in the algorithm.
	allIndsT = [list(a) for a in zip(*allInds)]
	
	for i in xinds:
		
		# looks like [([((0, 0), (0, 1)),((0, 1), (0, 2)),((0, 2), (0, 3)),...]
		compInds = list(zip(allIndsT[i][:-1], allIndsT[i][1:]))
		for p in compInds:
			gdict[indPtsMap[p[0]]][indPtsMap[p[1]]] = D(*p[0], *p[1])
		pass
	pass

	return gdict

pass
	
		
		
	
	
	
		
	

