from st.expr import Index, ConstRef
from st.grid import Grid

# Declare indices
i = Index(0)
j = Index(1)

# Declare grid
input = Grid("in", 2)
output = Grid("out", 2)
c = []
for cc in range(29):
    c.append(ConstRef('c[{}]'.format(cc)))

calc = c[ 0] * input(i    , j    ) + c[ 1] * input(i - 7, j    ) + c[ 2] * input(i - 6, j    ) + c[ 3] * input(i - 5, j    ) + c[ 4] * input(i - 4, j    ) + c[ 5] * input(i - 3, j    ) + c[ 6] * input(i - 2, j    ) + c[ 7] * input(i - 1, j    ) + c[ 8] * input(i + 1, j    ) + c[ 9] * input(i + 2, j    ) + c[10] * input(i + 3, j    ) + c[11] * input(i + 4, j    ) + c[12] * input(i + 5, j    ) + c[13] * input(i + 6, j    ) + c[14] * input(i + 7, j    ) + c[15] * input(i    , j - 7) + c[16] * input(i    , j - 6) + c[17] * input(i    , j - 5) + c[18] * input(i    , j - 4) + c[19] * input(i    , j - 3) + c[20] * input(i    , j - 2) + c[21] * input(i    , j - 1) + c[22] * input(i    , j + 1) + c[23] * input(i    , j + 2) + c[24] * input(i    , j + 3) + c[25] * input(i    , j + 4) + c[26] * input(i    , j + 5) + c[27] * input(i    , j + 6) + c[28] * input(i    , j + 7)

output(i, j).assign(calc)

STENCIL = [output]
