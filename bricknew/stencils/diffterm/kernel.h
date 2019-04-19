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
// Segment 4
uxx = (-2.847 * q_1(i,j,k) + 1.6 * (q_1(i + 1, j, k) + q_1(i - 1, j, k)) +
       -0.2 * (q_1(i + 2, j, k) + q_1(i - 2, j, k)) +
       0.0253 * (q_1(i + 3, j, k) + q_1(i - 3, j, k)) +
       -0.0017 * (q_1(i + 4, j, k) + q_1(i - 4, j, k))) *
      (dxinv0 * dxinv0);
uyy = (-2.847 * q_1(i,j,k) + 1.6 * (q_1(i, j + 1, k) + q_1(i, j - 1, k)) +
       -0.2 * (q_1(i, j + 2, k) + q_1(i, j - 2, k)) +
       0.0253 * (q_1(i, j + 3, k) + q_1(i, j - 3, k)) +
       -0.0017 * (q_1(i, j + 4, k) + q_1(i, j - 4, k))) *
      (dxinv1 * dxinv1);
uzz = (-2.847 * q_1(i,j,k) + 1.6 * (q_1(i, j, k + 1) + q_1(i, j, k - 1)) +
       -0.2 * (q_1(i, j, k + 2) + q_1(i, j, k - 2)) +
       0.0253 * (q_1(i, j, k + 3) + q_1(i, j, k - 3)) +
       -0.0017 * (q_1(i, j, k + 4) + q_1(i, j, k - 4))) *
      (dxinv2 * dxinv2);
vyx = (0.8 * (vy(i + 1, j, k) - vy(i - 1, j, k)) +
       -0.2 * (vy(i + 2, j, k) - vy(i - 2, j, k)) +
       0.038 * (vy(i + 3, j, k) - vy(i - 3, j, k)) +
       -0.0035 * (vy(i + 4, j, k) - vy(i - 4, j, k))) *
      dxinv0;
wzx = (0.8 * (wz(i + 1, j, k) - wz(i - 1, j, k)) +
       -0.2 * (wz(i + 2, j, k) - wz(i - 2, j, k)) +
       0.038 * (wz(i + 3, j, k) - wz(i - 3, j, k)) +
       -0.0035 * (wz(i + 4, j, k) - wz(i - 4, j, k))) *
      dxinv0;
diffflux1(i,j,k) =
    0.3311 * (1.333 * uxx + uyy + uzz + 0.333 * (vyx + wzx));
// Segment 5
vxx = (-2.847 * q_2(i,j,k) + 1.6 * (q_2(i + 1, j, k) + q_2(i - 1, j, k)) +
       -0.2 * (q_2(i + 2, j, k) + q_2(i - 2, j, k)) +
       0.0253 * (q_2(i + 3, j, k) + q_2(i - 3, j, k)) +
       -0.0017 * (q_2(i + 4, j, k) + q_2(i - 4, j, k))) *
      (dxinv0 * dxinv0);
vyy = (-2.847 * q_2(i,j,k) + 1.6 * (q_2(i, j + 1, k) + q_2(i, j - 1, k)) +
       -0.2 * (q_2(i, j + 2, k) + q_2(i, j - 2, k)) +
       0.0253 * (q_2(i, j + 3, k) + q_2(i, j - 3, k)) +
       -0.0017 * (q_2(i, j + 4, k) + q_2(i, j - 4, k))) *
      (dxinv1 * dxinv1);
vzz = (-2.847 * q_2(i,j,k) + 1.6 * (q_2(i, j, k + 1) + q_2(i, j, k - 1)) +
       -0.2 * (q_2(i, j, k + 2) + q_2(i, j, k - 2)) +
       0.0253 * (q_2(i, j, k + 3) + q_2(i, j, k - 3)) +
       -0.0017 * (q_2(i, j, k + 4) + q_2(i, j, k - 4))) *
      (dxinv2 * dxinv2);
uxy = (0.8 * (ux(i, j + 1, k) - ux(i, j - 1, k)) +
       -0.2 * (ux(i, j + 2, k) - ux(i, j - 2, k)) +
       0.038 * (ux(i, j + 3, k) - ux(i, j - 3, k)) +
       -0.0035 * (ux(i, j + 4, k) - ux(i, j - 4, k))) *
      dxinv1;
wzy = (0.8 * (wz(i, j + 1, k) - wz(i, j - 1, k)) +
       -0.2 * (wz(i, j + 2, k) - wz(i, j - 2, k)) +
       0.038 * (wz(i, j + 3, k) - wz(i, j - 3, k)) +
       -0.0035 * (wz(i, j + 4, k) - wz(i, j - 4, k))) *
      dxinv1;
diffflux2(i,j,k) =
    0.3311 * (vxx + 1.333 * vyy + vzz + 0.333 * (uxy + wzy));
