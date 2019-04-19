from st.expr import Index, ConstRef
from st.grid import Grid

# Declare indices
i = Index(0)
j = Index(1)
k = Index(2)

# Declare grid
ux = Grid("ux", 3)
vx = Grid("vx", 3)
wx = Grid("wx", 3)

uy = Grid("uy", 3)
vy = Grid("vy", 3)
wy = Grid("wy", 3)

uz = Grid("uz", 3)
vz = Grid("vz", 3)
wz = Grid("wz", 3)

q_1 = Grid("q_1", 3)
q_2 = Grid("q_2", 3)
q_3 = Grid("q_3", 3)

q_5 = Grid("q_5", 3)

diffflux1 = Grid("diffflux1", 3)
diffflux2 = Grid("diffflux2", 3)
diffflux3 = Grid("diffflux3", 3)
diffflux4 = Grid("diffflux4", 3)

dxinv0 = ConstRef("dxinv0")
dxinv1 = ConstRef("dxinv1")
dxinv2 = ConstRef("dxinv2")
