from st.expr import Index, ConstRef
from st.grid import Grid

i = Index(0)
j = Index(1)
k = Index(2)

qu = Grid("qu", 3)
qv = Grid("qv", 3)
qw = Grid("qw", 3)
qpres = Grid("qpres", 3)

flux_irho = Grid('flux_irho', 3)
flux_imx = Grid("flux_imx", 3)
flux_imy = Grid("flux_imy", 3)
flux_imz = Grid("flux_imz", 3)
flux_iene = Grid("flux_iene", 3)

cons_imx = Grid("cons_imx", 3)
cons_imy = Grid("cons_imy", 3)
cons_imz = Grid("cons_imz", 3)
cons_iene = Grid("cons_iene", 3)

dxinv0 = ConstRef('dxinv0')
dxinv1 = ConstRef('dxinv1')
dxinv2 = ConstRef('dxinv2')

ALP = ConstRef('ALP')
BET = ConstRef('BET')
GAM = ConstRef('GAM')
DEL = ConstRef('DEL')


qum4 = qu(i - 4, j, k)
qum3 = qu(i - 3, j, k)
qum2 = qu(i - 2, j, k)
qum1 = qu(i - 1, j, k)
qup1 = qu(i + 1, j, k)
qup2 = qu(i + 2, j, k)
qup3 = qu(i + 3, j, k)
qup4 = qu(i + 4, j, k)

_flux_irho = -dxinv0 * (
        ALP * cons_imx(i + 1, j, k) + -ALP * cons_imx(i - 1, j, k) + 
        BET * cons_imx(i + 2, j, k) + -BET * cons_imx(i - 2, j, k) + 
        GAM * cons_imx(i + 3, j, k) + -GAM * cons_imx(i - 3, j, k) + 
        DEL * cons_imx(i + 4, j, k) + -DEL * cons_imx(i - 4, j, k))

_flux_imx = -dxinv0 * (
        ALP * cons_imx(i + 1, j, k) * qup1 + -ALP * cons_imx(i - 1, j, k) * qum1 + 
        ALP * qpres(i + 1, j, k) + -ALP * qpres(i - 1, j, k) + 
        BET * cons_imx(i + 2, j, k) * qup2 + -BET * cons_imx(i - 2, j, k) * qum2 + 
        BET * qpres(i + 2, j, k) + -BET * qpres(i - 2, j, k) + 
        GAM * cons_imx(i + 3, j, k) * qup3 + -GAM * cons_imx(i - 3, j, k) * qum3 + 
        GAM * qpres(i + 3, j, k) + -GAM * qpres(i - 3, j, k) + 
        DEL * cons_imx(i + 4, j, k) * qup4 + -DEL * cons_imx(i - 4, j, k) * qum4 + 
        DEL * qpres(i + 4, j, k) + -DEL * qpres(i - 4, j, k))

_flux_imy = -dxinv0 * (
        ALP * cons_imy(i + 1, j, k) * qup1 + -ALP * cons_imy(i - 1, j, k) * qum1 +
        BET * cons_imy(i + 2, j, k) * qup2 + -BET * cons_imy(i - 2, j, k) * qum2 +
        GAM * cons_imy(i + 3, j, k) * qup3 + -GAM * cons_imy(i - 3, j, k) * qum3 +
        DEL * cons_imy(i + 4, j, k) * qup4 + -DEL * cons_imy(i - 4, j, k) * qum4)

_flux_imz = -dxinv0 * (
        ALP * cons_imz(i + 1, j, k) * qup1 + -ALP * cons_imz(i - 1, j, k) * qum1 +
        BET * cons_imz(i + 2, j, k) * qup2 + -BET * cons_imz(i - 2, j, k) * qum2 +
        GAM * cons_imz(i + 3, j, k) * qup3 + -GAM * cons_imz(i - 3, j, k) * qum3 +
        DEL * cons_imz(i + 4, j, k) * qup4 + -DEL * cons_imz(i - 4, j, k) * qum4)

_flux_iene = -dxinv0 * (
        ALP * cons_iene(i + 1, j, k) * qup1 + -ALP * cons_iene(i - 1, j, k) * qum1 +
        ALP * qpres(i + 1, j, k) * qup1 + -ALP * qpres(i - 1, j, k) * qum1 +
        BET * cons_iene(i + 2, j, k) * qup2 + -BET * cons_iene(i - 2, j, k) * qum2 +
        BET * qpres(i + 2, j, k) * qup2 + -BET * qpres(i - 2, j, k) * qum2 +
        GAM * cons_iene(i + 3, j, k) * qup3 + -GAM * cons_iene(i - 3, j, k) * qum3 +
        GAM * qpres(i + 3, j, k) * qup3 + -GAM * qpres(i - 3, j, k) * qum3 +
        DEL * cons_iene(i + 4, j, k) * qup4 + -DEL * cons_iene(i - 4, j, k) * qum4 +
        DEL * qpres(i + 4, j, k) * qup4 + -DEL * qpres(i - 4, j, k) * qum4)

