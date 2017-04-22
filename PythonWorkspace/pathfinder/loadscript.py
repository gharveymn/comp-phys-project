import QTPathFinder as qt
import importlib as il
import DataParser as dp
import DescendingSelection as ds
import HelperMethods as hm
import PathOptimization as po
import Plotting as pl

def get():
	'''USAGE:
		Use the following commands so you can reload each module

		>>> from importlib import reload
		>>> import loadscript
		>>> qt,il,dp,ds,hm,po,pl = loadscript.get()

(for copy paste)
from importlib import reload
import loadscript
qt,il,dp,ds,hm,po,pl = loadscript.get()

		Then run as usual. For example, if you make changes in DataParser, use the command

		>>> reload(dp)

		and then run as usual.
	'''

	return qt,il,dp,ds,hm,po,pl
pass