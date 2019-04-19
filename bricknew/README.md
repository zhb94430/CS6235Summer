# Artifact is now available!

## Organization

The artifact is split into 4 parts:

* The code generator: `./vecscatter` and `./st`
* The kernel code for all used stencils: `./stencils`
* The common library:
    * `./common`: brick library, common header definitions, utilities, timing code
    * `./schedules`: OpenMP/Loop schedule applied to 2D/3D stencils
* *run everything* script: `./runknl.sh` and `./runskx.sh` and `./runp100.sh`

## Software dependencies

* Intel Compiler and Intel OpenMP library, recommend:
    * \>= 2019
* GCC supporting *C++11*, recommend:
    * \>= 6.4.0
* CUDA, recommend:
    * \>=9
* Python 3.x: if not the default change the shebang in `./vecscatter`

## Just Run It!

Pick the corresponding *run everything* script for your platform and run it in this directory.

The script will iterate over all stencil directory and try to compile and run.

For KNL and Skylake-X, it will produce 3 numbers each corresponding the average iteration time of *baseline*, *tile*, and *brick*.

For P100, it will produce 2 numbers each corresponding to the average iteration time of *baseline*, and *brick*.

The dimension size for each platform is defined as `N=?` in `Makedef.X` for the corresponding platform in each stencil's directory.

## Acknowledgement

This research was supported by the Exascale Computing Project (17-SC-20-SC), a collaborative effort of the U.S. Department of Energy Office of Science and the National Nuclear Security Administration.
