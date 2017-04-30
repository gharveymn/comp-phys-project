import os
import time
import sys
import matplotlib.pyplot as plt
import matplotlib.lines as lines
import random
import warnings
warnings.filterwarnings("ignore",".*GUI is implemented.*")

def runDemo():

	print("\n")
	animatedprint("Hi, welcome to our short demo.")
	printsleep(1.0)
	animatedprint("Here we'll be doing a recompile and quick runthrough of all of our code.")
	animatedprint("---------------------------------------------------------------------------\n")
	printsleep(3.0)

	mapfile = "map2.txt"
	qt_threshold = 5
	actual_to_max_children_ratio = 0.75
	max_num_adjacent = 30

	os.chdir(os.path.dirname(os.path.abspath(__file__)))
	os.chdir("QTData")
	animatedprint("We'll start by compiling CreateQT.exe...")
	os.system("gcc -std=c99 -o CreateQT CreateQT.c")
	print("Done!\n")
	printsleep(2.0)
	animatedprint("Now we create the quadtree of %s with parameters"%mapfile)
	print("\tqt_threshold = %d"%qt_threshold)
	printsleep(0.1)
	print("\tactual_to_max_children_ratio = %f"%actual_to_max_children_ratio)
	printsleep(0.1)
	print("\tmax_num_adjacent = %d"%max_num_adjacent)
	printsleep(2.0)
	os.system("CreateQT.exe {0} {1} {2} {3}".format(mapfile,qt_threshold,actual_to_max_children_ratio,max_num_adjacent))
	print("Done!\n")
	printsleep(2.0)
	os.chdir("..")

	animatedprint("Now we'll find the shortest path between all nodes...")
	printsleep(2.0)
	import QTPathFinder as qt
	pack,pdict = qt.findAllPaths()
	mngr = plt.get_current_fig_manager()
	geom = mngr.window.geometry()
	x, y, dx, dy = geom.getRect()
	mngr.window.setGeometry(100, 100, dx, dy)
	plt.show()
	plt.pause(0.5)
	print("Done!\n")
	printsleep(1.0)

	animatedprint("Now let's find some paths. Bring up the figure if you don't already see it.")
	import DataParser as dp
	import HelperMethods as hm
	#To get legal points
	limits, rectVects = dp.parseQT(justTheRectangles=True)

	xrng = limits[1]-limits[0]
	yrng = limits[3]-limits[2]
	numPaths = 150

	startPoints = [(xrng*(random.random()),yrng*(random.random())) for i in range(numPaths)]
	endPoints = [(xrng*(random.random()),yrng*(random.random())) for i in range(numPaths)]
	removal = []
	for p in startPoints:
		if hm.isInsideRect(p,rectVects):
			removal.append(p)
		pass
	pass
	for r in removal:
		startPoints.remove(r)
	pass

	removal = []
	for p in endPoints:
		if hm.isInsideRect(p,rectVects):
			removal.append(p)
		pass
	pass
	for r in removal:
		endPoints.remove(r)
	pass
	printsleep(3.0)
	animatedprint("Begin plotting...")
	printsleep(1.0)

	demoPoints = dict(zip(startPoints,endPoints))

	line = lines.Line2D([], [], lw=2, c='red')
	ax = pack[2]
	ax.add_line(line)

	for s,e in demoPoints.items():
		line = qt.plotPathWithResults(pack,pdict,s,e,line)
		print("Start: ({:f},{:f}) | End: ({:f},{:f})".format(s[0],s[1],e[0],e[1]))
		sys.stdout.flush()
		plt.show()
		plt.pause(0.001)
	pass
	print("...Done!")
	printsleep(1.0)

	animatedprint("\nThis ends the demo. Thanks for watching!")
	plt.pause(5.0)

pass


def animatedprint(str):
	strArr = list(str)
	for i in range(len(strArr)):
		print(strArr[i], end="")
		printsleep(0.01)
	pass
	print()
pass

def printsleep(sleeptime):
	sys.stdout.flush()
	time.sleep(sleeptime)
pass


if __name__ == "__main__":
	runDemo()
pass