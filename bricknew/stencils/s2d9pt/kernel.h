out(i    , j    ) = c[ 0] * in(i    , j    )
                  + c[ 1] * in(i - 2, j    )
                  + c[ 2] * in(i - 1, j    )
                  + c[ 3] * in(i + 1, j    )
                  + c[ 4] * in(i + 2, j    )
                  + c[ 5] * in(i    , j - 2)
                  + c[ 6] * in(i    , j - 1)
                  + c[ 7] * in(i    , j + 1)
                  + c[ 8] * in(i    , j + 2);
