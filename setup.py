from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

setup(
    name = 'ela',
    version = '1.0',
    author = 'Shreyash Sharma',
    # The ext modules interface the cpp code with the python one:
    ext_modules=[
        Extension("ela",
            sources=["elawrapper.pyx", "ela_c.cpp"], # Note, you can link against a c++ library instead of including the source
            include_dirs=[".","source" , "/usr/local/include/opencv", "/usr/local/include"],
            language="c++",
            library_dirs=['/usr/local/lib', 'source'],
            libraries=['opencv_core'])
    ],
    cmdclass = {'build_ext': build_ext},
)
