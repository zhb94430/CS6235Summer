cmake_minimum_required(VERSION 3.7)
project(bricklib)

set(CMAKE_CXX_STANDARD 11)

find_package(CUDA REQUIRED)
SET(CUDA_SEPARABLE_COMPILATION ON)

set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-std=c++11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=gnu99")

find_package(MPI REQUIRED)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

if (NOT DEFINED EXAMPLE)
    set(EXAMPLE iso3dfd)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -D_EX_${EXAMPLE}")

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${MPI_INCLUDE_PATH}
)

set(LIB_FILES src/brick.cpp src/brick_rect.cpp)

set(EXAMPLE_FILES stencils/stencil_example.cpp stencils/other_example.cpp
        stencils/iso3dfd_generated.cpp stencils/iso3dfd.cpp stencils/cns.cpp)

add_library(brickcore ${LIB_FILES})

add_library(brickexample ${EXAMPLE_FILES})

add_library(brickmpi src/mpi/brick-mpi.cpp)

cuda_add_library(brickcuda src/cuda/brick-cuda.cpp)

add_executable(brick-test main.cpp)
target_link_libraries(brick-test brickcore brickexample)

add_executable(san-check san-check.cpp)
target_link_libraries(san-check brickcore brickexample)

add_executable(mpi-main mpi-main.cpp)
target_link_libraries(mpi-main brickcore brickmpi brickexample ${MPI_CXX_LIBRARIES})

cuda_add_executable(cuda-main cuda-main.cpp stencils/iso3dfd_cuda.cu)
target_link_libraries(cuda-main brickcore brickcuda)

install(TARGETS brickcore
        ARCHIVE DESTINATION lib)

install(TARGETS brickmpi
        ARCHIVE DESTINATION lib)

install(TARGETS brickcuda
        ARCHIVE DESTINATION lib)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/inc/
        DESTINATION include
        FILES_MATCHING PATTERN "*.h")

add_custom_target(test-single
        COMMAND ${CMAKE_BINARY_DIR}/brick-test 72 4,4,4 1,1,1
        # COMMAND ${CMAKE_BINARY_DIR}/brick-test 136 4,4,4 1,1,1
        COMMAND ${CMAKE_BINARY_DIR}/san-check 72 4,4,4 1,1,1
        DEPENDS brick-test san-check)

add_custom_target(test-all
        COMMAND ${CMAKE_COMMAND} --build . -- test-single
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
