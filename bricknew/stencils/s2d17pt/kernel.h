out(i    , j    ) = c[ 0] * in(i    , j    )
                  + c[ 1] * in(i - 4, j    )
                  + c[ 2] * in(i - 3, j    )
                  + c[ 3] * in(i - 2, j    )
                  + c[ 4] * in(i - 1, j    )
                  + c[ 5] * in(i + 1, j    )
                  + c[ 6] * in(i + 2, j    )
                  + c[ 7] * in(i + 3, j    )
                  + c[ 8] * in(i + 4, j    )
                  + c[ 9] * in(i    , j - 4)
                  + c[10] * in(i    , j - 3)
                  + c[11] * in(i    , j - 2)
                  + c[12] * in(i    , j - 1)
                  + c[13] * in(i    , j + 1)
                  + c[14] * in(i    , j + 2)
                  + c[15] * in(i    , j + 3)
                  + c[16] * in(i    , j + 4);