from st.expr import Index, ConstRef
from st.grid import Grid

# Declare indices
i = Index(0)
j = Index(1)
k = Index(2)

# Declare grid
phi = Grid("phi", 3)
alpha = Grid("alpha", 3)
beta_i = Grid("beta_i", 3)
beta_j = Grid("beta_j", 3)
beta_k = Grid("beta_k", 3)
phi_new = Grid("phi_new", 3)
lamb = Grid("lambda", 3)
rhs = Grid("rhs", 3)

h2inv = ConstRef('H2INV')

helmholtz = alpha(i, j, k) * phi(i, j, k) - h2inv * (beta_i(i + 1, j, k) * (phi(i + 1, j, k) - phi(i, j, k)) - beta_i(i, j, k) * (phi(i, j, k) - phi(i - 1, j, k)) + beta_j(i, j + 1, k) * (phi(i, j + 1, k) - phi(i, j, k)) - beta_j(i, j, k) * (phi(i, j, k) - phi(i, j - 1, k)) + beta_k(i, j, k + 1) * (phi(i, j, k + 1) - phi(i, j, k)) - beta_k(i, j, k) * (phi(i, j, k) - phi(i, j, k - 1)))

calc = phi(i, j, k) - lamb(i, j, k)*(helmholtz-rhs(i, j, k))
phi_new(i, j, k).assign(calc)

STENCIL = [phi_new]
