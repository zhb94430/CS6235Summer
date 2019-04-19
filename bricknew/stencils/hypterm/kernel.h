{
    bElem qum4 = qu(i - 4, j, k);
    bElem qum3 = qu(i - 3, j, k);
    bElem qum2 = qu(i - 2, j, k);
    bElem qum1 = qu(i - 1, j, k);
    bElem qup1 = qu(i + 1, j, k);
    bElem qup2 = qu(i + 2, j, k);
    bElem qup3 = qu(i + 3, j, k);
    bElem qup4 = qu(i + 4, j, k);
    flux_irho(i, j, k) =
        -dxinv0 * (ALP * cons_imx(i + 1, j, k) + -ALP * cons_imx(i - 1, j, k) +
                   BET * cons_imx(i + 2, j, k) + -BET * cons_imx(i - 2, j, k) +
                   GAM * cons_imx(i + 3, j, k) + -GAM * cons_imx(i - 3, j, k) +
                   DEL * cons_imx(i + 4, j, k) + -DEL * cons_imx(i - 4, j, k));
    flux_imx(i, j, k) =
        -dxinv0 *
        (ALP * cons_imx(i + 1, j, k) * qup1 +
         -ALP * cons_imx(i - 1, j, k) * qum1 + ALP * qpres(i + 1, j, k) +
         -ALP * qpres(i - 1, j, k) + BET * cons_imx(i + 2, j, k) * qup2 +
         -BET * cons_imx(i - 2, j, k) * qum2 + BET * qpres(i + 2, j, k) +
         -BET * qpres(i - 2, j, k) + GAM * cons_imx(i + 3, j, k) * qup3 +
         -GAM * cons_imx(i - 3, j, k) * qum3 + GAM * qpres(i + 3, j, k) +
         -GAM * qpres(i - 3, j, k) + DEL * cons_imx(i + 4, j, k) * qup4 +
         -DEL * cons_imx(i - 4, j, k) * qum4 + DEL * qpres(i + 4, j, k) +
         -DEL * qpres(i - 4, j, k));
    flux_imy(i, j, k) = -dxinv0 * (ALP * cons_imy(i + 1, j, k) * qup1 +
                                   -ALP * cons_imy(i - 1, j, k) * qum1 +
                                   BET * cons_imy(i + 2, j, k) * qup2 +
                                   -BET * cons_imy(i - 2, j, k) * qum2 +
                                   GAM * cons_imy(i + 3, j, k) * qup3 +
                                   -GAM * cons_imy(i - 3, j, k) * qum3 +
                                   DEL * cons_imy(i + 4, j, k) * qup4 +
                                   -DEL * cons_imy(i - 4, j, k) * qum4);
    flux_imz(i, j, k) = -dxinv0 * (ALP * cons_imz(i + 1, j, k) * qup1 +
                                   -ALP * cons_imz(i - 1, j, k) * qum1 +
                                   BET * cons_imz(i + 2, j, k) * qup2 +
                                   -BET * cons_imz(i - 2, j, k) * qum2 +
                                   GAM * cons_imz(i + 3, j, k) * qup3 +
                                   -GAM * cons_imz(i - 3, j, k) * qum3 +
                                   DEL * cons_imz(i + 4, j, k) * qup4 +
                                   -DEL * cons_imz(i - 4, j, k) * qum4);
    flux_iene(i, j, k) =
        -dxinv0 *
        (ALP * cons_iene(i + 1, j, k) * qup1 +
         -ALP * cons_iene(i - 1, j, k) * qum1 +
         ALP * qpres(i + 1, j, k) * qup1 + -ALP * qpres(i - 1, j, k) * qum1 +
         BET * cons_iene(i + 2, j, k) * qup2 +
         -BET * cons_iene(i - 2, j, k) * qum2 +
         BET * qpres(i + 2, j, k) * qup2 + -BET * qpres(i - 2, j, k) * qum2 +
         GAM * cons_iene(i + 3, j, k) * qup3 +
         -GAM * cons_iene(i - 3, j, k) * qum3 +
         GAM * qpres(i + 3, j, k) * qup3 + -GAM * qpres(i - 3, j, k) * qum3 +
         DEL * cons_iene(i + 4, j, k) * qup4 +
         -DEL * cons_iene(i - 4, j, k) * qum4 +
         DEL * qpres(i + 4, j, k) * qup4 + -DEL * qpres(i - 4, j, k) * qum4);
}
// Y dimension
{
    bElem qvm4 = qv(i, j - 4, k);
    bElem qvm3 = qv(i, j - 3, k);
    bElem qvm2 = qv(i, j - 2, k);
    bElem qvm1 = qv(i, j - 1, k);
    bElem qvp1 = qv(i, j + 1, k);
    bElem qvp2 = qv(i, j + 2, k);
    bElem qvp3 = qv(i, j + 3, k);
    bElem qvp4 = qv(i, j + 4, k);
    flux_irho(i, j, k) +=
        -dxinv1 * (ALP * cons_imy(i, j + 1, k) + -ALP * cons_imy(i, j - 1, k) +
                   BET * cons_imy(i, j + 3, k) + -BET * cons_imy(i, j - 2, k) +
                   GAM * cons_imy(i, j + 3, k) + -GAM * cons_imy(i, j - 3, k) +
                   DEL * cons_imy(i, j + 4, k) + -DEL * cons_imy(i, j - 4, k));
    flux_imx(i, j, k) += -dxinv1 * (ALP * cons_imx(i, j + 1, k) * qvp1 +
                                    -ALP * cons_imx(i, j - 1, k) * qvm1 +
                                    BET * cons_imx(i, j + 2, k) * qvp2 +
                                    -BET * cons_imx(i, j - 2, k) * qvm2 +
                                    GAM * cons_imx(i, j + 3, k) * qvp3 +
                                    -GAM * cons_imx(i, j - 3, k) * qvm3 +
                                    DEL * cons_imx(i, j + 4, k) * qvp4 +
                                    -DEL * cons_imx(i, j - 4, k) * qvm4);
    flux_imy(i, j, k) +=
        -dxinv1 *
        (ALP * cons_imy(i, j + 1, k) * qvp1 +
         -ALP * cons_imy(i, j - 1, k) * qvm1 + ALP * qpres(i, j + 1, k) +
         -ALP * qpres(i, j - 1, k) + BET * cons_imy(i, j + 2, k) * qvp2 +
         -BET * cons_imy(i, j - 2, k) * qvm2 + BET * qpres(i, j + 2, k) +
         -BET * qpres(i, j - 2, k) + GAM * cons_imy(i, j + 3, k) * qvp3 +
         -GAM * cons_imy(i, j - 3, k) * qvm3 + GAM * qpres(i, j + 3, k) +
         -GAM * qpres(i, j - 3, k) + DEL * cons_imy(i, j + 4, k) * qvp4 +
         -DEL * cons_imy(i, j - 4, k) * qvm4 + DEL * qpres(i, j + 4, k) +
         -DEL * qpres(i, j - 4, k));
    flux_imz(i, j, k) += -dxinv1 * (ALP * cons_imz(i, j + 1, k) * qvp1 +
                                    -ALP * cons_imz(i, j - 1, k) * qvm1 +
                                    BET * cons_imz(i, j + 2, k) * qvp2 +
                                    -BET * cons_imz(i, j - 2, k) * qvm2 +
                                    GAM * cons_imz(i, j + 3, k) * qvp3 +
                                    -GAM * cons_imz(i, j - 3, k) * qvm3 +
                                    DEL * cons_imz(i, j + 4, k) * qvp4 +
                                    -DEL * cons_imz(i, j - 4, k) * qvm4);
    flux_iene(i, j, k) +=
        -dxinv1 *
        (ALP * cons_iene(i, j + 1, k) * qvp1 +
         -ALP * cons_imy(i, j - 1, k) * qvm1 + ALP * qpres(i, j + 1, k) * qvp1 +
         -ALP * qpres(i, j - 1, k) * qvm1 +
         BET * cons_iene(i, j + 2, k) * qvp2 +
         -BET * cons_imy(i, j - 2, k) * qvm2 + BET * qpres(i, j + 2, k) * qvp2 +
         -BET * qpres(i, j - 2, k) * qvm2 +
         GAM * cons_iene(i, j + 3, k) * qvp3 +
         -GAM * cons_imy(i, j - 3, k) * qvm3 + GAM * qpres(i, j + 3, k) * qvp3 +
         -GAM * qpres(i, j - 3, k) * qvm3 +
         DEL * cons_iene(i, j + 4, k) * qvp4 +
         -DEL * cons_imy(i, j - 4, k) * qvm4 + DEL * qpres(i, j + 4, k) * qvp4 +
         -DEL * qpres(i, j - 4, k) * qvm4);
}
// Z dimension
{
    bElem qwm4 = qw(i, j, k - 4);
    bElem qwm3 = qw(i, j, k - 3);
    bElem qwm2 = qw(i, j, k - 2);
    bElem qwm1 = qw(i, j, k - 1);
    bElem qwp1 = qw(i, j, k + 1);
    bElem qwp2 = qw(i, j, k + 2);
    bElem qwp3 = qw(i, j, k + 3);
    bElem qwp4 = qw(i, j, k + 4);
    flux_irho(i, j, k) +=
        -dxinv2 * (ALP * cons_imz(i, j, k + 1) + -ALP * cons_imz(i, j, k - 1) +
                   BET * cons_imz(i, j, k + 2) + -BET * cons_imz(i, j, k - 2) +
                   GAM * cons_imz(i, j, k + 3) + -GAM * cons_imz(i, j, k - 3) +
                   DEL * cons_imz(i, j, k + 4) + -DEL * cons_imz(i, j, k - 4));
    flux_imx(i, j, k) += -dxinv2 * (ALP * cons_imx(i, j, k + 1) * qwp1 +
                                    -ALP * cons_imx(i, j, k - 1) * qwm1 +
                                    BET * cons_imx(i, j, k + 2) * qwp2 +
                                    -BET * cons_imx(i, j, k - 2) * qwm2 +
                                    GAM * cons_imx(i, j, k + 3) * qwp3 +
                                    -GAM * cons_imx(i, j, k - 3) * qwm3 +
                                    DEL * cons_imx(i, j, k + 4) * qwp4 +
                                    -DEL * cons_imx(i, j, k - 4) * qwm4);
    flux_imy(i, j, k) += -dxinv2 * (ALP * cons_imy(i, j, k + 1) * qwp1 +
                                    -ALP * cons_imx(i, j, k - 1) * qwm1 +
                                    BET * cons_imy(i, j, k + 2) * qwp2 +
                                    -BET * cons_imx(i, j, k - 2) * qwm2 +
                                    GAM * cons_imy(i, j, k + 3) * qwp3 +
                                    -GAM * cons_imx(i, j, k - 3) * qwm3 +
                                    DEL * cons_imy(i, j, k + 4) * qwp4 +
                                    -DEL * cons_imx(i, j, k - 4) * qwm4);
    flux_imz(i, j, k) +=
        -dxinv2 *
        (ALP * cons_imz(i, j, k + 1) * qwp1 +
         -ALP * cons_imx(i, j, k - 1) * qwm1 + ALP * qpres(i, j, k + 1) +
         -ALP * qpres(i, j, k - 1) + BET * cons_imz(i, j, k + 2) * qwp2 +
         -BET * cons_imx(i, j, k - 2) * qwm2 + BET * qpres(i, j, k + 2) +
         -BET * qpres(i, j, k - 2) + GAM * cons_imz(i, j, k + 3) * qwp3 +
         -GAM * cons_imx(i, j, k - 3) * qwm3 + GAM * qpres(i, j, k + 3) +
         -GAM * qpres(i, j, k - 3) + DEL * cons_imz(i, j, k + 4) * qwp4 +
         -DEL * cons_imx(i, j, k - 4) * qwm4 + DEL * qpres(i, j, k + 4) +
         -DEL * qpres(i, j, k - 4));
    flux_iene(i, j, k) +=
        -dxinv2 *
        (ALP * cons_iene(i, j, k + 1) * qwp1 +
         -ALP * cons_imx(i, j, k - 1) * qwm1 + ALP * qpres(i, j, k + 1) * qwp1 +
         -ALP * qpres(i, j, k - 1) * qwm1 +
         BET * cons_iene(i, j, k + 2) * qwp2 +
         -BET * cons_imx(i, j, k - 2) * qwm2 + BET * qpres(i, j, k + 2) * qwp2 +
         -BET * qpres(i, j, k - 2) * qwm2 +
         GAM * cons_iene(i, j, k + 3) * qwp3 +
         -GAM * cons_imx(i, j, k - 3) * qwm3 + GAM * qpres(i, j, k + 3) * qwp3 +
         -GAM * qpres(i, j, k - 3) * qwm3 +
         DEL * cons_iene(i, j, k + 4) * qwp4 +
         -DEL * cons_imx(i, j, k - 4) * qwm4 + DEL * qpres(i, j, k + 4) * qwp4 +
         -DEL * qpres(i, j, k - 4) * qwm4);
}

