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

Alpha version is released!

The following features are implemented in the alpha version.

- AOI hit counter
- Heatmap using Gauss Sum / Kernel Density Estimation
- Simple IVT fixation filter

The alpha release is only for Linux x86_64.

Documentation is in `/docs/ganca0.0_alpha.md`.

Distribution is in the build tree `build/python/dist/ganca-0.0.1a0-py3-none-any.whl`.

The alpha release is a minimal release for testing and evaluation purposes only and should not be used for production.

The CI strategy is not yet decided, so there might be drastic changes in the beta release.

I have a rough goal of releasing the beta version somewhere in spring 2024, but I can't promise anything.

Beta version and later versions will be released on PyPI and CRAN.

The following features are considered to be implemented in the beta version.

- Practical fixation filter
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

## How to build

As in any CMake projects, run the following commands from the root directory of this repository. Change the build directory (/build) as you like.

```bash
cmake -S. -Bbuild # only C++
cmake --build build
```

For building the Python package, run the following commands or toggle `BUILD_PYTHON` option in /CMakeLists.txt.

The target `python_package` is defined in /cmake/python.cmake.

```bash
cmake -S. -Bbuild -DBUILD_PYTHON=ON # C++ and Python
cmake --build build --target python_package -v # build only python
```

## Codemap

- AOIHit: AOI hit counter src directory
- FixationFilter: fixation filter src directory
- Heatmap: heatmap src directory
- Helper: helper src directory
- Gazepath: still under development
- python/setup.py.in: setup.py template for python package
- python_test: python test scripts, copied to build tree
- test: test scripts, currently not used
- test_data: test data, copied to build tree
- cmake: cmake scripts
- extern: git sub modules, used in /test
- docs: documentation
- CMakeLists.txt
- LICENSE
- README.md
- .gitignore
- .gitmodules

For each src directory (AOIHit, FixationFilter, Heatmap, Helper, Gazepath):

- "ModuleName"
  - include/"modulename"/"ModuleName".hpp: header file
  - src/"ModuleName".cpp: source file
  - python
    - "modulename".i: SWIG interface file
    - CMakeLists.txt: called from /cmake/python.cmake
  - tests
    - "modulename"_test.cpp: catch2 test script
    - CMakeLists.txt: called from ../CMakeLists.txt
  - CMakeLists.txt: called from /cmake/cpp.cmake

## Acknowledgement

This repository is based on [https://github.com/Mizux/cmake-swig](https://github.com/Mizux/cmake-swig).