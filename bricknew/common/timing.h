#define TIMELIMIT 5

compute();

double st = omp_get_wtime();
double ed = st;

long iter = 1;

while (st + TIMELIMIT > ed) {
    for (long i = 0; i < iter; ++i)
        compute();
    iter *= 2;
    ed = omp_get_wtime();
}

std::cout << (ed - st) / (iter - 1) << std::endl;
