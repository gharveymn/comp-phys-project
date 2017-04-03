import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
import matplotlib.ticker as mt
from scipy import interpolate

def main():
	
	fig1 = plt.figure(1)
	ax = fig1.gca(projection='3d')
	
	mngr = plt.get_current_fig_manager()
	geom = mngr.window.geometry()
	x, y, dx, dy = geom.getRect()
	mngr.window.setGeometry(100, 100, dx, dy)
	# Provides x and y coordinates associated with one random z coordinate
	x = np.linspace(0, 1, 5)
	y = np.linspace(0, 1, 5)
	x, y = np.meshgrid(x, y)
	
	z = np.random.rand(x.size).reshape(x.shape)
	z /= z.sum()
	
	f = interpolate.interp2d(x, y, z, 'cubic')
	x2 = np.linspace(0, 1, 1000)
	y2 = np.linspace(0, 1, 1000)
	z2 = f(x2, y2)
	z2 /= z2.sum()
	x2, y2 = np.meshgrid(x2, y2)
	
	surf = ax.plot_surface(x2, y2, z2, cmap=cm.coolwarm, linewidth=0, antialiased=True)
	ax.set_zlim(0, 2*z2.max())
	ax.zaxis.set_major_locator(mt.LinearLocator(10))
	ax.zaxis.set_major_formatter(mt.NullFormatter())
	
	cbar = fig1.colorbar(surf, shrink=0.5, aspect=5)
	plt.setp(cbar.ax.get_yticklabels(), visible=False)
	
	fig2 = plt.figure(2)
	plot_heatmap(fig2, z2)
	
	plt.show()


pass


def plot_heatmap(fig2, Z):
	from mpl_toolkits.axes_grid1 \
		import SubplotDivider, LocatableAxes, Size
	
	Z = np.flipud(Z)
	
	divider = SubplotDivider(fig2, 1, 1, 1, aspect=True)
	
	# axes for image
	ax = LocatableAxes(fig2, divider.get_position())
	
	# axes for colorbar
	ax_cb = LocatableAxes(fig2, divider.get_position())
	
	h = [Size.AxesX(ax),  # main axes
		Size.Fixed(0.05),  # padding, 0.1 inch
		Size.Fixed(0.2),  # colorbar, 0.3 inch
		]
	
	v = [Size.AxesY(ax)]
	
	divider.set_horizontal(h)
	divider.set_vertical(v)
	
	ax.set_axes_locator(divider.new_locator(nx=0, ny=0))
	ax_cb.set_axes_locator(divider.new_locator(nx=2, ny=0))
	
	fig2.add_axes(ax)
	fig2.add_axes(ax_cb)
	
	ax_cb.axis["left"].toggle(all=False)
	ax_cb.axis["right"].toggle(ticks=True)
	
	im = ax.imshow(Z,cmap=cm.coolwarm, extent=(0, 1, 0, 1), interpolation="nearest")
	plt.colorbar(im, cax=ax_cb)
	plt.setp(ax_cb.get_yticklabels(), visible=False)
	
	mngr = plt.get_current_fig_manager()
	geom = mngr.window.geometry()
	x, y, dx, dy = geom.getRect()
	mngr.window.setGeometry(dx + 200, 100, dx, dy)


pass

if __name__ == "__main__":
	main()
pass
