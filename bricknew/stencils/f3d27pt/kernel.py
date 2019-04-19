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
for cc in range(27):
    c.append(ConstRef('c[{}]'.format(cc)))

calc = c[ 0] * input(i - 1, j - 1, k - 1) + c[ 1] * input(i    , j - 1, k - 1) + c[ 2] * input(i + 1, j - 1, k - 1) + c[ 3] * input(i - 1, j    , k - 1) + c[ 4] * input(i    , j    , k - 1) + c[ 5] * input(i + 1, j    , k - 1) + c[ 6] * input(i - 1, j + 1, k - 1) + c[ 7] * input(i    , j + 1, k - 1) + c[ 8] * input(i + 1, j + 1, k - 1) + c[ 9] * input(i - 1, j - 1, k    ) + c[10] * input(i    , j - 1, k    ) + c[11] * input(i + 1, j - 1, k    ) + c[12] * input(i - 1, j    , k    ) + c[13] * input(i    , j    , k    ) + c[14] * input(i + 1, j    , k    ) + c[15] * input(i - 1, j + 1, k    ) + c[16] * input(i    , j + 1, k    ) + c[17] * input(i + 1, j + 1, k    ) + c[18] * input(i - 1, j - 1, k + 1) + c[19] * input(i    , j - 1, k + 1) + c[20] * input(i + 1, j - 1, k + 1) + c[21] * input(i - 1, j    , k + 1) + c[22] * input(i    , j    , k + 1) + c[23] * input(i + 1, j    , k + 1) + c[24] * input(i - 1, j + 1, k + 1) + c[25] * input(i    , j + 1, k + 1) + c[26] * input(i + 1, j + 1, k + 1)

output(i, j, k).assign(calc)

STENCIL = [output]