qvm4 = qv(i, j - 4, k)
qvm3 = qv(i, j - 3, k)
qvm2 = qv(i, j - 2, k)
qvm1 = qv(i, j - 1, k)
qvp1 = qv(i, j + 1, k)
qvp2 = qv(i, j + 2, k)
qvp3 = qv(i, j + 3, k)
qvp4 = qv(i, j + 4, k)
_flux_irho += -dxinv1 * (
        ALP * cons_imy(i, j + 1, k) + -ALP * cons_imy(i, j - 1, k) +
        BET * cons_imy(i, j + 3, k) + -BET * cons_imy(i, j - 2, k) +
        GAM * cons_imy(i, j + 3, k) + -GAM * cons_imy(i, j - 3, k) +
        DEL * cons_imy(i, j + 4, k) + -DEL * cons_imy(i, j - 4, k))

_flux_imx += -dxinv1 * (
        ALP * cons_imx(i, j + 1, k) * qvp1 + -ALP * cons_imx(i, j - 1, k) * qvm1 +
        BET * cons_imx(i, j + 2, k) * qvp2 + -BET * cons_imx(i, j - 2, k) * qvm2 +
        GAM * cons_imx(i, j + 3, k) * qvp3 + -GAM * cons_imx(i, j - 3, k) * qvm3 +
        DEL * cons_imx(i, j + 4, k) * qvp4 + -DEL * cons_imx(i, j - 4, k) * qvm4)

_flux_imy += -dxinv1 * (
        ALP * cons_imy(i, j + 1, k) * qvp1 + -ALP * cons_imy(i, j - 1, k) * qvm1 + 
        ALP * qpres(i, j + 1, k) + -ALP * qpres(i, j - 1, k) + 
        BET * cons_imy(i, j + 2, k) * qvp2 + -BET * cons_imy(i, j - 2, k) * qvm2 + 
        BET * qpres(i, j + 2, k) + -BET * qpres(i, j - 2, k) + 
        GAM * cons_imy(i, j + 3, k) * qvp3 + -GAM * cons_imy(i, j - 3, k) * qvm3 + 
        GAM * qpres(i, j + 3, k) + -GAM * qpres(i, j - 3, k) + 
        DEL * cons_imy(i, j + 4, k) * qvp4 + -DEL * cons_imy(i, j - 4, k) * qvm4 + 
        DEL * qpres(i, j + 4, k) + -DEL * qpres(i, j - 4, k))

_flux_imz += -dxinv1 * (
        ALP * cons_imz(i, j + 1, k) * qvp1 + -ALP * cons_imz(i, j - 1, k) * qvm1 +
        BET * cons_imz(i, j + 2, k) * qvp2 + -BET * cons_imz(i, j - 2, k) * qvm2 +
        GAM * cons_imz(i, j + 3, k) * qvp3 + -GAM * cons_imz(i, j - 3, k) * qvm3 +
        DEL * cons_imz(i, j + 4, k) * qvp4 + -DEL * cons_imz(i, j - 4, k) * qvm4)

_flux_iene += -dxinv1 * (
        ALP * cons_iene(i, j + 1, k) * qvp1 + -ALP * cons_imy(i, j - 1, k) * qvm1 + 
        ALP * qpres(i, j + 1, k) * qvp1 + -ALP * qpres(i, j - 1, k) * qvm1 +
        BET * cons_iene(i, j + 2, k) * qvp2 + -BET * cons_imy(i, j - 2, k) * qvm2 + 
        BET * qpres(i, j + 2, k) * qvp2 + -BET * qpres(i, j - 2, k) * qvm2 +
        GAM * cons_iene(i, j + 3, k) * qvp3 + -GAM * cons_imy(i, j - 3, k) * qvm3 + 
        GAM * qpres(i, j + 3, k) * qvp3 + -GAM * qpres(i, j - 3, k) * qvm3 +
        DEL * cons_iene(i, j + 4, k) * qvp4 + -DEL * cons_imy(i, j - 4, k) * qvm4 + 
        DEL * qpres(i, j + 4, k) * qvp4 + -DEL * qpres(i, j - 4, k) * qvm4)

