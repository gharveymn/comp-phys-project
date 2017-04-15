from distutils.core import setup
from Cython.Build import cythonize

#This doesn't actually work on my machine...
setup(
  name = 'pathfinder',
  ext_modules = cythonize("*.pyx"),
)