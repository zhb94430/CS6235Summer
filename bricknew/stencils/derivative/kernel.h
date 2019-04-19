r1(i, j, k) += c2 * (mu(i, j + 2, k) * met1(i, j + 2, k) * met1(i, j + 2, k) *
                         (c2 * (u2(i + 2, j + 2, k) - u2(i - 2, j + 2, k)) +
                          c1 * (u2(i + 1, j + 2, k) - u2(i - 1, j + 2, k))) +
                     mu(i, j - 2, k) * met1(i, j - 2, k) * met1(i, j - 2, k) *
                         (c2 * (u2(i + 2, j - 2, k) - u2(i - 2, j - 2, k)) +
                          c1 * (u2(i + 1, j - 2, k) - u2(i - 1, j - 2, k)))) +
               c1 * (mu(i, j + 1, k) * met1(i, j + 1, k) * met1(i, j + 1, k) *
                         (c2 * (u2(i + 2, j + 1, k) - u2(i - 2, j + 1, k)) +
                          c1 * (u2(i + 1, j + 1, k) - u2(i - 1, j + 1, k))) +
                     mu(i, j - 1, k) * met1(i, j - 1, k) * met1(i, j - 1, k) *
                         (c2 * (u2(i + 2, j - 1, k) - u2(i - 2, j - 1, k)) +
                          c1 * (u2(i + 1, j - 1, k) - u2(i - 1, j - 1, k)))) +
               c2 * (la(i + 2, j, k) * met1(i + 2, j, k) * met1(i + 2, j, k) *
                         (c2 * (u2(i + 2, j + 2, k) - u2(i + 2, j - 2, k)) +
                          c1 * (u2(i + 2, j + 1, k) - u2(i + 2, j - 1, k))) +
                     la(i - 2, j, k) * met1(i - 2, j, k) * met1(i - 2, j, k) *
                         (c2 * (u2(i - 2, j + 2, k) - u2(i - 2, j - 2, k)) +
                          c1 * (u2(i - 2, j + 1, k) - u2(i - 2, j - 1, k)))) +
               c1 * (la(i + 1, j, k) * met1(i + 1, j, k) * met1(i + 1, j, k) *
                         (c2 * (u2(i + 1, j + 2, k) - u2(i + 1, j - 2, k)) +
                          c1 * (u2(i + 1, j + 1, k) - u2(i + 1, j - 1, k))) +
                     la(i - 1, j, k) * met1(i - 1, j, k) * met1(i - 1, j, k) *
                         (c2 * (u2(i - 1, j + 2, k) - u2(i - 1, j - 2, k)) +
                          c1 * (u2(i - 1, j + 1, k) - u2(i - 1, j - 1, k))));

