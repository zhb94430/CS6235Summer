out(i    , j    , k    ) = c[ 0] * in(i    , j    , k    )
                         + c[ 1] * in(i - 1, j    , k    )
                         + c[ 2] * in(i + 1, j    , k    )
                         + c[ 3] * in(i    , j - 1, k    )
                         + c[ 4] * in(i    , j + 1, k    )
                         + c[ 5] * in(i    , j    , k - 1)
                         + c[ 6] * in(i    , j    , k + 1);