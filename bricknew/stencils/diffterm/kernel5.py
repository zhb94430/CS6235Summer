from st.expr import Index, ConstRef
from st.grid import Grid
from kernel import *

txx = (-2.847 * q_5(i,j,k) + 1.6 * (q_5(i + 1, j, k) + q_5(i - 1, j, k)) + -0.2 * (q_5(i + 2, j, k) + q_5(i - 2, j, k)) + 0.0253 * (q_5(i + 3, j, k) + q_5(i - 3, j, k)) + -0.0017 * (q_5(i + 4, j, k) + q_5(i - 4, j, k))) * (dxinv0 * dxinv0)
tyy = (-2.847 * q_5(i,j,k) + 1.6 * (q_5(i, j + 1, k) + q_5(i, j - 1, k)) + -0.2 * (q_5(i, j + 2, k) + q_5(i, j - 2, k)) + 0.0253 * (q_5(i, j + 3, k) + q_5(i, j - 3, k)) + -0.0017 * (q_5(i, j + 4, k) + q_5(i, j - 4, k))) * (dxinv1 * dxinv1)
tzz = (-2.847 * q_5(i,j,k) + 1.6 * (q_5(i, j, k + 1) + q_5(i, j, k - 1)) + -0.2 * (q_5(i, j, k + 2) + q_5(i, j, k - 2)) + 0.0253 * (q_5(i, j, k + 3) + q_5(i, j, k - 3)) + -0.0017 * (q_5(i, j, k + 4) + q_5(i, j, k - 4))) * (dxinv2 * dxinv2)
divu = 0.666 * (ux(i,j,k) + vy(i,j,k) + wz(i,j,k))
tauxx = 2e0 * ux(i,j,k) - divu
tauyy = 2e0 * vy(i,j,k) - divu
tauzz = 2e0 * wz(i,j,k) - divu
tauxy = uy(i,j,k) + vx(i,j,k)
tauxz = uz(i,j,k) + wx(i,j,k)
tauyz = vz(i,j,k) + wy(i,j,k)
mechwork = tauxx * ux(i,j,k) + tauyy * vy(i,j,k) + tauzz * wz(i,j,k) + (tauxy * tauxy) + (tauxz * tauxz) + (tauyz * tauyz)
mechwork = 0.3311 * mechwork + diffflux1(i,j,k) * q_1(i,j,k) + diffflux2(i,j,k) * q_2(i,j,k) + diffflux3(i,j,k) * q_3(i,j,k)
diffflux4(i,j,k).assign(0.7112 * (txx + tyy + tzz) + mechwork)

STENCIL = [diffflux4]
