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

calc = c[ 0] * input(i    , j    ) + c[ 1] * input(i - 2, j    ) + c[ 2] * input(i - 1, j    ) + c[ 3] * input(i + 1, j    ) + c[ 4] * input(i + 2, j    ) + c[ 5] * input(i    , j - 2) + c[ 6] * input(i    , j - 1) + c[ 7] * input(i    , j + 1) + c[ 8] * input(i    , j + 2)

output(i, j).assign(calc)

STENCIL = [output]
