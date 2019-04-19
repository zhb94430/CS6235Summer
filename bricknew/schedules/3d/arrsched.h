#pragma omp parallel for collapse(2)
for (long tk = GZ; tk < N + GZ; tk += TILEK)
for (long tj = GZ; tj < N + GZ; tj += TILEJ)
for (long ti = GZ; ti < N + GZ; ti += TILEI)
for (long k = tk; k < tk + TILEK; ++k)
for (long j = tj; j < tj + TILEJ; ++j)
#pragma omp simd
for (long i = ti; i < ti + TILEI; ++i)
