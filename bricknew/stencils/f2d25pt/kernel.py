from st.expr import Index, ConstRef
from st.grid import Grid

# Declare indices
i = Index(0)
j = Index(1)

# Declare grid
input = Grid("in", 2)
output = Grid("out", 2)
c = []
for cc in range(25):
    c.append(ConstRef('c[{}]'.format(cc)))

calc = c[ 0] * input(i - 2, j - 2) + c[ 1] * input(i - 1, j - 2) + c[ 2] * input(i    , j - 2) + c[ 3] * input(i + 1, j - 2) + c[ 4] * input(i + 2, j - 2) + c[ 5] * input(i - 2, j - 1) + c[ 6] * input(i - 1, j - 1) + c[ 7] * input(i    , j - 1) + c[ 8] * input(i + 1, j - 1) + c[ 9] * input(i + 2, j - 1) + c[10] * input(i - 2, j    ) + c[11] * input(i - 1, j    ) + c[12] * input(i    , j    ) + c[13] * input(i + 1, j    ) + c[14] * input(i + 2, j    ) + c[15] * input(i - 2, j + 1) + c[16] * input(i - 1, j + 1) + c[17] * input(i    , j + 1) + c[18] * input(i + 1, j + 1) + c[19] * input(i + 2, j + 1) + c[20] * input(i - 2, j + 2) + c[21] * input(i - 1, j + 2) + c[22] * input(i    , j + 2) + c[23] * input(i + 1, j + 2) + c[24] * input(i + 2, j + 2)

output(i, j).assign(calc)

STENCIL = [output]
