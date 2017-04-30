import PathOptimization as po


def findPaths(pack, pdict, lock, dynamicPaths, startPoints, endPoints):
	gdict = pack[0]
	for startPoint in startPoints:
		pdict[startPoint] = {}
		for endPoint in endPoints:
			if endPoint != startPoint:
				sp = po.dynamicDijkstra(gdict, lock, startPoint, endPoint, dynamicPaths, startPoint, visited=[],
								    distances={}, predecessors={})
				path = sp[1]
				pdict[startPoint][endPoint] = path
				# print("bye from {0}".format(th.get_ident()))
			pass
		pass
	pass


pass
