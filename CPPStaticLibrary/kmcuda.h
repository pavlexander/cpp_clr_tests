//Project: https://github.com/src-d/kmcuda

#include <stdint.h>

typedef enum {
  kmcudaSuccess = 0,
  kmcudaInvalidArguments,
  kmcudaNoSuchDevice,
  kmcudaMemoryAllocationFailure,
  kmcudaRuntimeError,
  kmcudaMemoryCopyError
} KMCUDAResult;

typedef enum {
  kmcudaInitMethodRandom = 0,
  kmcudaInitMethodPlusPlus,
  kmcudaInitMethodAFKMC2,
  kmcudaInitMethodImport
} KMCUDAInitMethod;

typedef enum {
  kmcudaDistanceMetricL2,
  kmcudaDistanceMetricCosine
} KMCUDADistanceMetric;

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Performs K-means clustering on GPU / CUDA.
/// @param init centroids initialization method.
/// @param init_params pointer to a struct / number with centroid initialization
///                    parameters. Ignored unless init == kmcudaInitMethodAFKMC2.
///                    In case with kmcudaInitMethodAFKMC2 it is expected to be
///                    uint32_t* to m; m == 0 means the default value (200).
/// @param tolerance if the number of reassignments drop below this ratio, stop.
/// @param yinyang_t the relative number of cluster groups, usually 0.1.
/// @param metric the distance metric to use. The default is Euclidean (L2), can be
///               changed to cosine to behave as Spherical K-means with the angular
///               distance. Please note that samples *must* be normalized in that
///               case.
/// @param samples_size number of samples.
/// @param features_size number of features (vector dimensionality).
/// @param clusters_size number of clusters.
/// @param seed random generator seed passed to srand().
/// @param device used CUDA device mask. E.g., 1 means #0, 2 means #1 and 3 means
///               #0 and #1. n-th bit corresponds to n-th device.
/// @param device_ptrs If negative, input and output pointers are taken from host;
///                    otherwise, device number where to load and store data.
/// @param fp16x2 If true, the input is treated as half2 instead of float. In that case,
///               features_size must be 2 times smaller than the real size.
/// @param verbosity 0 - no output; 1 - progress output; >=2 - debug output.
/// @param samples input array of size samples_size x features_size in row major format.
/// @param centroids output array of centroids of size clusters_size x features_size
///                  in row major format.
/// @param assignments output array of cluster indices for each sample of size
///                    samples_size x 1.
/// @param average_distance output mean distance between cluster elements and
///                         the corresponding centroids. If nullptr, not calculated.
/// @return KMCUDAResult.
KMCUDAResult kmeans_cuda(
    KMCUDAInitMethod init, const void *init_params, float tolerance, float yinyang_t,
    KMCUDADistanceMetric metric, uint32_t samples_size, uint16_t features_size,
    uint32_t clusters_size, uint32_t seed, uint32_t device, int32_t device_ptrs,
    int32_t fp16x2, int32_t verbosity, const float *samples, float *centroids,
    uint32_t *assignments, float *average_distance, bool isAdded);

#ifdef __cplusplus
}  // extern "C"
#endif

#ifdef __cplusplus
#include <string>
#include <unordered_map>

namespace {
    namespace kmcuda {
        /// Mapping from strings to KMCUDAInitMethod - useful for wrappers.
        const std::unordered_map<std::string, KMCUDAInitMethod> init_methods {
            {"kmeans++", kmcudaInitMethodPlusPlus},
            {"k-means++", kmcudaInitMethodPlusPlus},
            {"afkmc2", kmcudaInitMethodAFKMC2},
            {"afk-mc2", kmcudaInitMethodAFKMC2},
            {"random", kmcudaInitMethodRandom}
        };

        /// Mapping from strings to KMCUDADistanceMetric - useful for wrappers.
        const std::unordered_map<std::string, KMCUDADistanceMetric> metrics {
            {"euclidean", kmcudaDistanceMetricL2},
            {"L2", kmcudaDistanceMetricL2},
            {"l2", kmcudaDistanceMetricL2},
            {"cos", kmcudaDistanceMetricCosine},
            {"cosine", kmcudaDistanceMetricCosine},
            {"angular", kmcudaDistanceMetricCosine}
        };

        /// Mapping from KMCUDAResult to strings - useful for wrappers.
        const std::unordered_map<int, const char *> statuses {
            {kmcudaSuccess, "Success"},
            {kmcudaInvalidArguments, "InvalidArguments"},
            {kmcudaNoSuchDevice, "NoSuchDevice"},
            {kmcudaMemoryAllocationFailure, "MemoryAllocationFailure"},
            {kmcudaRuntimeError, "RuntimeError"},
            {kmcudaMemoryCopyError, "MemoryCopyError"}
        };
    }  // namespace kmcuda
}  // namespace
#endif  // __cplusplus
