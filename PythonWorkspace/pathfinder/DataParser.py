import HelperMethods as Helper
from pathlib import Path as filePath
import os

#Make sure this runs in the locating file directory
os.chdir(os.path.dirname(os.path.abspath(__file__)))

def parseQT(justTheRectangles=False):
	my_file = filePath('QTData/tree.txt')
	if not my_file.is_file():
		print("QTData/tree.txt not created yet. Running QTData/CreateQT.exe ...")
		os.startfile('QTData/CreateQT.exe')
		print("Done.")
	pass

	try:
		file = open('QTData/tree.txt', 'r')
	except IOError:
		print("This shouldn't happen!")
		raise
	pass

	mapfile = file.readline().rstrip()

	#parse the rectangles barriers
	limits, rectVects = parseMap(mapfile)

	#Quick and dirty for the demo
	if justTheRectangles:
		return limits, rectVects
	pass


	data = [float(val) for val in file.read().strip().split()]

	gdict = {}

	limitRect = [[(limits[0],limits[2]),(limits[1],limits[2]),(limits[1],limits[3]), (limits[0],limits[3])]]

	i = 0
	while(i < len(data) - 4):
		x = data[i]
		y = data[i + 1]
		l = data[i + 2]
		w = data[i + 3]
		
		num_adjacent = int(data[i+4])
		i += 5

		if not Helper.isInsideRect((x,y),rectVects) and num_adjacent != 0:

			if (x,y) not in gdict:
				gdict[(x,y)] = {}
			pass

			for j in range(i,i+num_adjacent*4,4):
				x1 = data[j]
				y1 = data[j+1]
				# l1 = data[j+2]
				# w1 = data[j+3]

				if not Helper.isInsideRect((x1,y1),rectVects): #and not Helper.crossesBox((x,y),(x1,y1),rectVects):
					# dist = l1*l1 + w1*w1
					dist = Helper.distancesq((x,y),(x1,y1))
					gdict[(x,y)][(x1,y1)] = dist
					if (x1,y1) in gdict:
						gdict[(x1,y1)][(x,y)] = dist
					else:
						gdict[(x1,y1)] = {(x,y):dist}
					pass
				pass
			pass
		pass

		i += num_adjacent*4

	pass

	print("Number of nodes: {0}".format(len(gdict)))
	clean(gdict,rectVects)
	print("Number of nodes in cleaned graph: {0}".format(len(gdict)))

	return gdict,limits,rectVects

pass


def parseMap(mapfile):

	try:
		file = open('QTData/%s'%(mapfile), 'r')
	except IOError:
		print("QTData/{0} does not exist! Have you created it yet?".format(mapfile))
		raise
	pass

	data = [float(val) for val in file.read().strip().split()]
	
	x_min = data[0]
	x_max = data[1]
	y_min = data[2]
	y_max = data[3]
	limits = [x_min,x_max,y_min,y_max]
	num_squares = int(data[4])

	rectVects = [[]]*num_squares
	j = 0
	for i in range(5,len(data)-3,4):
		x = data[i]
		y = data[i+1]
		l = data[i+2]
		w = data[i+3]
		rectVects[j] = [(x,y),(x+l,y),(x+l,y+w),(x,y+w),(x,y)]
		j += 1
	pass

	return limits, rectVects
pass

def clean(gdict,rectVects):
	# TODO: Get rid of useless cleaning if possible

	removalSet = []

	#Make sure we don't have keys pointing to nothing
	for key in gdict:
		if not gdict[key]:
			removalSet += [key]
		pass
	pass

	for rm in removalSet:
		del gdict[rm]
	pass

	removalSet = set()

	#Likewise make sure this is true on the second level
	for secondLevel in gdict.values():
		for secondaryKey in secondLevel:
			if secondaryKey not in gdict:
				removalSet.add(secondaryKey)
			pass
		pass
	pass

	removeKeys(gdict,removalSet)

pass

def removeKeys(gdict,removalSet):
	for rm in removalSet:
		for secondLevel in gdict.values():
			secondLevel.pop(rm, None)
		pass
	pass
pass