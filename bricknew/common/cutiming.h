#define TIMEITER 100

compute(); // Warm up
cudaEvent_t start, stop;
float elapsed;
cudaDeviceSynchronize();
cudaEventCreate(&start);
cudaEventCreate(&stop);
cudaEventRecord(start);
for (int i = 0; i < TIMEITER; ++i)
    compute();
cudaEventRecord(stop);
cudaEventSynchronize(stop);
cudaEventElapsedTime(&elapsed, start, stop);
std::cout << elapsed / TIMEITER / 1000 << std::endl;
