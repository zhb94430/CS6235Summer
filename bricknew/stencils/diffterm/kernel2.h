// Segment 4
bElem uxx = (-2.847 * q_1(i,j,k) + 1.6 * (q_1(i + 1, j, k) + q_1(i - 1, j, k)) +
       -0.2 * (q_1(i + 2, j, k) + q_1(i - 2, j, k)) +
       0.0253 * (q_1(i + 3, j, k) + q_1(i - 3, j, k)) +
       -0.0017 * (q_1(i + 4, j, k) + q_1(i - 4, j, k))) *
      (dxinv0 * dxinv0);
bElem uyy = (-2.847 * q_1(i,j,k) + 1.6 * (q_1(i, j + 1, k) + q_1(i, j - 1, k)) +
       -0.2 * (q_1(i, j + 2, k) + q_1(i, j - 2, k)) +
       0.0253 * (q_1(i, j + 3, k) + q_1(i, j - 3, k)) +
       -0.0017 * (q_1(i, j + 4, k) + q_1(i, j - 4, k))) *
      (dxinv1 * dxinv1);
bElem uzz = (-2.847 * q_1(i,j,k) + 1.6 * (q_1(i, j, k + 1) + q_1(i, j, k - 1)) +
       -0.2 * (q_1(i, j, k + 2) + q_1(i, j, k - 2)) +
       0.0253 * (q_1(i, j, k + 3) + q_1(i, j, k - 3)) +
       -0.0017 * (q_1(i, j, k + 4) + q_1(i, j, k - 4))) *
      (dxinv2 * dxinv2);
bElem vyx = (0.8 * (vy(i + 1, j, k) - vy(i - 1, j, k)) +
       -0.2 * (vy(i + 2, j, k) - vy(i - 2, j, k)) +
       0.038 * (vy(i + 3, j, k) - vy(i - 3, j, k)) +
       -0.0035 * (vy(i + 4, j, k) - vy(i - 4, j, k))) *
      dxinv0;
bElem wzx = (0.8 * (wz(i + 1, j, k) - wz(i - 1, j, k)) +
       -0.2 * (wz(i + 2, j, k) - wz(i - 2, j, k)) +
       0.038 * (wz(i + 3, j, k) - wz(i - 3, j, k)) +
       -0.0035 * (wz(i + 4, j, k) - wz(i - 4, j, k))) *
      dxinv0;
diffflux1(i,j,k) =
    0.3311 * (1.333 * uxx + uyy + uzz + 0.333 * (vyx + wzx));
