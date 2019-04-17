cmake_minimum_required(VERSION 3.13)
project(BRICKSCUDA LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

find_package(CUDA  REQUIRED)

include_directories("${CUDA_INCLUDE_DIRS}")
include_directories("bricklib/inc")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/bricklib)

add_library(GSRBCuda GSRBCuda.cu GSRBCuda.h)
target_compile_features(GSRBCuda PUBLIC cxx_std_11)
set_target_properties(GSRBCuda PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

add_library(GSRBBricks GSRBBricks.cu GSRBBricks.h)
target_compile_features(GSRBBricks PUBLIC cxx_std_11)
set_target_properties(GSRBBricks PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
target_link_libraries(GSRBBricks brickcore "${OpenMP_CXX_FLAGS}")

add_executable(main main.cpp)

# add_executable(main main.cpp GSRBBricks.cpp)

set_property(TARGET main 
             PROPERTY CUDA_SEPARABLE_COMPILATION ON)
target_link_libraries(main GSRBCuda)
target_link_libraries(main GSRBBricks)
