from st.expr import Index, ConstRef
from st.grid import Grid

# Declare indices
i = Index(0)
j = Index(1)

# Declare grid
input = Grid("in", 2)
output = Grid("out", 2)
c = []
for cc in range(49):
    c.append(ConstRef('c[{}]'.format(cc)))

calc = c[ 0] * input(i - 3, j - 3) + c[ 1] * input(i - 2, j - 3) + c[ 2] * input(i - 1, j - 3) + c[ 3] * input(i    , j - 3) + c[ 4] * input(i + 1, j - 3) + c[ 5] * input(i + 2, j - 3) + c[ 6] * input(i + 3, j - 3) + c[ 7] * input(i - 3, j - 2) + c[ 8] * input(i - 2, j - 2) + c[ 9] * input(i - 1, j - 2) + c[10] * input(i    , j - 2) + c[11] * input(i + 1, j - 2) + c[12] * input(i + 2, j - 2) + c[13] * input(i + 3, j - 2) + c[14] * input(i - 3, j - 1) + c[15] * input(i - 2, j - 1) + c[16] * input(i - 1, j - 1) + c[17] * input(i    , j - 1) + c[18] * input(i + 1, j - 1) + c[19] * input(i + 2, j - 1) + c[20] * input(i + 3, j - 1) + c[21] * input(i - 3, j    ) + c[22] * input(i - 2, j    ) + c[23] * input(i - 1, j    ) + c[24] * input(i    , j    ) + c[25] * input(i + 1, j    ) + c[26] * input(i + 2, j    ) + c[27] * input(i + 3, j    ) + c[28] * input(i - 3, j + 1) + c[29] * input(i - 2, j + 1) + c[30] * input(i - 1, j + 1) + c[31] * input(i    , j + 1) + c[32] * input(i + 1, j + 1) + c[33] * input(i + 2, j + 1) + c[34] * input(i + 3, j + 1) + c[35] * input(i - 3, j + 2) + c[36] * input(i - 2, j + 2) + c[37] * input(i - 1, j + 2) + c[38] * input(i    , j + 2) + c[39] * input(i + 1, j + 2) + c[40] * input(i + 2, j + 2) + c[41] * input(i + 3, j + 2) + c[42] * input(i - 3, j + 3) + c[43] * input(i - 2, j + 3) + c[44] * input(i - 1, j + 3) + c[45] * input(i    , j + 3) + c[46] * input(i + 1, j + 3) + c[47] * input(i + 2, j + 3) + c[48] * input(i + 3, j + 3);

output(i, j).assign(calc)

STENCIL = [output]