qwm4 = qw(i, j, k - 4)
qwm3 = qw(i, j, k - 3)
qwm2 = qw(i, j, k - 2)
qwm1 = qw(i, j, k - 1)
qwp1 = qw(i, j, k + 1)
qwp2 = qw(i, j, k + 2)
qwp3 = qw(i, j, k + 3)
qwp4 = qw(i, j, k + 4)

_flux_irho += -dxinv2 * (
        ALP * cons_imz(i, j, k + 1) + -ALP * cons_imz(i, j, k - 1) + 
        BET * cons_imz(i, j, k + 2) + -BET * cons_imz(i, j, k - 2) + 
        GAM * cons_imz(i, j, k + 3) + -GAM * cons_imz(i, j, k - 3) + 
        DEL * cons_imz(i, j, k + 4) + -DEL * cons_imz(i, j, k - 4))

_flux_imx += -dxinv2 * (
        ALP * cons_imx(i, j, k + 1) * qwp1 + -ALP * cons_imx(i, j, k - 1) * qwm1 +
        BET * cons_imx(i, j, k + 2) * qwp2 + -BET * cons_imx(i, j, k - 2) * qwm2 +
        GAM * cons_imx(i, j, k + 3) * qwp3 + -GAM * cons_imx(i, j, k - 3) * qwm3 +
        DEL * cons_imx(i, j, k + 4) * qwp4 + -DEL * cons_imx(i, j, k - 4) * qwm4)

_flux_imy += -dxinv2 * (
        ALP * cons_imy(i, j, k + 1) * qwp1 + -ALP * cons_imx(i, j, k - 1) * qwm1 +
        BET * cons_imy(i, j, k + 2) * qwp2 + -BET * cons_imx(i, j, k - 2) * qwm2 +
        GAM * cons_imy(i, j, k + 3) * qwp3 + -GAM * cons_imx(i, j, k - 3) * qwm3 +
        DEL * cons_imy(i, j, k + 4) * qwp4 + -DEL * cons_imx(i, j, k - 4) * qwm4)

_flux_imz += -dxinv2 * (
        ALP * cons_imz(i, j, k + 1) * qwp1 + -ALP * cons_imx(i, j, k - 1) * qwm1 + 
        ALP * qpres(i, j, k + 1) + -ALP * qpres(i, j, k - 1) + 
        BET * cons_imz(i, j, k + 2) * qwp2 + -BET * cons_imx(i, j, k - 2) * qwm2 + 
        BET * qpres(i, j, k + 2) + -BET * qpres(i, j, k - 2) + 
        GAM * cons_imz(i, j, k + 3) * qwp3 + -GAM * cons_imx(i, j, k - 3) * qwm3 + 
        GAM * qpres(i, j, k + 3) + -GAM * qpres(i, j, k - 3) + 
        DEL * cons_imz(i, j, k + 4) * qwp4 + -DEL * cons_imx(i, j, k - 4) * qwm4 + 
        DEL * qpres(i, j, k + 4) + -DEL * qpres(i, j, k - 4))

_flux_iene += -dxinv2 * (
        ALP * cons_iene(i, j, k + 1) * qwp1 + -ALP * cons_imx(i, j, k - 1) * qwm1 + 
        ALP * qpres(i, j, k + 1) * qwp1 + -ALP * qpres(i, j, k - 1) * qwm1 + 
        BET * cons_iene(i, j, k + 2) * qwp2 + -BET * cons_imx(i, j, k - 2) * qwm2 + 
        BET * qpres(i, j, k + 2) * qwp2 + -BET * qpres(i, j, k - 2) * qwm2 + 
        GAM * cons_iene(i, j, k + 3) * qwp3 + -GAM * cons_imx(i, j, k - 3) * qwm3 + 
        GAM * qpres(i, j, k + 3) * qwp3 + -GAM * qpres(i, j, k - 3) * qwm3 + 
        DEL * cons_iene(i, j, k + 4) * qwp4 + -DEL * cons_imx(i, j, k - 4) * qwm4 + 
        DEL * qpres(i, j, k + 4) * qwp4 + -DEL * qpres(i, j, k - 4) * qwm4)

flux_irho(i, j, k).assign(_flux_irho)
flux_imx(i, j, k).assign(_flux_imx)
flux_imy(i, j, k).assign(_flux_imy)
flux_imz(i, j, k).assign(_flux_imz)
flux_iene(i, j, k).assign(_flux_iene)

STENCIL = [flux_irho, flux_imx, flux_imy, flux_imz, flux_iene]
