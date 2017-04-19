import numpy as np

def distancesq(r1,r2): return (r2[0]-r1[0])**2 + (r2[1]-r1[1])**2

def addtup(i,j): return tuple(map(sum,zip(i,j)))

def eledivtup(i,j): return tuple(map((lambda x: x[0]/x[1]),zip(i,j)))

def scadivtup(t,s): return tuple(map((1./s).__mul__, t))

def findClosestNode(pointArray, p):
    npPointArray = np.asarray(pointArray)
    deltas = npPointArray - p
    return pointArray[np.argmin( np.einsum('ij,ij->i', deltas, deltas) )]
pass

def isInsideRect(p,rectVects,edgesAreLava=True):
	if edgesAreLava:
		for rect in rectVects:
					
			w = rect[0][0]
			s = rect[0][1]
			e = rect[2][0]
			n = rect[2][1]
			
			#If the centerpoint falls inside one of the rectangles, add to list for removal
			return(  				p[1] < n					and \
					w < p[0]		 and			p[0] < e  	and \
								p[1] > s						)
			pass
		pass
	else:
		for rect in rectVects:
					
			w = rect[0][0]
			s = rect[0][1]
			e = rect[2][0]
			n = rect[2][1]
			
			#If the centerpoint falls inside one of the rectangles, add to list for removal
			return(  				p[1] <= n					and \
					w <= p[0]		 and			p[0] <= e  	and \
								p[1] >= s						)
				
			pass
		pass
	pass
	#Comment of shame
	#There used to be a return false statement here
pass