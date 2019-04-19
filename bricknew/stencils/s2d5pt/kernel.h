out(i    , j    ) = c[ 0] * in(i    , j    )
                  + c[ 1] * in(i - 1, j    )
                  + c[ 2] * in(i + 1, j    )
                  + c[ 3] * in(i    , j - 1)
                  + c[ 4] * in(i    , j + 1);
