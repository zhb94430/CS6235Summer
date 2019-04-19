#!/bin/bash

arch=knl
tilek=8
tilej=8
tilei=8
fold=8
opti=2

mypath=$(realpath $0)
mypath=$(dirname "$mypath")

echo "Running for $arch using ($tilek, $tilej, $tilei) and fold ($fold) with optimization level $opti"

export OMP_PLACES=cores
export KMP_HOT_TEAMS_MODE=1
export KMP_HOT_TEAMS_MAX_LEVEL=2
export KMP_HW_SUBSET=64c

# Add vecscatter to path
export PATH=$mypath:$PATH

for i in $mypath/stencils/*/; do
    if ! [ -f "$i/Makefile" ]; then
        continue
    fi
    r=$(cat $i/radius)
    if (( r > $tilek )); then
        continue
    fi
    echo $i
    pushd $i > /dev/null
    make clean all ARCH=$arch BFOLD=$fold "EXOPT=-DTILEK=$tilek -DTILEJ=$tilej -DTILEI=$tilei -O$opti" 2&>/dev/null
    make run ARCH=$arch
    popd > /dev/null
done
