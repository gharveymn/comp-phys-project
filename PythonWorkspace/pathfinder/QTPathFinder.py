import Plotting as pl
from pathlib import Path as filePath
import PathOpt
import os
from HelperMethods import *
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.path as mpath
import matplotlib.patches as patches
import matplotlib.animation as animation
import matplotlib.lines as lines
import time
import copy
import collections
from drawnow import drawnow

#**
#pack 
#
# is defined as [gdict,fig,ax,limits]
#**

#main is called by "if __name__ == "__main__":" at the bottom of the file, or by findShortestPath
def main(startPoint, endPoint, pack):
	#pack includes the large gdict variable, so save it when you run it the first time. This improves speed tremendously.

	if not pack:
		pack = initData()
	pass
	
	line = lines.Line2D([],[],lw=2,c='red')
	ax = pack[2]
	ax.add_line(line)
	findPathDijkstra(*pack,startPoint,endPoint,line)

	return pack

pass


def initData():

	plt.clf()

	#ion is interactive mode on. This makes it so the window doesn't close after processing
	plt.ion()

	#parse the rectangles
	limits, rectVects = parseMap()

	#Get data from the quadtree file
	gdict = parseQT(limits,rectVects)

	fig, ax = plotBox(gdict,limits,rectVects)

	####this is pack
	return [gdict, fig, ax, limits]

pass


def findPathDijkstra(gdict,fig,ax,limits,startPoint,endPoint,line):

	r1 = findClosestNode(gdict,startPoint)
	r2 = findClosestNode(gdict,endPoint)
	

	t1 = time.time()
	sp = PathOpt.dijkstra(gdict,r1,r2)
	t2 = time.time()

	print(t2-t1)

	line.set_xdata([p[0] for p in sp[1]])
	line.set_ydata([p[1] for p in sp[1]])

	# path = sp[1]
	# path.insert(0,startPoint)
	# path.append(endPoint)

	#pl.plotPath(ax,path,'red')

pass


def findPathAStar(gdict,fig,ax,limits,startPoint,endPoint,line):


	r1 = findClosestNode(gdict,startPoint)
	r2 = findClosestNode(gdict,endPoint)

	t1 = time.time()
	sp = PathOpt.AStar(gdict,r1,r2,1)
	t2 = time.time()

	print(t2-t1)

	line.set_xdata([p[0] for p in sp[1]])
	line.set_ydata([p[1] for p in sp[1]])

	#print("(6.25,1.25):{0}".format(gdict[(6.25,1.25)]))
	#print("(6.25,0.0):{0}".format(gdict[(6.25,0.0)]))
	# path = sp[1]
	# path.insert(0,startPoint)
	# path.append(endPoint)

	#pl.plotPath(ax,path,'red')
	
pass


def findPathBoth(gdict,fig,ax,limits,startPoint,endPoint,line):

	findPathAStar(gdict,fig,ax,limits,startPoint,endPoint,line)
	findPathDijkstra(gdict,fig,ax,limits,startPoint,endPoint,line)

pass


#Shouldn't be needed as of April 13, 1PM. We now clean as we instaniate
def deportIllegals(gdict, rectVects):

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


def isInsideRect(p,rectVects,edgesAreLava=True):
	if edgesAreLava:
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
	else:
		for rect in rectVects:
					
			w = rect[0][0]
			s = rect[0][1]
			e = rect[2][0]
			n = rect[2][1]
			
			#If the centerpoint falls inside one of the rectangles, add to list for removal
			if(  				p[1] <= n					and \
					w <= p[0]		 and			p[0] <= e  	and \
								p[1] >= s						):
				#-------------------------------------------------------#
				return True
			pass
		pass
	pass
	return False
pass


