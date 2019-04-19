#if _TILEK == 1
long tk = GZ + blockIdx.z * TILEK;
#else
long k = GZ + blockIdx.z * TILEK + threadIdx.z;
#endif

#if _TILEJ == 1
long tj = GZ + blockIdx.y * TILEJ;
#else
long j = GZ + blockIdx.y * TILEJ + threadIdx.y;
#endif

long i = GZ + blockIdx.x * TILEI + threadIdx.x;

#if _TILEK == 1
for (long k = tk; k < tk + TILEK; ++k)
#endif
#if _TILEJ == 1
for (long j = tj; j < tj + TILEJ; ++j)
#endif
