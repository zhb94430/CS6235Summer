//
// Created by Tuowen Zhao on 3/5/18.
//

#include "brick-cuda.h"

void cuda_send(brick &dev, brick &host) {
  auto sz = (size_t) (host.info->bri_n * host.elem_sz * host.step);
  cudaCheck(cudaMemcpy(dev.dat, host.dat, sz, cudaMemcpyHostToDevice));
}

void cuda_recv(brick &host, brick &dev) {
  auto sz = (size_t) (host.info->bri_n * host.elem_sz * host.step);
  cudaCheck(cudaMemcpy(host.dat, dev.dat, sz, cudaMemcpyDeviceToHost));
}

void cuda_send(brickd &dev, brickd &host) {
  cudaCheck(cudaMemcpy(dev.dat, host.dat, host.info->bri_n * host.info->bri_sz * sizeof(float),
                       cudaMemcpyHostToDevice));
}

void cuda_recv(brickd &host, brickd &dev) {
  cudaCheck(cudaMemcpy(host.dat, dev.dat, host.info->bri_n * host.info->bri_sz * sizeof(float),
                       cudaMemcpyDeviceToHost));
}

brick_list cuda_copy(brick_list &host) {
  brick_list dev = host;
  cudaCheck(cudaMalloc(&dev.rdat, (dev.rlen + 1) * sizeof(long)));
  cudaCheck(cudaMemcpy(dev.rdat, host.rdat, (dev.rlen + 1) * sizeof(long), cudaMemcpyHostToDevice));
  cudaCheck(cudaMalloc(&dev.bdat, (host.rdat[dev.rlen] + 1) * sizeof(long)));
  cudaCheck(cudaMemcpy(dev.bdat, host.bdat, (host.rdat[dev.rlen] + 1) * sizeof(long), cudaMemcpyHostToDevice));
  cudaCheck(cudaMalloc(&dev.dat, dev.len * sizeof(long)));
  cudaCheck(cudaMemcpy(dev.dat, host.dat, dev.len * sizeof(long), cudaMemcpyHostToDevice));
  return dev;
}

brick_info *cuda_copy(brick_info *host) {
  if (host->dev_ptr != nullptr)
    return host->dev_ptr;
  brick_info dev = *host;
  cudaCheck(cudaMalloc(&dev.adj, host->bri_n * sizeof(long) * 26));
  cudaCheck(cudaMemcpy(dev.adj, host->adj, host->bri_n * sizeof(long) * 26, cudaMemcpyHostToDevice));
  cudaCheck(cudaMalloc(&(host->dev_ptr), sizeof(brick_info)));
  cudaCheck(cudaMemcpy(host->dev_ptr, &dev, sizeof(brick_info), cudaMemcpyHostToDevice));
  return host->dev_ptr;
}

brickd cuda_copy(brickd &host) {
  brickd dev = host;
  dev.info = cuda_copy(host.info);
  cudaCheck(cudaMalloc(&dev.dat, host.info->bri_n * host.info->bri_sz * sizeof(float)));
  cuda_send(dev, host);
  return dev;
}

brick cuda_copy(brick &host) {
  brick dev = host;
  dev.info = cuda_copy(host.info);
  auto sz = (size_t) (host.info->bri_n * host.elem_sz * host.step);
  cudaCheck(cudaMalloc(&dev.dat, sz));
  cuda_send(dev, host);
  return dev;
}

void cuda_free(brick_list &dev) {
  cudaFree(dev.rdat);
  cudaFree(dev.bdat);
  cudaFree(dev.dat);
}