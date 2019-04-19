#pragma omp parallel for
for (long tj = GZ; tj < N + GZ; tj += TILEJ)
for (long ti = GZ; ti < N + GZ; ti += TILEI)
for (long j = tj; j < tj + TILEJ; ++j)
#pragma omp simd
for (long i = ti; i < ti + TILEI; ++i)
