#include "rnghelp.h"

namespace {
    std::mt19937_64 *mt = nullptr;
    std::uniform_real_distribution<bElem> *u = nullptr;
}

#pragma omp threadprivate(mt)
#pragma omp threadprivate(u)

bElem randD() {
    if (mt == nullptr) {
        #pragma omp critical
        {
            std::random_device r;
            mt = new std::mt19937_64(r());
            u = new std::uniform_real_distribution<bElem>(0, 1);
        }
    }
    return (*u)(*mt);
}

