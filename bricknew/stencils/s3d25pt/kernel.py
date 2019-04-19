from st.expr import Index, ConstRef
from st.grid import Grid

# Declare indices
i = Index(0)
j = Index(1)
k = Index(2)

# Declare grid
input = Grid("in", 3)
output = Grid("out", 3)
c = []
for cc in range(125):
    c.append(ConstRef('c[{}]'.format(cc)))

calc = c[ 0] * input(i    , j    , k    ) + c[ 1] * input(i - 4, j    , k    ) + c[ 2] * input(i - 3, j    , k    ) + c[ 3] * input(i - 2, j    , k    ) + c[ 4] * input(i - 1, j    , k    ) + c[ 5] * input(i + 1, j    , k    ) + c[ 6] * input(i + 2, j    , k    ) + c[ 7] * input(i + 3, j    , k    ) + c[ 8] * input(i + 4, j    , k    ) + c[ 9] * input(i    , j - 4, k    ) + c[10] * input(i    , j - 3, k    ) + c[11] * input(i    , j - 2, k    ) + c[12] * input(i    , j - 1, k    ) + c[13] * input(i    , j + 1, k    ) + c[14] * input(i    , j + 2, k    ) + c[15] * input(i    , j + 3, k    ) + c[16] * input(i    , j + 4, k    ) + c[17] * input(i    , j    , k - 4) + c[18] * input(i    , j    , k - 3) + c[19] * input(i    , j    , k - 2) + c[20] * input(i    , j    , k - 1) + c[21] * input(i    , j    , k + 1) + c[22] * input(i    , j    , k + 2) + c[23] * input(i    , j    , k + 3) + c[24] * input(i    , j    , k + 4)

output(i, j, k).assign(calc)

STENCIL = [output]
