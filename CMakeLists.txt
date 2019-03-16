cmake_minimum_required(VERSION 3.13)
project(BRICKSCUDA LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 14)

include_directories("bricklib/inc")

add_library(GSRBCuda GSRBCuda.cu)
target_compile_features(GSRBCuda PUBLIC cxx_std_11)
set_target_properties(GSRBCuda PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

add_executable(main main.cpp)
target_link_libraries(GSRBCuda)