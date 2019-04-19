#ifndef MULTIARRAY_H
#define MULTIARRAY_H
#define _MA_ALIGNMENT 4096
#include <vector>
#include "defs.h"

bElem *uninitArray(const std::vector<long> &list, long &size);

bElem *randomArray(const std::vector<long> &list);

bElem *zeroArray(const std::vector<long> &list);

bool compareArray(const std::vector<long> &list, bElem *arrA, bElem *arrB);

#endif
