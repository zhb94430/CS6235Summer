out(i    , j    ) = c[ 0] * in(i - 1, j - 1)
                  + c[ 1] * in(i    , j - 1)
                  + c[ 2] * in(i + 1, j - 1)
                  + c[ 3] * in(i - 1, j    )
                  + c[ 4] * in(i    , j    )
                  + c[ 5] * in(i + 1, j    )
                  + c[ 6] * in(i - 1, j + 1)
                  + c[ 7] * in(i    , j + 1)
                  + c[ 8] * in(i + 1, j + 1);
