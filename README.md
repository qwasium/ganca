# ganca

**STILL UNDER DEVELOPMENT**

This project is still under development.

Thare can be any changes in the future.

This project is public in order to make the development process transparent.

No pull requests will be accepted until the beta version is released.

## What is ganca?

ganca is a simple and fast eye-tracking data analysis tool.

The aim is to create a cross-platform, fast low-level library for eye-tracking data analysis targeting Python and R, and MATLAB if possible.

## When is it coming?

Alpha version is planned to be released in Jan. 2024, but can be delayed.

The following features are planned to be implemented in the alpha version.

- Heatmap using Kernel Density Estimation
- Heatmap using Gauss Sum
- Gazepath plot()
- Simple IAT fixation filter
- Simple IVT fixation filter


I have a rough goal of releasing the beta version somewhere in spring 2024, but I can't promise anything.

Beta version and later versions will be released on PyPI and CRAN.

The following features are considered to be implemented in the beta version.

- Heatmap using particle filter
- parallel processing


## MATLAB?

I'm not planning to release a built version for MATLAB.

Users will need to build the package by themselves.

My MATLAB license will expire in March 2024, so I can't support it.

## Dependencies

The following dependencies are required to build the package. If CMake can't find them, you might need to provide the path in `CMakeLists.txt`.

The versions shown below are of the tested environment. Tested on Ubuntu 22.04 only.

- CMake 3.22.1
- SWIG 4.0.2
- Python 3.10.
- OpenCV 4.8.1: [you might need to edit cmake script if build fails](/cmake/opencv.cmake)

## How to build

As in any CMake projects, run the following commands from the root directory of this repository. Change the build directory (/build) as you like.

```bash
cmake -S. -Bbuild
cmake --build build
```

For building the Python package, run the following commands or toggle `BUILD_PYTHON` option in /CMakeLists.txt.

The target `python_package` is defined in /cmake/python.cmake.

```bash
cmake -S. -Bbuild -DBUILD_PYTHON=ON
cmake --build build --target python_package -v
```

## Codemap



## Acknowledgement

This repository is based on [https://github.com/Mizux/cmake-swig](https://github.com/Mizux/cmake-swig).