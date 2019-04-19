#!/bin/bash

pushd ../..
export PATH=$(pwd):$PATH
popd

module load cuda/10.0
module load python/3.6.3
module load gcc/6.4.0

make all ARCH=gpu