r1(i, j, k) += c2 * ((2 * mu(i, j, k + 2) + la(i, j, k + 2)) *
                         met2(i, j, k + 2) * met1(i, j, k + 2) *
                         (c2 * (u1(i + 2, j, k + 2) - u1(i - 2, j, k + 2)) +
                          c1 * (u1(i + 1, j, k + 2) - u1(i - 1, j, k + 2))) *
                         strx(i) * stry(j) +
                     mu(i, j, k + 2) * met3(i, j, k + 2) * met1(i, j, k + 2) *
                         (c2 * (u2(i + 2, j, k + 2) - u2(i - 2, j, k + 2)) +
                          c1 * (u2(i + 1, j, k + 2) - u2(i - 1, j, k + 2))) +
                     mu(i, j, k + 2) * met4(i, j, k + 2) * met1(i, j, k + 2) *
                         (c2 * (u3(i + 2, j, k + 2) - u3(i - 2, j, k + 2)) +
                          c1 * (u3(i + 1, j, k + 2) - u3(i - 1, j, k + 2))) *
                         stry(j) +
                     ((2 * mu(i, j, k - 2) + la(i, j, k - 2)) *
                          met2(i, j, k - 2) * met1(i, j, k - 2) *
                          (c2 * (u1(i + 2, j, k - 2) - u1(i - 2, j, k - 2)) +
                           c1 * (u1(i + 1, j, k - 2) - u1(i - 1, j, k - 2))) *
                          strx(i) * stry(j) +
                      mu(i, j, k - 2) * met3(i, j, k - 2) * met1(i, j, k - 2) *
                          (c2 * (u2(i + 2, j, k - 2) - u2(i - 2, j, k - 2)) +
                           c1 * (u2(i + 1, j, k - 2) - u2(i - 1, j, k - 2))) +
                      mu(i, j, k - 2) * met4(i, j, k - 2) * met1(i, j, k - 2) *
                          (c2 * (u3(i + 2, j, k - 2) - u3(i - 2, j, k - 2)) +
                           c1 * (u3(i + 1, j, k - 2) - u3(i - 1, j, k - 2))) *
                          stry(j))) +
               c1 * ((2 * mu(i, j, k + 1) + la(i, j, k + 1)) *
                         met2(i, j, k + 1) * met1(i, j, k + 1) *
                         (c2 * (u1(i + 2, j, k + 1) - u1(i - 2, j, k + 1)) +
                          c1 * (u1(i + 1, j, k + 1) - u1(i - 1, j, k + 1))) *
                         strx(i + 2) * stry(j) +
                     mu(i, j, k + 1) * met3(i, j, k + 1) * met1(i, j, k + 1) *
                         (c2 * (u2(i + 2, j, k + 1) - u2(i - 2, j, k + 1)) +
                          c1 * (u2(i + 1, j, k + 1) - u2(i - 1, j, k + 1))) +
                     mu(i, j, k + 1) * met4(i, j, k + 1) * met1(i, j, k + 1) *
                         (c2 * (u3(i + 2, j, k + 1) - u3(i - 2, j, k + 1)) +
                          c1 * (u3(i + 1, j, k + 1) - u3(i - 1, j, k + 1))) *
                         stry(j) +
                     ((2 * mu(i, j, k - 1) + la(i, j, k - 1)) *
                          met2(i, j, k - 1) * met1(i, j, k - 1) *
                          (c2 * (u1(i + 2, j, k - 1) - u1(i - 2, j, k - 1)) +
                           c1 * (u1(i + 1, j, k - 1) - u1(i - 1, j, k - 1))) *
                          strx(i - 2) * stry(j) +
                      mu(i, j, k - 1) * met3(i, j, k - 1) * met1(i, j, k - 1) *
                          (c2 * (u2(i + 2, j, k - 1) - u2(i - 2, j, k - 1)) +
                           c1 * (u2(i + 1, j, k - 1) - u2(i - 1, j, k - 1))) +
                      mu(i, j, k - 1) * met4(i, j, k - 1) * met1(i, j, k - 1) *
                          (c2 * (u3(i + 2, j, k - 1) - u3(i - 2, j, k - 1)) +
                           c1 * (u3(i + 1, j, k - 1) - u3(i - 1, j, k - 1))) *
                          stry(j)));