// Segment 6
wxx = (-2.847 * q_3(i,j,k) + 1.6 * (q_3(i + 1, j, k) + q_3(i - 1, j, k)) +
       -0.2 * (q_3(i + 2, j, k) + q_3(i - 2, j, k)) +
       0.0253 * (q_3(i + 3, j, k) + q_3(i - 3, j, k)) +
       -0.0017 * (q_3(i + 4, j, k) + q_3(i - 4, j, k))) *
      (dxinv0 * dxinv0);
wyy = (-2.847 * q_3(i,j,k) + 1.6 * (q_3(i, j + 1, k) + q_3(i, j - 1, k)) +
       -0.2 * (q_3(i, j + 2, k) + q_3(i, j - 2, k)) +
       0.0253 * (q_3(i, j + 3, k) + q_3(i, j - 3, k)) +
       -0.0017 * (q_3(i, j + 4, k) + q_3(i, j - 4, k))) *
      (dxinv1 * dxinv1);
wzz = (-2.847 * q_3(i,j,k) + 1.6 * (q_3(i, j, k + 1) + q_3(i, j, k - 1)) +
       -0.2 * (q_3(i, j, k + 2) + q_3(i, j, k - 2)) +
       0.0253 * (q_3(i, j, k + 3) + q_3(i, j, k - 3)) +
       -0.0017 * (q_3(i, j, k + 4) + q_3(i, j, k - 4))) *
      (dxinv2 * dxinv2);
uxz = (0.8 * (ux(i, j, k + 1) - ux(i, j, k - 1)) +
       -0.2 * (ux(i, j, k + 2) - ux(i, j, k - 2)) +
       0.038 * (ux(i, j, k + 3) - ux(i, j, k - 3)) +
       -0.0035 * (ux(i, j, k + 4) - ux(i, j, k - 4))) *
      dxinv2;
vyz = (0.8 * (vy(i, j, k + 1) - vy(i, j, k - 1)) +
       -0.2 * (vy(i, j, k + 2) - vy(i, j, k - 2)) +
       0.038 * (vy(i, j, k + 3) - vy(i, j, k - 3)) +
       -0.0035 * (vy(i, j, k + 4) - vy(i, j, k - 4))) *
      dxinv2;
diffflux3(i,j,k) =
    0.3311 * (wxx + wyy + 1.333 * wzz + 0.333 * (uxz + vyz));
// Segment 7
txx = (-2.847 * q_5(i,j,k) + 1.6 * (q_5(i + 1, j, k) + q_5(i - 1, j, k)) +
       -0.2 * (q_5(i + 2, j, k) + q_5(i - 2, j, k)) +
       0.0253 * (q_5(i + 3, j, k) + q_5(i - 3, j, k)) +
       -0.0017 * (q_5(i + 4, j, k) + q_5(i - 4, j, k))) *
      (dxinv0 * dxinv0);
tyy = (-2.847 * q_5(i,j,k) + 1.6 * (q_5(i, j + 1, k) + q_5(i, j - 1, k)) +
       -0.2 * (q_5(i, j + 2, k) + q_5(i, j - 2, k)) +
       0.0253 * (q_5(i, j + 3, k) + q_5(i, j - 3, k)) +
       -0.0017 * (q_5(i, j + 4, k) + q_5(i, j - 4, k))) *
      (dxinv1 * dxinv1);
tzz = (-2.847 * q_5(i,j,k) + 1.6 * (q_5(i, j, k + 1) + q_5(i, j, k - 1)) +
       -0.2 * (q_5(i, j, k + 2) + q_5(i, j, k - 2)) +
       0.0253 * (q_5(i, j, k + 3) + q_5(i, j, k - 3)) +
       -0.0017 * (q_5(i, j, k + 4) + q_5(i, j, k - 4))) *
      (dxinv2 * dxinv2);
divu = 0.666 * (ux(i,j,k) + vy(i,j,k) + wz(i,j,k));
tauxx = 2e0 * ux(i,j,k) - divu;
tauyy = 2e0 * vy(i,j,k) - divu;
tauzz = 2e0 * wz(i,j,k) - divu;
tauxy = uy(i,j,k) + vx(i,j,k);
tauxz = uz(i,j,k) + wx(i,j,k);
tauyz = vz(i,j,k) + wy(i,j,k);
mechwork = tauxx * ux(i,j,k) + tauyy * vy(i,j,k) + tauzz * wz(i,j,k) +
           (tauxy * tauxy) + (tauxz * tauxz) + (tauyz * tauyz);
mechwork = 0.3311 * mechwork + diffflux1(i,j,k) * q_1(i,j,k) +
           diffflux2(i,j,k) * q_2(i,j,k) +
           diffflux3(i,j,k) * q_3(i,j,k);
diffflux4(i,j,k) = 0.7112 * (txx + tyy + tzz) + mechwork;
