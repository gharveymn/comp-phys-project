import Plotting as pl
from pathlib import Path as filePath
import PathOpt
import os
from HelperMethods import *
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.path as mpath
import matplotlib.patches as patches
import time
import copy

def main(startPoint, endPoint, gdict):

	plt.ion()
	plt.clf()

	#Get data from QT
	if not gdict:
		gdict = parseQT()
	pass

	fig1 = plt.figure(1)
	plt.scatter(*list(zip(*gdict.keys())),s=1)
	ax = fig1.gca()

	limits, rectVects = parseMap()

	ax.set_xlim(limits[0],limits[1])
	ax.set_ylim(limits[2],limits[3])
	
	for i in gdict:
		for j in gdict[i]:
			path = [i,j]

			pl.plotPath(ax,path,linewidth=1)

		pass
	pass

	#return

	for rects in rectVects:
		drawRect(ax,rects)
		pass
	pass

	plt.scatter(*list(zip(*gdict.keys())),s=1)

	deportIllegals(gdict,rectVects)

	findPathAStar(gdict,ax,startPoint,endPoint,limits)

	return gdict, ax, limits

pass


def findPathDijkstra(gdict,ax,startPoint,endPoint,limits):

	r1 = findClosestNode(gdict,startPoint)
	r2 = findClosestNode(gdict,endPoint)
	
	t1 = time.time()
	sp = PathOpt.dijkstra(gdict,r1,r2,ax)
	t2 = time.time()

	print(t2-t1)

	path = sp[1]
	path.insert(0,startPoint)
	path.append(endPoint)

	pl.plotPath(ax,path,'red')
	ax.set_xlim(limits[0],limits[1])
	ax.set_ylim(limits[2],limits[3])

	plt.show()
pass

def findPathAStar(gdict,ax,startPoint,endPoint,limits):

	r1 = findClosestNode(gdict,startPoint)
	r2 = findClosestNode(gdict,endPoint)

	t1 = time.time()
	sp = PathOpt.AStar(gdict,r1,r2)
	t2 = time.time()

	print(t2-t1)

	path = sp[1]
	path.insert(0,startPoint)
	path.append(endPoint)

	pl.plotPath(ax,path,'red')
	ax.set_xlim(limits[0],limits[1])
	ax.set_ylim(limits[2],limits[3])

	plt.show()

	return ax

pass


def findPathBoth(gdict,ax,startPoint,endPoint,limits):

	findPathAStar(gdict,ax,startPoint,endPoint,limits)
	findPathDijkstra(gdict,ax,startPoint,endPoint,limits)

pass


def deportIllegals(gdict, rectVects):

	#toRemove = {}

	#Remove all paths which pass though a rectangle
	# for i in gdict:
	# 	for j in gdict[i]:
	# 		centerPoint = scadivtup(addtup(i,j),2)
	# 		if(isInsideRect(centerPoint,rectVects)):
	# 			toRemove[i] = j
	# 		pass
	# 	pass
	# pass

	# for i,j in toRemove.items():
	# 	gdict[i].pop(j)
	# pass

	toRemove = set()
	#Remove all points which are inside rectangles
	for point in gdict:
		if(isInsideRect(point,rectVects)):
			toRemove.add(point)
		pass
	pass

	#Clean all levels containing these points
	for point in toRemove:
		gdict.pop(point,0)
		for j in gdict.values():
			j.pop(point,0)
		pass
	pass

	
	toRemove = set()

	#If i:{} then remove the empty i
	for i,j in gdict.items():
		if not j:
			toRemove.add(i)
		pass
	pass

	for i in toRemove:
		del gdict[i]
	pass


pass

def isInsideRect(p,rectVects):
	for rect in rectVects:
				
		w = rect[0][0]
		s = rect[0][1]
		e = rect[2][0]
		n = rect[2][1]
		
		#If the centerpoint falls inside one of the rectangles, add to list for removal
		if(  				p[1] < n					and \
				w < p[0]		 and			p[0] < e  	and \
							p[1] > s						):
			#-------------------------------------------------------#
			return True
		pass
	pass
	return False
pass


def parseQT():

	my_file = filePath('tree.txt')
	if not my_file.is_file():
    		os.startfile('CreateQT.exe')
	pass

	file = open('tree.txt', 'r')
	data = [float(val) for val in file.read().strip().split()]


	gdict = {}

	i = 0
	while(i < len(data) - 4):
		x = data[i]
		y = data[i + 1]
		l = data[i + 2]
		w = data[i + 3]
		
		num_adjacent = int(data[i+4])
		i += 5

		gdict[(x,y)] = {}

		gdict[(x,y)][(x+l,y)] = l
		gdict[(x,y)][(x,y+w)] = w

		if (x+w,y) in gdict:
			gdict[(x+l,y)][(x,y)] = l
		else:
			gdict[(x+l,y)] = {(x,y):l}
		pass

		if (x,y+l) in gdict:
			gdict[(x,y+w)][(x,y)] = w
		else:
			gdict[(x,y+w)] = {(x,y):w}
		pass
		

		#gdict[(x,y)] = {(x+l,y+w):np.sqrt(l**2 + w**2)}
		for j in range(i,i+num_adjacent*4,4):
			x1 = data[j]
			y1 = data[j+1]
			l1 = data[j+2]
			w1 = data[j+3]
			gdict[(x,y)][(x1,y1)] = l1+w1
			

			#gdict[(x,y)][(x1,y1)] = distancesq((x,y),(x1,y1))

		pass


		i += num_adjacent*4

	pass

	# appendables = copy.deepcopy(gdict)

	# #Create new indices using second order coordinates, find neighbors. These will be filtered later.
	# for i in gdict:
	# 	for j in gdict[i]:
	# 		if j not in appendables:
	# 			appendables[j] = {i:gdict[i][j]}
	# 		else:
	# 			appendables[j][i] = gdict[i][j]
	# 		pass
	# 	pass
	# pass

	# gdict = appendables
				
	return gdict

pass


def parseMap():
	file = open('map.txt', 'r')
	data = [float(val) for val in file.read().strip().split()]

	x_min = data[0]
	x_max = data[1]
	y_min = data[2]
	y_max = data[3]
	limits = [x_min,x_max,y_min,y_max]
	num_squares = int(data[4])

	rectVects = [[]]*num_squares
	j = 0
	for i in range(5,len(data),3):
		x = data[i]
		y = data[i+1]
		w = data[i+2]
		rectVects[j] = [(x,y),(x+w,y),(x+w,y+w),(x,y+w),(x,y)]
		j += 1
	pass

	return limits, rectVects


def drawRect(ax,verts,fc='yellow'):

	codes = [mpath.Path.MOVETO,
         mpath.Path.LINETO,
         mpath.Path.LINETO,
         mpath.Path.LINETO,
         mpath.Path.CLOSEPOLY,
         ]

	path = mpath.Path(verts, codes)

	patch = patches.PathPatch(path, facecolor=fc, lw=1)
	ax.add_patch(patch)
pass


def findClosestNode(gdict,p):
	return min(gdict.keys(), key=lambda x: distancesq(x, p))
pass


def findShortestPath(startPoint,endPoint, gdict={}):
	main(startPoint,endPoint,gdict)
pass


def findAllPaths(gdict,ax,limits):
	#TODO Find all paths!
pass


if __name__ == "__main__":
	os.chdir(os.path.dirname(os.path.abspath(__file__)))
	findShortestPath((0,0),(8,7.8))
pass
