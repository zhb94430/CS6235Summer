#!/bin/bash

osize=$(objdump -t brick | grep "[0-9a-f]*\s\s*_ZZ4mainENKUlvE_clEv" | awk '{print $5}')
vsize=$(objdump -t vstile | grep "[0-9a-f]*\s\s*_ZZ4mainENKUlvE0_clEv" | awk '{print $5}')
bsize=$(objdump -t brick | grep "[0-9a-f]*\s\s*_ZZ4mainENKUlvE0_clEv" | awk '{print $5}')

echo Size comparison
python -c "print('{:.2f}kB, {:.2f}kB, {:.2f}kB'.format(0x${osize}/1024.0, 0x${vsize}/1024.0, 0x${bsize}/1024.0))"
