#if _TILEJ == 1
long tj = GZ + blockIdx.y * TILEJ;
#else
long j = GZ + blockIdx.y * TILEJ + threadIdx.y;
#endif

long i = GZ + blockIdx.x * TILEI + threadIdx.x;

#if _TILEJ == 1
for (long j = tj; j < tj + TILEJ; ++j)
#endif
