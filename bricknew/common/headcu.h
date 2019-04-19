#include "brick-cuda.h"
#include "cudaarray.h"

#define _TILEK TILEK
#define _TILEJ TILEJ
#define _TILEI TILEI

typedef Brick<Dim<TILEJ, TILEI>, Dim<BFOLD>> Brick2D;

typedef Brick<Dim<TILEK, TILEJ, TILEI>, Dim<BFOLD>> Brick3D;
