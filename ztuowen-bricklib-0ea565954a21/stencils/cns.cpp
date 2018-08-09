#include"brick.h"
#include"immintrin.h"
#include"cns_const.h"
#include"omp.h"


int naive_cns(brickd *cons, brickd *q, brickd *flux, brick_list &blist, float *dx) {
  float dxinv0 = 1 / dx[0];
  float dxinv1 = 1 / dx[1];
  float dxinv2 = 1 / dx[2];
  omp_set_num_threads(blist.lv1);
#pragma omp parallel for schedule(dynamic, 1) proc_bind(spread)
  for (long r = 0; r < blist.rlen; ++r) {
    omp_set_num_threads(blist.lv2);
#pragma omp parallel for schedule(static, 1) proc_bind(close)
    for (long l = blist.rdat[r]; l < blist.rdat[r + 1]; ++l)
      for (long o = blist.bdat[l]; o < blist.bdat[l + 1]; ++o) {
        long b = blist.dat[o];
        int k, j, i;
        for (k = 0; k < flux[irho].info->dim_z; ++k)
          for (j = 0; j < flux[irho].info->dim_y; ++j)
            for (i = 0; i < flux[irho].info->dim_x; ++i) {
              // X dimension
              {
                float qum4 = q[qu].elem(b, k, j, i - 4);
                float qum3 = q[qu].elem(b, k, j, i - 3);
                float qum2 = q[qu].elem(b, k, j, i - 2);
                float qum1 = q[qu].elem(b, k, j, i - 1);
                float qup1 = q[qu].elem(b, k, j, i + 1);
                float qup2 = q[qu].elem(b, k, j, i + 2);
                float qup3 = q[qu].elem(b, k, j, i + 3);
                float qup4 = q[qu].elem(b, k, j, i + 4);
                flux[irho].elem(b, k, j, i) =
                    -dxinv0 * (
                        ALP * cons[imx].elem(b, k, j, i + 1) + -ALP * cons[imx].elem(b, k, j, i - 1) +
                        BET * cons[imx].elem(b, k, j, i + 2) + -BET * cons[imx].elem(b, k, j, i - 2) +
                        GAM * cons[imx].elem(b, k, j, i + 3) + -GAM * cons[imx].elem(b, k, j, i - 3) +
                        DEL * cons[imx].elem(b, k, j, i + 4) + -DEL * cons[imx].elem(b, k, j, i - 4)
                    );
                flux[imx].elem(b, k, j, i) =
                    -dxinv0 * (
                        ALP * cons[imx].elem(b, k, j, i + 1) * qup1 + -ALP * cons[imx].elem(b, k, j, i - 1) * qum1 +
                        ALP * q[qpres].elem(b, k, j, i + 1) + -ALP * q[qpres].elem(b, k, j, i - 1) +
                        BET * cons[imx].elem(b, k, j, i + 2) * qup2 + -BET * cons[imx].elem(b, k, j, i - 2) * qum2 +
                        BET * q[qpres].elem(b, k, j, i + 2) + -BET * q[qpres].elem(b, k, j, i - 2) +
                        GAM * cons[imx].elem(b, k, j, i + 3) * qup3 + -GAM * cons[imx].elem(b, k, j, i - 3) * qum3 +
                        GAM * q[qpres].elem(b, k, j, i + 3) + -GAM * q[qpres].elem(b, k, j, i - 3) +
                        DEL * cons[imx].elem(b, k, j, i + 4) * qup4 + -DEL * cons[imx].elem(b, k, j, i - 4) * qum4 +
                        DEL * q[qpres].elem(b, k, j, i + 4) + -DEL * q[qpres].elem(b, k, j, i - 4)
                    );
                flux[imy].elem(b, k, j, i) =
                    -dxinv0 * (
                        ALP * cons[imy].elem(b, k, j, i + 1) * qup1 + -ALP * cons[imy].elem(b, k, j, i - 1) * qum1 +
                        BET * cons[imy].elem(b, k, j, i + 2) * qup2 + -BET * cons[imy].elem(b, k, j, i - 2) * qum2 +
                        GAM * cons[imy].elem(b, k, j, i + 3) * qup3 + -GAM * cons[imy].elem(b, k, j, i - 3) * qum3 +
                        DEL * cons[imy].elem(b, k, j, i + 4) * qup4 + -DEL * cons[imy].elem(b, k, j, i - 4) * qum4
                    );
                flux[imz].elem(b, k, j, i) =
                    -dxinv0 * (
                        ALP * cons[imz].elem(b, k, j, i + 1) * qup1 + -ALP * cons[imz].elem(b, k, j, i - 1) * qum1 +
                        BET * cons[imz].elem(b, k, j, i + 2) * qup2 + -BET * cons[imz].elem(b, k, j, i - 2) * qum2 +
                        GAM * cons[imz].elem(b, k, j, i + 3) * qup3 + -GAM * cons[imz].elem(b, k, j, i - 3) * qum3 +
                        DEL * cons[imz].elem(b, k, j, i + 4) * qup4 + -DEL * cons[imz].elem(b, k, j, i - 4) * qum4
                    );
                flux[iene].elem(b, k, j, i) =
                    -dxinv0 * (
                        ALP * cons[iene].elem(b, k, j, i + 1) * qup1 + -ALP * cons[iene].elem(b, k, j, i - 1) * qum1 +
                        ALP * q[qpres].elem(b, k, j, i + 1) * qup1 + -ALP * q[qpres].elem(b, k, j, i - 1) * qum1 +
                        BET * cons[iene].elem(b, k, j, i + 2) * qup2 + -BET * cons[iene].elem(b, k, j, i - 2) * qum2 +
                        BET * q[qpres].elem(b, k, j, i + 2) * qup2 + -BET * q[qpres].elem(b, k, j, i - 2) * qum2 +
                        GAM * cons[iene].elem(b, k, j, i + 3) * qup3 + -GAM * cons[iene].elem(b, k, j, i - 3) * qum3 +
                        GAM * q[qpres].elem(b, k, j, i + 3) * qup3 + -GAM * q[qpres].elem(b, k, j, i - 3) * qum3 +
                        DEL * cons[iene].elem(b, k, j, i + 4) * qup4 + -DEL * cons[iene].elem(b, k, j, i - 4) * qum4 +
                        DEL * q[qpres].elem(b, k, j, i + 4) * qup4 + -DEL * q[qpres].elem(b, k, j, i - 4) * qum4
                    );
              }
              // Y dimension
              {
                float qvm4 = q[qv].elem(b, k, j - 4, i);
                float qvm3 = q[qv].elem(b, k, j - 3, i);
                float qvm2 = q[qv].elem(b, k, j - 2, i);
                float qvm1 = q[qv].elem(b, k, j - 1, i);
                float qvp1 = q[qv].elem(b, k, j + 1, i);
                float qvp2 = q[qv].elem(b, k, j + 2, i);
                float qvp3 = q[qv].elem(b, k, j + 3, i);
                float qvp4 = q[qv].elem(b, k, j + 4, i);
                flux[irho].elem(b, k, j, i) +=
                    -dxinv1 * (
                        ALP * cons[imy].elem(b, k, j + 1, i) + -ALP * cons[imy].elem(b, k, j - 1, i) +
                        BET * cons[imy].elem(b, k, j + 3, i) + -BET * cons[imy].elem(b, k, j - 2, i) +
                        GAM * cons[imy].elem(b, k, j + 3, i) + -GAM * cons[imy].elem(b, k, j - 3, i) +
                        DEL * cons[imy].elem(b, k, j + 4, i) + -DEL * cons[imy].elem(b, k, j - 4, i)
                    );
                flux[imx].elem(b, k, j, i) +=
                    -dxinv1 * (
                        ALP * cons[imx].elem(b, k, j + 1, i) * qvp1 + -ALP * cons[imx].elem(b, k, j - 1, i) * qvm1 +
                        BET * cons[imx].elem(b, k, j + 2, i) * qvp2 + -BET * cons[imx].elem(b, k, j - 2, i) * qvm2 +
                        GAM * cons[imx].elem(b, k, j + 3, i) * qvp3 + -GAM * cons[imx].elem(b, k, j - 3, i) * qvm3 +
                        DEL * cons[imx].elem(b, k, j + 4, i) * qvp4 + -DEL * cons[imx].elem(b, k, j - 4, i) * qvm4
                    );
                flux[imy].elem(b, k, j, i) +=
                    -dxinv1 * (
                        ALP * cons[imy].elem(b, k, j + 1, i) * qvp1 + -ALP * cons[imy].elem(b, k, j - 1, i) * qvm1 +
                        ALP * q[qpres].elem(b, k, j + 1, i) + -ALP * q[qpres].elem(b, k, j - 1, i) +
                        BET * cons[imy].elem(b, k, j + 2, i) * qvp2 + -BET * cons[imy].elem(b, k, j - 2, i) * qvm2 +
                        BET * q[qpres].elem(b, k, j + 2, i) + -BET * q[qpres].elem(b, k, j - 2, i) +
                        GAM * cons[imy].elem(b, k, j + 3, i) * qvp3 + -GAM * cons[imy].elem(b, k, j - 3, i) * qvm3 +
                        GAM * q[qpres].elem(b, k, j + 3, i) + -GAM * q[qpres].elem(b, k, j - 3, i) +
                        DEL * cons[imy].elem(b, k, j + 4, i) * qvp4 + -DEL * cons[imy].elem(b, k, j - 4, i) * qvm4 +
                        DEL * q[qpres].elem(b, k, j + 4, i) + -DEL * q[qpres].elem(b, k, j - 4, i)
                    );
                flux[imz].elem(b, k, j, i) +=
                    -dxinv1 * (
                        ALP * cons[imz].elem(b, k, j + 1, i) * qvp1 + -ALP * cons[imz].elem(b, k, j - 1, i) * qvm1 +
                        BET * cons[imz].elem(b, k, j + 2, i) * qvp2 + -BET * cons[imz].elem(b, k, j - 2, i) * qvm2 +
                        GAM * cons[imz].elem(b, k, j + 3, i) * qvp3 + -GAM * cons[imz].elem(b, k, j - 3, i) * qvm3 +
                        DEL * cons[imz].elem(b, k, j + 4, i) * qvp4 + -DEL * cons[imz].elem(b, k, j - 4, i) * qvm4
                    );
                flux[iene].elem(b, k, j, i) +=
                    -dxinv1 * (
                        ALP * cons[iene].elem(b, k, j + 1, i) * qvp1 + -ALP * cons[imy].elem(b, k, j - 1, i) * qvm1 +
                        ALP * q[qpres].elem(b, k, j + 1, i) * qvp1 + -ALP * q[qpres].elem(b, k, j - 1, i) * qvm1 +
                        BET * cons[iene].elem(b, k, j + 2, i) * qvp2 + -BET * cons[imy].elem(b, k, j - 2, i) * qvm2 +
                        BET * q[qpres].elem(b, k, j + 2, i) * qvp2 + -BET * q[qpres].elem(b, k, j - 2, i) * qvm2 +
                        GAM * cons[iene].elem(b, k, j + 3, i) * qvp3 + -GAM * cons[imy].elem(b, k, j - 3, i) * qvm3 +
                        GAM * q[qpres].elem(b, k, j + 3, i) * qvp3 + -GAM * q[qpres].elem(b, k, j - 3, i) * qvm3 +
                        DEL * cons[iene].elem(b, k, j + 4, i) * qvp4 + -DEL * cons[imy].elem(b, k, j - 4, i) * qvm4 +
                        DEL * q[qpres].elem(b, k, j + 4, i) * qvp4 + -DEL * q[qpres].elem(b, k, j - 4, i) * qvm4
                    );
              }
              // Z dimension
              {
                float qwm4 = q[qw].elem(b, k - 4, j, i);
                float qwm3 = q[qw].elem(b, k - 3, j, i);
                float qwm2 = q[qw].elem(b, k - 2, j, i);
                float qwm1 = q[qw].elem(b, k - 1, j, i);
                float qwp1 = q[qw].elem(b, k + 1, j, i);
                float qwp2 = q[qw].elem(b, k + 2, j, i);
                float qwp3 = q[qw].elem(b, k + 3, j, i);
                float qwp4 = q[qw].elem(b, k + 4, j, i);
                flux[irho].elem(b, k, j, i) +=
                    -dxinv2 * (
                        ALP * cons[imz].elem(b, k + 1, j, i) + -ALP * cons[imz].elem(b, k - 1, j, i) +
                        BET * cons[imz].elem(b, k + 2, j, i) + -BET * cons[imz].elem(b, k - 2, j, i) +
                        GAM * cons[imz].elem(b, k + 3, j, i) + -GAM * cons[imz].elem(b, k - 3, j, i) +
                        DEL * cons[imz].elem(b, k + 4, j, i) + -DEL * cons[imz].elem(b, k - 4, j, i)
                    );
                flux[imx].elem(b, k, j, i) +=
                    -dxinv2 * (
                        ALP * cons[imx].elem(b, k + 1, j, i) * qwp1 + -ALP * cons[imx].elem(b, k - 1, j, i) * qwm1 +
                        BET * cons[imx].elem(b, k + 2, j, i) * qwp2 + -BET * cons[imx].elem(b, k - 2, j, i) * qwm2 +
                        GAM * cons[imx].elem(b, k + 3, j, i) * qwp3 + -GAM * cons[imx].elem(b, k - 3, j, i) * qwm3 +
                        DEL * cons[imx].elem(b, k + 4, j, i) * qwp4 + -DEL * cons[imx].elem(b, k - 4, j, i) * qwm4
                    );
                flux[imy].elem(b, k, j, i) +=
                    -dxinv2 * (
                        ALP * cons[imy].elem(b, k + 1, j, i) * qwp1 + -ALP * cons[imx].elem(b, k - 1, j, i) * qwm1 +
                        BET * cons[imy].elem(b, k + 2, j, i) * qwp2 + -BET * cons[imx].elem(b, k - 2, j, i) * qwm2 +
                        GAM * cons[imy].elem(b, k + 3, j, i) * qwp3 + -GAM * cons[imx].elem(b, k - 3, j, i) * qwm3 +
                        DEL * cons[imy].elem(b, k + 4, j, i) * qwp4 + -DEL * cons[imx].elem(b, k - 4, j, i) * qwm4
                    );
                flux[imz].elem(b, k, j, i) +=
                    -dxinv2 * (
                        ALP * cons[imz].elem(b, k + 1, j, i) * qwp1 + -ALP * cons[imx].elem(b, k - 1, j, i) * qwm1 +
                        ALP * q[qpres].elem(b, k + 1, j, i) + -ALP * q[qpres].elem(b, k - 1, j, i) +
                        BET * cons[imz].elem(b, k + 2, j, i) * qwp2 + -BET * cons[imx].elem(b, k - 2, j, i) * qwm2 +
                        BET * q[qpres].elem(b, k + 2, j, i) + -BET * q[qpres].elem(b, k - 2, j, i) +
                        GAM * cons[imz].elem(b, k + 3, j, i) * qwp3 + -GAM * cons[imx].elem(b, k - 3, j, i) * qwm3 +
                        GAM * q[qpres].elem(b, k + 3, j, i) + -GAM * q[qpres].elem(b, k - 3, j, i) +
                        DEL * cons[imz].elem(b, k + 4, j, i) * qwp4 + -DEL * cons[imx].elem(b, k - 4, j, i) * qwm4 +
                        DEL * q[qpres].elem(b, k + 4, j, i) + -DEL * q[qpres].elem(b, k - 4, j, i)
                    );
                flux[iene].elem(b, k, j, i) +=
                    -dxinv2 * (
                        ALP * cons[iene].elem(b, k + 1, j, i) * qwp1 + -ALP * cons[imx].elem(b, k - 1, j, i) * qwm1 +
                        ALP * q[qpres].elem(b, k + 1, j, i) * qwp1 + -ALP * q[qpres].elem(b, k - 1, j, i) * qwm1 +
                        BET * cons[iene].elem(b, k + 2, j, i) * qwp2 + -BET * cons[imx].elem(b, k - 2, j, i) * qwm2 +
                        BET * q[qpres].elem(b, k + 2, j, i) * qwp2 + -BET * q[qpres].elem(b, k - 2, j, i) * qwm2 +
                        GAM * cons[iene].elem(b, k + 3, j, i) * qwp3 + -GAM * cons[imx].elem(b, k - 3, j, i) * qwm3 +
                        GAM * q[qpres].elem(b, k + 3, j, i) * qwp3 + -GAM * q[qpres].elem(b, k - 3, j, i) * qwm3 +
                        DEL * cons[iene].elem(b, k + 4, j, i) * qwp4 + -DEL * cons[imx].elem(b, k - 4, j, i) * qwm4 +
                        DEL * q[qpres].elem(b, k + 4, j, i) * qwp4 + -DEL * q[qpres].elem(b, k - 4, j, i) * qwm4
                    );
              }
            }
      }
  }
  return 1;
}

