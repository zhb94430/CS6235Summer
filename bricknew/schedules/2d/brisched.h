#pragma omp parallel for
for (long j = GZ / TILEJ; j < (N + GZ) / TILEJ; ++j)
for (long i = GZ / TILEI; i < (N + GZ) / TILEI; ++i)
