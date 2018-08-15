#include <iostream>

#include "brick.h"
#include "omp.h"

int main(int argc, char** argv)
{
    // Set up the Brick 
    

    long n = std::stoi(argv[1]);
    long RZ, RY, RX;
    long BZ, BY, BX;
    sscanf(argv[2], "%ld,%ld,%ld", &RZ, &RY, &RX);
    sscanf(argv[3], "%ld,%ld,%ld", &BZ, &BY, &BX);
    if (n % BDIM_X != 0 || n % BDIM_Y != 0 || n & BDIM_Z != 0)
      std::cerr << "The size of the input dimension is not divisible by the size of the block" << std::endl;
      std::cout << "Benchmark running with " << n << " elements at each dimension for " TOSTRING(_EXAMPLE) << std::endl;
      std::cout << "RZ " << RZ << ";RY " << RY << ";RX " << RX << std::endl;
      std::cout << "BZ " << BZ << ";BY " << BY << ";BX " << BX << std::endl;
      std::cout << "Running with " << omp_get_num_procs() << " procs" << std::endl;
      //  ---- Initialize data ----
      // Brick info
      brick_info binfo(BDIM_Z, BDIM_Y, BDIM_X);
      // Create bricks according to the mapping
      brick_list blist = binfo.genList(n / BDIM_Z + 2, n / BDIM_Y + 2, n / BDIM_X + 2, RZ, RY, RX, BZ, BY, BX);
      

                 
}
