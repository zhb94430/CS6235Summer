from st.expr import Index, ConstRef
from st.grid import Grid
from kernel import *

wxx = (-2.847 * q_3(i,j,k) + 1.6 * (q_3(i + 1, j, k) + q_3(i - 1, j, k)) + -0.2 * (q_3(i + 2, j, k) + q_3(i - 2, j, k)) + 0.0253 * (q_3(i + 3, j, k) + q_3(i - 3, j, k)) + -0.0017 * (q_3(i + 4, j, k) + q_3(i - 4, j, k))) * (dxinv0 * dxinv0)
wyy = (-2.847 * q_3(i,j,k) + 1.6 * (q_3(i, j + 1, k) + q_3(i, j - 1, k)) + -0.2 * (q_3(i, j + 2, k) + q_3(i, j - 2, k)) + 0.0253 * (q_3(i, j + 3, k) + q_3(i, j - 3, k)) + -0.0017 * (q_3(i, j + 4, k) + q_3(i, j - 4, k))) * (dxinv1 * dxinv1)
wzz = (-2.847 * q_3(i,j,k) + 1.6 * (q_3(i, j, k + 1) + q_3(i, j, k - 1)) + -0.2 * (q_3(i, j, k + 2) + q_3(i, j, k - 2)) + 0.0253 * (q_3(i, j, k + 3) + q_3(i, j, k - 3)) + -0.0017 * (q_3(i, j, k + 4) + q_3(i, j, k - 4))) * (dxinv2 * dxinv2)
uxz = (0.8 * (ux(i, j, k + 1) - ux(i, j, k - 1)) + -0.2 * (ux(i, j, k + 2) - ux(i, j, k - 2)) + 0.038 * (ux(i, j, k + 3) - ux(i, j, k - 3)) + -0.0035 * (ux(i, j, k + 4) - ux(i, j, k - 4))) * dxinv2
vyz = (0.8 * (vy(i, j, k + 1) - vy(i, j, k - 1)) + -0.2 * (vy(i, j, k + 2) - vy(i, j, k - 2)) + 0.038 * (vy(i, j, k + 3) - vy(i, j, k - 3)) + -0.0035 * (vy(i, j, k + 4) - vy(i, j, k - 4))) * dxinv2
diffflux3(i,j,k).assign(0.3311 * (wxx + wyy + 1.333 * wzz + 0.333 * (uxz + vyz)))

STENCIL = [diffflux3]
