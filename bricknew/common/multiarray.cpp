#include "multiarray.h"
#include "cmpconst.h"
#include "rnghelp.h"
#include <iostream>

bElem *uninitArray(const std::vector<long> &list, long &size) {
    size = 1;
    for (auto i: list)
        size *= i;
    return (bElem *)aligned_alloc(_MA_ALIGNMENT, size * sizeof(bElem));
}

bElem *randomArray(const std::vector<long> &list) {
    long size;
    bElem* arr = uninitArray(list, size);
    #pragma omp parallel for
    for (long l = 0; l < size; ++l)
        arr[l] = randD();
    return arr;
}

bElem *zeroArray(const std::vector<long> &list) {
    long size;
    bElem* arr = uninitArray(list, size);
    #pragma omp parallel for
    for (long l = 0; l < size; ++l)
        arr[l] = 0.0;
    return arr;
}

bool compareArray(const std::vector<long> &list, bElem *arrA, bElem *arrB) {
    long size = 1;
    for (auto i: list)
        size *= i;
    bool same = true;
    #pragma omp parallel for reduction(&&: same)
    for (long l = 0; l < size; ++l) {
        bElem diff = std::abs(arrA[l] - arrB[l]);
        bool r = (diff < CMP_ERR) || (diff < (std::abs(arrA[l]) + std::abs(arrB[l])) * CMP_ERR);
        same = same && r;
    }
    return same;
}
