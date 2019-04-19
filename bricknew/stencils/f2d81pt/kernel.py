from st.expr import Index, ConstRef
from st.grid import Grid

# Declare indices
i = Index(0)
j = Index(1)

# Declare grid
input = Grid("in", 2)
output = Grid("out", 2)
c = []
for cc in range(81):
    c.append(ConstRef('c[{}]'.format(cc)))

calc = c[ 0] * input(i - 4, j - 4) + c[ 1] * input(i - 3, j - 4) + c[ 2] * input(i - 2, j - 4) + c[ 3] * input(i - 1, j - 4) + c[ 4] * input(i    , j - 4) + c[ 5] * input(i + 1, j - 4) + c[ 6] * input(i + 2, j - 4) + c[ 7] * input(i + 3, j - 4) + c[ 8] * input(i + 4, j - 4) + c[ 9] * input(i - 4, j - 3) + c[10] * input(i - 3, j - 3) + c[11] * input(i - 2, j - 3) + c[12] * input(i - 1, j - 3) + c[13] * input(i    , j - 3) + c[14] * input(i + 1, j - 3) + c[15] * input(i + 2, j - 3) + c[16] * input(i + 3, j - 3) + c[17] * input(i + 4, j - 3) + c[18] * input(i - 4, j - 2) + c[19] * input(i - 3, j - 2) + c[20] * input(i - 2, j - 2) + c[21] * input(i - 1, j - 2) + c[22] * input(i    , j - 2) + c[23] * input(i + 1, j - 2) + c[24] * input(i + 2, j - 2) + c[25] * input(i + 3, j - 2) + c[26] * input(i + 4, j - 2) + c[27] * input(i - 4, j - 1) + c[28] * input(i - 3, j - 1) + c[29] * input(i - 2, j - 1) + c[30] * input(i - 1, j - 1) + c[31] * input(i    , j - 1) + c[32] * input(i + 1, j - 1) + c[33] * input(i + 2, j - 1) + c[34] * input(i + 3, j - 1) + c[35] * input(i + 4, j - 1) + c[36] * input(i - 4, j    ) + c[37] * input(i - 3, j    ) + c[38] * input(i - 2, j    ) + c[39] * input(i - 1, j    ) + c[40] * input(i    , j    ) + c[41] * input(i + 1, j    ) + c[42] * input(i + 2, j    ) + c[43] * input(i + 3, j    ) + c[44] * input(i + 4, j    ) + c[45] * input(i - 4, j + 1) + c[46] * input(i - 3, j + 1) + c[47] * input(i - 2, j + 1) + c[48] * input(i - 1, j + 1) + c[49] * input(i    , j + 1) + c[50] * input(i + 1, j + 1) + c[51] * input(i + 2, j + 1) + c[52] * input(i + 3, j + 1) + c[53] * input(i + 4, j + 1) + c[54] * input(i - 4, j + 2) + c[55] * input(i - 3, j + 2) + c[56] * input(i - 2, j + 2) + c[57] * input(i - 1, j + 2) + c[58] * input(i    , j + 2) + c[59] * input(i + 1, j + 2) + c[60] * input(i + 2, j + 2) + c[61] * input(i + 3, j + 2) + c[62] * input(i + 4, j + 2) + c[63] * input(i - 4, j + 3) + c[64] * input(i - 3, j + 3) + c[65] * input(i - 2, j + 3) + c[66] * input(i - 1, j + 3) + c[67] * input(i    , j + 3) + c[68] * input(i + 1, j + 3) + c[69] * input(i + 2, j + 3) + c[70] * input(i + 3, j + 3) + c[71] * input(i + 4, j + 3) + c[72] * input(i - 4, j + 4) + c[73] * input(i - 3, j + 4) + c[74] * input(i - 2, j + 4) + c[75] * input(i - 1, j + 4) + c[76] * input(i    , j + 4) + c[77] * input(i + 1, j + 4) + c[78] * input(i + 2, j + 4) + c[79] * input(i + 3, j + 4) + c[80] * input(i + 4, j + 4);

output(i, j).assign(calc)

STENCIL = [output]
