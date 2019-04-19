from st.expr import Index, ConstRef
from st.grid import Grid
from kernel import *

vxx = (-2.847 * q_2(i,j,k) + 1.6 * (q_2(i + 1, j, k) + q_2(i - 1, j, k)) + -0.2 * (q_2(i + 2, j, k) + q_2(i - 2, j, k)) + 0.0253 * (q_2(i + 3, j, k) + q_2(i - 3, j, k)) + -0.0017 * (q_2(i + 4, j, k) + q_2(i - 4, j, k))) * (dxinv0 * dxinv0)
vyy = (-2.847 * q_2(i,j,k) + 1.6 * (q_2(i, j + 1, k) + q_2(i, j - 1, k)) + -0.2 * (q_2(i, j + 2, k) + q_2(i, j - 2, k)) + 0.0253 * (q_2(i, j + 3, k) + q_2(i, j - 3, k)) + -0.0017 * (q_2(i, j + 4, k) + q_2(i, j - 4, k))) * (dxinv1 * dxinv1)
vzz = (-2.847 * q_2(i,j,k) + 1.6 * (q_2(i, j, k + 1) + q_2(i, j, k - 1)) + -0.2 * (q_2(i, j, k + 2) + q_2(i, j, k - 2)) + 0.0253 * (q_2(i, j, k + 3) + q_2(i, j, k - 3)) + -0.0017 * (q_2(i, j, k + 4) + q_2(i, j, k - 4))) * (dxinv2 * dxinv2)
uxy = (0.8 * (ux(i, j + 1, k) - ux(i, j - 1, k)) + -0.2 * (ux(i, j + 2, k) - ux(i, j - 2, k)) + 0.038 * (ux(i, j + 3, k) - ux(i, j - 3, k)) + -0.0035 * (ux(i, j + 4, k) - ux(i, j - 4, k))) * dxinv1
wzy = (0.8 * (wz(i, j + 1, k) - wz(i, j - 1, k)) + -0.2 * (wz(i, j + 2, k) - wz(i, j - 2, k)) + 0.038 * (wz(i, j + 3, k) - wz(i, j - 3, k)) + -0.0035 * (wz(i, j + 4, k) - wz(i, j - 4, k))) * dxinv1
diffflux2(i,j,k).assign(0.3311 * (vxx + 1.333 * vyy + vzz + 0.333 * (uxy + wzy)))

STENCIL = [diffflux2]
