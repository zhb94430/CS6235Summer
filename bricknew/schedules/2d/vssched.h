#pragma omp parallel for
for (long j = GZ; j < N + GZ; j += TILEJ)
for (long i = GZ; i < N + GZ; i += TILEI)