r1(i, j, k) +=
    (c2 * ((2 * mu(i + 2, j, k) + la(i + 2, j, k)) * met2(i + 2, j, k) *
               met1(i + 2, j, k) *
               (c2 * (u1(i + 2, j, k + 2) - u1(i + 2, j, k - 2)) +
                c1 * (u1(i + 2, j, k + 1) - u1(i + 2, j, k - 1))) *
               strx(i) +
           la(i + 2, j, k) * met3(i + 2, j, k) * met1(i + 2, j, k) *
               (c2 * (u2(i + 2, j, k + 2) - u2(i + 2, j, k - 2)) +
                c1 * (u2(i + 2, j, k + 1) - u2(i + 2, j, k - 1))) *
               stry(j) +
           la(i + 2, j, k) * met4(i + 2, j, k) * met1(i + 2, j, k) *
               (c2 * (u3(i + 2, j, k + 2) - u3(i + 2, j, k - 2)) +
                c1 * (u3(i + 2, j, k + 1) - u3(i + 2, j, k - 1))) +
           ((2 * mu(i - 2, j, k) + la(i - 2, j, k)) * met2(i - 2, j, k) *
                met1(i - 2, j, k) *
                (c2 * (u1(i - 2, j, k + 2) - u1(i - 2, j, k - 2)) +
                 c1 * (u1(i - 2, j, k + 1) - u1(i - 2, j, k - 1))) *
                strx(i) +
            la(i - 2, j, k) * met3(i - 2, j, k) * met1(i - 2, j, k) *
                (c2 * (u2(i - 2, j, k + 2) - u2(i - 2, j, k - 2)) +
                 c1 * (u2(i - 2, j, k + 1) - u2(i - 2, j, k - 1))) *
                stry(j) +
            la(i - 2, j, k) * met4(i - 2, j, k) * met1(i - 2, j, k) *
                (c2 * (u3(i - 2, j, k + 2) - u3(i - 2, j, k - 2)) +
                 c1 * (u3(i - 2, j, k + 1) - u3(i - 2, j, k - 1))))) +
     c1 * ((2 * mu(i + 1, j, k) + la(i + 1, j, k)) * met2(i + 1, j, k) *
               met1(i + 1, j, k) *
               (c2 * (u1(i + 1, j, k + 2) - u1(i + 1, j, k - 2)) +
                c1 * (u1(i + 1, j, k + 1) - u1(i + 1, j, k - 1))) *
               strx(i) +
           la(i + 1, j, k) * met3(i + 1, j, k) * met1(i + 1, j, k) *
               (c2 * (u2(i + 1, j, k + 2) - u2(i + 1, j, k - 2)) +
                c1 * (u2(i + 1, j, k + 1) - u2(i + 1, j, k - 1))) *
               stry(j) +
           la(i + 1, j, k) * met4(i + 1, j, k) * met1(i + 1, j, k) *
               (c2 * (u3(i + 1, j, k + 2) - u3(i + 1, j, k - 2)) +
                c1 * (u3(i + 1, j, k + 1) - u3(i + 1, j, k - 1))) +
           ((2 * mu(i - 1, j, k) + la(i - 1, j, k)) * met2(i - 1, j, k) *
                met1(i - 1, j, k) *
                (c2 * (u1(i - 1, j, k + 2) - u1(i - 1, j, k - 2)) +
                 c1 * (u1(i - 1, j, k + 1) - u1(i - 1, j, k - 1))) *
                strx(i) +
            la(i - 1, j, k) * met3(i - 1, j, k) * met1(i - 1, j, k) *
                (c2 * (u2(i - 1, j, k + 2) - u2(i - 1, j, k - 2)) +
                 c1 * (u2(i - 1, j, k + 1) - u2(i - 1, j, k - 1))) *
                stry(j) +
            la(i - 1, j, k) * met4(i - 1, j, k) * met1(i - 1, j, k) *
                (c2 * (u3(i - 1, j, k + 2) - u3(i - 1, j, k - 2)) +
                 c1 * (u3(i - 1, j, k + 1) - u3(i - 1, j, k - 1)))))) *
    stry(j);

