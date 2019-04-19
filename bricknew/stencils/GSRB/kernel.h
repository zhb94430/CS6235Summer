out(i, j, k) = c1 * alpha(i, j, k) * x(i, j, k) -
               c2 * h2inv *
                   (beta_i(i + 1, j, k) * (x(i + 1, j, k) - x(i, j, k)) +
                    beta_i(i, j, k) * (x(i - 1, j, k) - x(i, j, k)) +
                    beta_j(i, j + 1, k) * (x(i, j + 1, k) - x(i, j, k)) +
                    beta_j(i, j, k) * (x(i, j - 1, k) - x(i, j, k)) +
                    beta_k(i, j, k + 1) * (x(i, j, k + 1) - x(i, j, k)) +
                    beta_k(i, j, k) * (x(i, j, k - 1) - x(i, j, k)));
