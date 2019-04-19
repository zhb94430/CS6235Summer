#pragma omp parallel for collapse(2)
for (long k = GZ; k < N + GZ; k += TILEK)
for (long j = GZ; j < N + GZ; j += TILEJ)
for (long i = GZ; i < N + GZ; i += TILEI)