r1(i, j, k) += c2 * (mu(i, j + 2, k) * met3(i, j + 2, k) * met1(i, j + 2, k) *
                         (c2 * (u1(i, j + 2, k + 2) - u1(i, j + 2, k - 2)) +
                          c1 * (u1(i, j + 2, k + 1) - u1(i, j + 2, k - 1))) *
                         stry(j + 1) * strx(i) +
                     mu(i, j + 2, k) * met2(i, j + 2, k) * met1(i, j + 2, k) *
                         (c2 * (u2(i, j + 2, k + 2) - u2(i, j + 2, k - 2)) +
                          c1 * (u2(i, j + 2, k + 1) - u2(i, j + 2, k - 1))) +
                     (mu(i, j - 2, k) * met3(i, j - 2, k) * met1(i, j - 2, k) *
                          (c2 * (u1(i, j - 2, k + 2) - u1(i, j - 2, k - 2)) +
                           c1 * (u1(i, j - 2, k + 1) - u1(i, j - 2, k - 1))) *
                          stry(j) * strx(i) +
                      mu(i, j - 2, k) * met2(i, j - 2, k) * met1(i, j - 2, k) *
                          (c2 * (u2(i, j - 2, k + 2) - u2(i, j - 2, k - 2)) +
                           c1 * (u2(i, j - 2, k + 1) - u2(i, j - 2, k - 1))))) +
               c1 * (mu(i, j + 1, k) * met3(i, j + 1, k) * met1(i, j + 1, k) *
                         (c2 * (u1(i, j + 1, k + 2) - u1(i, j + 1, k - 2)) +
                          c1 * (u1(i, j + 1, k + 1) - u1(i, j + 1, k - 1))) *
                         stry(j - 1) * strx(i) +
                     mu(i, j + 1, k) * met2(i, j + 1, k) * met1(i, j + 1, k) *
                         (c2 * (u2(i, j + 1, k + 2) - u2(i, j + 1, k - 2)) +
                          c1 * (u2(i, j + 1, k + 1) - u2(i, j + 1, k - 1))) +
                     (mu(i, j - 1, k) * met3(i, j - 1, k) * met1(i, j - 1, k) *
                          (c2 * (u1(i, j - 1, k + 2) - u1(i, j - 1, k - 2)) +
                           c1 * (u1(i, j - 1, k + 1) - u1(i, j - 1, k - 1))) *
                          stry(j) * strx(i) +
                      mu(i, j - 1, k) * met2(i, j - 1, k) * met1(i, j - 1, k) *
                          (c2 * (u2(i, j - 1, k + 2) - u2(i, j - 1, k - 2)) +
                           c1 * (u2(i, j - 1, k + 1) - u2(i, j - 1, k - 1)))));

r1(i, j, k) += c2 * (mu(i, j, k + 2) * met3(i, j, k + 2) * met1(i, j, k + 2) *
                         (c2 * (u1(i, j + 2, k + 2) - u1(i, j - 2, k + 2)) +
                          c1 * (u1(i, j + 1, k + 2) - u1(i, j - 1, k + 2))) *
                         stry(j + 2) * strx(i) +
                     la(i, j, k + 2) * met2(i, j, k + 2) * met1(i, j, k + 2) *
                         (c2 * (u2(i, j + 2, k + 2) - u2(i, j - 2, k + 2)) +
                          c1 * (u2(i, j + 1, k + 2) - u2(i, j - 1, k + 2))) +
                     (mu(i, j, k - 2) * met3(i, j, k - 2) * met1(i, j, k - 2) *
                          (c2 * (u1(i, j + 2, k - 2) - u1(i, j - 2, k - 2)) +
                           c1 * (u1(i, j + 1, k - 2) - u1(i, j - 1, k - 2))) *
                          stry(j) * strx(i) +
                      la(i, j, k - 2) * met2(i, j, k - 2) * met1(i, j, k - 2) *
                          (c2 * (u2(i, j + 2, k - 2) - u2(i, j - 2, k - 2)) +
                           c1 * (u2(i, j + 1, k - 2) - u2(i, j - 1, k - 2))))) +
               c1 * (mu(i, j, k + 1) * met3(i, j, k + 1) * met1(i, j, k + 1) *
                         (c2 * (u1(i, j + 2, k + 1) - u1(i, j - 2, k + 1)) +
                          c1 * (u1(i, j + 1, k + 1) - u1(i, j - 1, k + 1))) *
                         stry(j - 2) * strx(i) +
                     la(i, j, k + 1) * met2(i, j, k + 1) * met1(i, j, k + 1) *
                         (c2 * (u2(i, j + 2, k + 1) - u2(i, j - 2, k + 1)) +
                          c1 * (u2(i, j + 1, k + 1) - u2(i, j - 1, k + 1))) +
                     (mu(i, j, k - 1) * met3(i, j, k - 1) * met1(i, j, k - 1) *
                          (c2 * (u1(i, j + 2, k - 1) - u1(i, j - 2, k - 1)) +
                           c1 * (u1(i, j + 1, k - 1) - u1(i, j - 1, k - 1))) *
                          stry(j) * strx(i) +
                      la(i, j, k - 1) * met2(i, j, k - 1) * met1(i, j, k - 1) *
                          (c2 * (u2(i, j + 2, k - 1) - u2(i, j - 2, k - 1)) +
                           c1 * (u2(i, j + 1, k - 1) - u2(i, j - 1, k - 1)))));
