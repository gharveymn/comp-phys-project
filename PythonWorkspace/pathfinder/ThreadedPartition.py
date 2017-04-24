import PathOptimization as po
import threading

# TODO:
# input:
# 	pack
# 	startpoints
#	endpoints
#
# get:
#	path for each startpoint and endpoint
#
# return:
#	dictionary of paths in form 
# {(startpoint1):{(endpoint1):[(pathpoint1),(pathpoint2),...], (endpoint2):{...}}, (startpoint2):{...}}

def findPaths(pack, pdict, lock, dynamicPaths, startPoints, endPoints):
    gdict = pack[0]
    for startPoint in startPoints:
        pdict[startPoint] = {}
        for endPoint in endPoints:
            sp = po.dynamicDijkstra(gdict, lock, startPoint, endPoint, dynamicPaths, startPoint, visited=[], distances={}, predecessors={})
            path = sp[1]
            pdict[startPoint][endPoint] = path
            #print("{0} in {1}\n".format(endPoint,threading.get_ident()))
        pass
    pass
pass

# def statusUpdate():
#     print(len(dynamicPaths))
#     threading.Timer(2,statusUpdate).start()
# pass
	