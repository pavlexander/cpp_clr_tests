#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <map>
#include <memory>

#include "kmcuda.h"
#include <iostream>

extern "C" {
    KMCUDAResult kmeans_cuda(
        KMCUDAInitMethod init, const void *init_params, float tolerance, float yinyang_t,
        KMCUDADistanceMetric metric, uint32_t samples_size, uint16_t features_size,
        uint32_t clusters_size, uint32_t seed, uint32_t device, int32_t device_ptrs,
        int32_t fp16x2, int32_t verbosity, const float *samples, float *centroids,
        uint32_t *assignments, float *average_distance, bool isAdded)
    {
        std::cout << "Alghoritm finished" << std::endl;
        int das;
        int32_t dass;
        return kmcudaSuccess;
    }
}  // extern "C"
