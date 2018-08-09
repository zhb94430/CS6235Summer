# Brick layout for C++

# How to

## Directory

Most of the code in this directory are helper & library code.

* For actual stencil computation example look at `src/stencil_example.cpp`:
    * `naive_stencil` would be the code that get inputted into CHiLL
* `main.cpp` contains some sort of setup code to use the accomanying data structures
    * The interface is flexible and any hooks can be used as long as the same amount of information is passed to the function that calculates stencils

## Building & running

### Using CMake

CMake is chosen for IDE(CLion) support

***To Build and Run:***

1. Create a build directory in source tree `mkdir build`
2. Create configuration `cd build && cmake .. -DCMAKE_CXX_COMPILER=icpc -DCMAKE_BUILD_TYPE=Release`
3. Build and run: `make test-all`

***For different kind of test:***

Add `-DEXAMPLE=(stencil/stream)` to the configuration step.

### Using make

Makefile is used to do quick compile and test.

* To build: type `make` in the root directory
* To build and run: `make test-all`
* For a different kind of test:
    1. `make clean`
    2. `make EXAMPLE=stream test-all`
