// Segment 1
ux(i,j,k) = (0.8 * (q_1(i + 1, j, k) - q_1(i - 1, j, k)) +
               -0.2 * (q_1(i + 2, j, k) - q_1(i - 2, j, k)) +
               0.038 * (q_1(i + 3, j, k) - q_1(i - 3, j, k)) +
               -0.0035 * (q_1(i + 4, j, k) - q_1(i - 4, j, k))) *
              dxinv0;
vx(i,j,k) = (0.8 * (q_2(i + 1, j, k) - q_2(i - 1, j, k)) +
               -0.2 * (q_2(i + 2, j, k) - q_2(i - 2, j, k)) +
               0.038 * (q_2(i + 3, j, k) - q_2(i - 3, j, k)) +
               -0.0035 * (q_2(i + 4, j, k) - q_2(i - 4, j, k))) *
              dxinv0;
wx(i,j,k) = (0.8 * (q_3(i + 1, j, k) - q_3(i - 1, j, k)) +
               -0.2 * (q_3(i + 2, j, k) - q_3(i - 2, j, k)) +
               0.038 * (q_3(i + 3, j, k) - q_3(i - 3, j, k)) +
               -0.0035 * (q_3(i + 4, j, k) - q_3(i - 4, j, k))) *
              dxinv0;
// Segment 2
uy(i,j,k) = (0.8 * (q_1(i, j + 1, k) - q_1(i, j - 1, k)) +
               -0.2 * (q_1(i, j + 2, k) - q_1(i, j - 2, k)) +
               0.038 * (q_1(i, j + 3, k) - q_1(i, j - 3, k)) +
               -0.0035 * (q_1(i, j + 4, k) - q_1(i, j - 4, k))) *
              dxinv1;
vy(i,j,k) = (0.8 * (q_2(i, j + 1, k) - q_2(i, j - 1, k)) +
               -0.2 * (q_2(i, j + 2, k) - q_2(i, j - 2, k)) +
               0.038 * (q_2(i, j + 3, k) - q_2(i, j - 3, k)) +
               -0.0035 * (q_2(i, j + 4, k) - q_2(i, j - 4, k))) *
              dxinv1;
wy(i,j,k) = (0.8 * (q_3(i, j + 1, k) - q_3(i, j - 1, k)) +
               -0.2 * (q_3(i, j + 2, k) - q_3(i, j - 2, k)) +
               0.038 * (q_3(i, j + 3, k) - q_3(i, j - 3, k)) +
               -0.0035 * (q_3(i, j + 4, k) - q_3(i, j - 4, k))) *
              dxinv1;
// Segment 3
uz(i,j,k) = (0.8 * (q_1(i, j, k + 1) - q_1(i, j, k - 1)) +
               -0.2 * (q_1(i, j, k + 2) - q_1(i, j, k - 2)) +
               0.038 * (q_1(i, j, k + 3) - q_1(i, j, k - 3)) +
               -0.0035 * (q_1(i, j, k + 4) - q_1(i, j, k - 4))) *
              dxinv2;
vz(i,j,k) = (0.8 * (q_2(i, j, k + 1) - q_2(i, j, k - 1)) +
               -0.2 * (q_2(i, j, k + 2) - q_2(i, j, k - 2)) +
               0.038 * (q_2(i, j, k + 3) - q_2(i, j, k - 3)) +
               -0.0035 * (q_2(i, j, k + 4) - q_2(i, j, k - 4))) *
              dxinv2;
wz(i,j,k) = (0.8 * (q_3(i, j, k + 1) - q_3(i, j, k - 1)) +
               -0.2 * (q_3(i, j, k + 2) - q_3(i, j, k - 2)) +
               0.038 * (q_3(i, j, k + 3) - q_3(i, j, k - 3)) +
               -0.0035 * (q_3(i, j, k + 4) - q_3(i, j, k - 4))) *
              dxinv2;
