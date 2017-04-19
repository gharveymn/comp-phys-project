import HelperMethods as Helper
from pathlib import Path as filePath
import os

#Make sure this runs in the locating file directory
os.chdir(os.path.dirname(os.path.abspath(__file__)))

def parseQT(limits, rectVects):

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

		if not Helper.isInsideRect((x,y),rectVects):

			if (x,y) not in gdict:
				gdict[(x,y)] = {}
			pass

			if Helper.isInsideRect((x+l,y),limitRect,edgesAreLava=False) and not Helper.isInsideRect((x+l,y),rectVects):
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

			if Helper.isInsideRect((x,y+w),limitRect,edgesAreLava=False) and not Helper.isInsideRect((x,y+w),rectVects):
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

				if not Helper.isInsideRect((x1,y1),rectVects):
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

	try:
		file = open('QTData/map2.txt', 'r')
	except IOError:
		print("QTData/map.txt does not exist! Have you created it yet?")
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