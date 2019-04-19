out(i, j,
    k) = c1 * alpha(i, j, k) * x(i, j, k) -
         c2 * h2inv *
             (0.0833 *
                  (beta_i(i, j, k) * (15.0 * (x(i - 1, j, k) - x(i, j, k)) -
                                      (x(i - 1, j, k) - x(i + 1, j, k))) +
                   beta_i(i + 1, j, k) * (15.0 * (x(i + 1, j, k) - x(i, j, k)) -
                                          (x(i + 2, j, k) - x(i - 1, j, k))) +
                   beta_j(i, j, k) * (15.0 * (x(i, j - 1, k) - x(i, j, k)) -
                                      (x(i, j - 1, k) - x(i, j + 1, k))) +
                   beta_j(i, j + 1, k) * (15.0 * (x(i, j + 1, k) - x(i, j, k)) -
                                          (x(i, j + 2, k) - x(i, j - 1, k))) +
                   beta_k(i, j, k) * (15.0 * (x(i, j, k - 1) - x(i, j, k)) -
                                      (x(i, j, k - 2) - x(i, j, k + 1))) +
                   beta_k(i, j, k + 1) * (15.0 * (x(i, j, k + 1) - x(i, j, k)) -
                                          (x(i, j, k + 2) - x(i, j, k - 1)))) +
              0.25 * 0.0833 *
                  ((beta_i(i, j + 1, k) - beta_i(i, j - 1, k)) *
                       (x(i - 1, j + 1, k) - x(i, j + 1, k) -
                        x(i - 1, j - 1, k) + x(i, j - 1, k)) +
                   (beta_i(i, j, k + 1) - beta_i(i, j, k - 1)) *
                       (x(i - 1, j, k + 1) - x(i, j, k + 1) -
                        x(i - 1, j, k - 1) + x(i, j, k - 1)) +
                   (beta_j(i + 1, j, k) - beta_j(i - 1, j, k)) *
                       (x(i + 1, j - 1, k) - x(i + 1, j, k) -
                        x(i - 1, j - 1, k) + x(i - 1, j, k)) +
                   (beta_j(i, j, k + 1) - beta_j(i, j, k - 1)) *
                       (x(i, j - 1, k + 1) - x(i, j, k + 1) -
                        x(i, j - 1, k - 1) + x(i, j, k - 1)) +
                   (beta_k(i + 1, j, k) - beta_k(i - 1, j, k)) *
                       (x(i + 1, j, k - 1) - x(i + 1, j, k) -
                        x(i - 1, j, k - 1) + x(i - 1, j, k)) +
                   (beta_k(i, j + 1, k) - beta_k(i, j - 1, k)) *
                       (x(i, j + 1, k - 1) - x(i, j + 1, k) -
                        x(i, j - 1, k - 1) + x(i, j - 1, k)) +
                   (beta_i(i + 1, j + 1, k) - beta_i(i + 1, j - 1, k)) *
                       (x(i + 1, j + 1, k) - x(i, j + 1, k) -
                        x(i + 1, j - 1, k) + x(i, j - 1, k)) +
                   (beta_i(i + 1, j, k + 1) - beta_i(i + 1, j, k - 1)) *
                       (x(i + 1, j, k + 1) - x(i, j, k + 1) -
                        x(i + 1, j, k - 1) + x(i, j, k - 1)) +
                   (beta_j(i + 1, j + 1, k) - beta_j(i - 1, j + 1, k)) *
                       (x(i + 1, j + 1, k) - x(i + 1, j, k) -
                        x(i - 1, j + 1, k) + x(i - 1, j, k)) +
                   (beta_j(i, j + 1, k + 1) - beta_j(i, j + 1, k - 1)) *
                       (x(i, j + 1, k + 1) - x(i, j, k + 1) -
                        x(i, j + 1, k - 1) + x(i, j, k - 1)) +
                   (beta_k(i + 1, j, k + 1) - beta_k(i - 1, j, k + 1)) *
                       (x(i + 1, j, k + 1) - x(i + 1, j, k) -
                        x(i - 1, j, k + 1) + x(i - 1, j, k)) +
                   (beta_k(i, j + 1, k + 1) - beta_k(i, j - 1, k + 1)) *
                       (x(i, j + 1, k + 1) - x(i, j + 1, k) -
                        x(i, j - 1, k + 1) + x(i, j - 1, k))));
