#!/bin/bash

arch=p100
tilek=8
tilej=8
tilei=8
fold='4\\,8'

mypath=$(realpath $0)
mypath=$(dirname "$mypath")

echo "Running for $arch using ($tilek, $tilej, $tilei) and fold ($fold)"

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
    make clean all ARCH=$arch "BFOLD=$fold" "EXOPT=-DTILEK=$tilek -DTILEJ=$tilej -DTILEI=$tilei -O2" 2&>/dev/null
    make run ARCH=$arch
    popd > /dev/null
done
