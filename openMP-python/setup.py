from setuptools import Extension, setup
from Cython.Build import cythonize

ext_modules = [
    Extension(
        "main.pyx",
        ["main.pyx"],
        extra_compile_args=['-fopenmp'],
        extra_link_args=['-fopenmp'],
    ),
    Extension(
        "mandelbrot.pyx",
        ["mandelbrot.pyx"],
        extra_compile_args=['-fopenmp'],
        extra_link_args=['-fopenmp'],
    )
]

setup(
    name='mandelbrot-openmp',
    ext_modules=cythonize(ext_modules),
)