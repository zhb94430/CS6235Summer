from st.expr import Index, ConstRef
from st.grid import Grid

# Declare indices
i = Index(0)
j = Index(1)

# Declare grid
input = Grid("in", 2)
output = Grid("out", 2)
c = []
for cc in range(17):
    c.append(ConstRef('c[{}]'.format(cc)))

calc = c[ 0] * input(i    , j    ) + c[ 1] * input(i - 4, j    ) + c[ 2] * input(i - 3, j    ) + c[ 3] * input(i - 2, j    ) + c[ 4] * input(i - 1, j    ) + c[ 5] * input(i + 1, j    ) + c[ 6] * input(i + 2, j    ) + c[ 7] * input(i + 3, j    ) + c[ 8] * input(i + 4, j    ) + c[ 9] * input(i    , j - 4) + c[10] * input(i    , j - 3) + c[11] * input(i    , j - 2) + c[12] * input(i    , j - 1) + c[13] * input(i    , j + 1) + c[14] * input(i    , j + 2) + c[15] * input(i    , j + 3) + c[16] * input(i    , j + 4)

output(i, j).assign(calc)

STENCIL = [output]
