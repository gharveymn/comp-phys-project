# comp-phys-project
PHYS 4250 project repository

The directory "Quad Tree Implementation" contains C code for generation of quadtrees based on the map files. That data is stored in an adjacency list that is tree.txt. The quadtree generation allows for adjustment of parameters with some nice barriers for protection from memory overflow.

For \*reasons\* we mirror this code in "PythonWorkspace/pathfinder/QTData". Symbolic links would probably be a good idea (or just directly linking it), but I'm not sure how to set that up on Windows.

Python files are located in "PythonWorkspace" wherein "pathfinder" is the operating folder (pathfinder27 was for some proof of concept code in Python 2.7). There are two points of entry in QTPathFinder --- one that finds the shortest path between two points, and another that does the same but for all points in a dynamic matter.