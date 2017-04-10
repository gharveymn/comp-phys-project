import Plotting as pl
from pathlib import Path as filePath
import PathOpt
import os
from Main import distance
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.path as mpath
import matplotlib.patches as patches

def main():
	#Get data from QT
	gdict = parseQT()

	fig1 = plt.figure(1)
	plt.scatter(*list(zip(*gdict.keys())),s=1)
	ax = fig1.gca()

	limits, rectVects = parseMap()

	for rects in rectVects:
		drawRect(ax,rects)
	pass

	startPoint = (0,0)
	endPoint = (8,8)

	r1 = findClosestNode(gdict,startPoint)
	r2 = findClosestNode(gdict,endPoint)
	
	sp = PathOpt.dijkstra(gdict,r1,r2)

	path = sp[1]
	path.insert(0,r1)
	path.append(r2)

	pl.plotPath(ax,sp[1],'red')
	ax.set_xlim(limits[0],limits[1])
	ax.set_ylim(limits[2],limits[3])

	plt.show()

pass
	


def parseQT():

	my_file = filePath('tree.txt')
	if not my_file.is_file():
    		os.startfile('CreateQT.exe')
	pass

	file = open('tree.txt', 'r');
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

		gdict[(x,y)] = {(x+l,y+w):np.sqrt(l**2 + w**2)}
		for j in range(i,i+num_adjacent*4,4):
			x1 = data[j]
			y1 = data[j+1]
			l1 = data[j+2]
			w1 = data[j+3]

			gdict[(x,y)][(x1,y1)] = distance((x,y),(x1,y1))

		pass


		i += num_adjacent*4

	pass

	#newdict = {}

	# for keys1 in gdict:
	# 	newdict[keys1] = {}
	# 	for keys2 in gdict[keys1]:
	# 		if keys2 in gdict.keys():
	# 			print(keys2)
	# 			newdict[keys1][keys2] = gdict[keys1][keys2]
	# 		else:
	# 			print(keys2)
	# 		pass
	# 	pass
	# pass


	return gdict

pass


def parseMap():
	file = open('map.txt', 'r');
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
	return min(gdict.keys(), key=lambda x: distance(x, p))
pass


if __name__ == "__main__":
	os.chdir(os.path.dirname(os.path.abspath(__file__)))
	main()
pass