def parseQT(limits, rectVects):

	my_file = filePath('tree.txt')
	if not my_file.is_file():
    		os.startfile('CreateQT.exe')
	pass

	file = open('tree.txt', 'r')
	data = [float(val) for val in file.read().strip().split()]

	gdict = collections.OrderedDict()

	limitRect = [[(limits[0],limits[2]),(limits[1],limits[2]),(limits[1],limits[3]), (limits[0],limits[3])]]

	i = 0
	while(i < len(data) - 4):
		x = data[i]
		y = data[i + 1]
		l = data[i + 2]
		w = data[i + 3]
		
		num_adjacent = int(data[i+4])
		i += 5

		if not isInsideRect((x,y),rectVects):

			if (x,y) not in gdict:
				gdict[(x,y)] = {}
			pass

			if isInsideRect((x+l,y),limitRect,edgesAreLava=False) and not isInsideRect((x+l,y),rectVects):
				gdict[(x,y)][(x+l,y)] = l
				#print("{0}, {1}".format((x,y),(x+l,y)))
				if (x+l,y) in gdict:
					gdict[(x+l,y)][(x,y)] = l
					#print("{0}, {1}".format((x+l,y),(x,y)))
				else:
					gdict[(x+l,y)] = {(x,y):l}
					#print("{0}, {1}".format((x+l,y),(x,y)))
				pass
			pass

			if isInsideRect((x,y+w),limitRect,edgesAreLava=False) and not isInsideRect((x,y+w),rectVects):
				gdict[(x,y)][(x,y+w)] = w
				#print("{0}, {1}".format((x,y),(x,y+w)))
				if (x,y+w) in gdict:
					gdict[(x,y+w)][(x,y)] = w
					#print("{0}, {1}".format((x,y+w),(x,y)))
				else:
					gdict[(x,y+w)] = {(x,y):w}
					#print("{0}, {1}".format((x,y+w),(x,y)))
				pass
			pass

			for j in range(i,i+num_adjacent*4,4):
				x1 = data[j]
				y1 = data[j+1]
				l1 = data[j+2]
				w1 = data[j+3]

				if not isInsideRect((x1,y1),rectVects):
					gdict[(x,y)][(x1,y1)] = l1+w1
					if (x1,y1) in gdict:
						gdict[(x1,y1)][(x,y)] = l1+w1
					else:
						gdict[(x1,y1)] = {(x,y):l1+w1}
					pass
				pass
			pass
		pass

		i += num_adjacent*4

	pass
				
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
pass


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


def findShortestPath(startPoint,endPoint, pack=[]):
	return main(startPoint,endPoint,pack)
pass


def plotBox(gdict,limits,rectVects):
	fig = plt.figure(1)
	plt.scatter(*list(zip(*gdict.keys())),s=1)
	ax = fig.gca()

	ax.set_xlim(limits[0],limits[1])
	ax.set_ylim(limits[2],limits[3])
	
	for rects in rectVects:
		drawRect(ax,rects)
	pass

	for i in gdict:
		for j in gdict[i]:
			path = [i,j]
			pl.plotPath(ax,path,linewidth=1)
		pass
	pass

	plt.show()

	return fig, ax

pass


def findAllPaths(pack = [],needsFigure = False):
	#TODO Find all paths!

	if not pack:
		pack = initData()
	pass

	if needsFigure:
		limits, rectVects = parseMap()
		fig, ax = plotBox(pack[0],limits,rectVects)
		pack = [pack[0], fig, ax, limits]
	pass
	fig = pack[1]
	ax = pack[2]
	limits = pack[3]
	line = lines.Line2D([],[],lw=2,c='red')
	ax.add_line(line)
	findPathDijkstra(*pack,(0,0),(8,7.8),line)
	plt.draw()
	numPaths = 15
	for i in range(numPaths):
		k = limits[1]*i/numPaths
		findPathDijkstra(*pack,(k,0),(8,7.8),line)

		#Sometimes this works, sometimes it doesn't... idk.
		#Calculations are good though.
		fig.canvas.draw()
		fig.canvas.flush_events()
	pass

	return pack

pass


if __name__ == "__main__":
	os.chdir(os.path.dirname(os.path.abspath(__file__)))
	findAllPaths()
pass