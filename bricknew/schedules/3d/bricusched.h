unsigned k = GZ / TILEK + blockIdx.z;
unsigned j = GZ / TILEJ + blockIdx.y;
unsigned i = GZ / TILEI + blockIdx.x;

unsigned b = grid[k][j][i];
