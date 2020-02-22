#pragma once
#include <iostream>
#using <mscorlib.dll>
#include "../CPPStaticLibrary/kmcuda.h"
//#include "../Core2/functionTest.h"

using namespace System;

namespace CLRCoreLibrary {

	public enum class KMCUDAResultM : char {
		kmcudaSuccess = 0,
		kmcudaInvalidArguments,
		kmcudaNoSuchDevice,
		kmcudaMemoryAllocationFailure,
		kmcudaRuntimeError,
		kmcudaMemoryCopyError
	};

	public enum class KMCUDAInitMethodM : char {
		kmcudaInitMethodRandom = 0,
		kmcudaInitMethodPlusPlus,
		kmcudaInitMethodAFKMC2,
		kmcudaInitMethodImport
	};

	public enum class KMCUDADistanceMetricM : char {
		kmcudaDistanceMetricL2,
		kmcudaDistanceMetricCosine
	};

	public ref class KMCudaWrapper
	{
	private:
	public:
		static KMCUDAResultM Clusterize(
			KMCUDAInitMethodM init,
			//Int32 init_params, //const void *init_params,
			System::Single tolerance,
			System::Single yinyang_t,
			KMCUDADistanceMetricM metric, 
			System::UInt32 samples_size,
			System::UInt16 features_size,
			System::UInt32 clusters_size,
			System::UInt32 seed,
			System::UInt32 device,
			System::Int32 device_ptrs,
			System::Boolean fp16x2,
			System::Int32 verbosity,
			array<System::Single, 2>^ samples, // const?
			array<System::Single, 2>^% centroids,
			array<System::UInt32>^% assignments,
			System::Single% average_distance,
			System::Boolean isAdded
		)
		{
			KMCUDAInitMethod unManagedInit = (KMCUDAInitMethod)((int)init);
			KMCUDADistanceMetric unmanagedMetric = (KMCUDADistanceMetric)((int)metric);

			//KMCUDAResult unManagedResult = (KMCUDAResult)(1);
			/*
			pin_ptr<float> uSamples = &samples[0];
			unsigned int uSamplesSize = samples->Length;
			*/
			
			//int clustersSize = 3;
			//int samplesSize = 5;
			//int featuresSize = 2;
			//int N = samplesSize * featuresSize;

			pin_ptr<float> uSamples = &samples[0, 0];
			float *uSamplesBasePtr = uSamples;

			//std::cout << "Samples contents:" << '\n';
			//for (int i = 0; i < N; ++i) {
			//	std::cout << uSamples[i] << '\n';
			//}

			pin_ptr<float> uCentroids = &centroids[0, 0];
			float *uCentroidsBasePtr = uCentroids;
			//unsigned int uCentroidsSize = centroids->Length;
			
			//int centroidsActualSize = clustersSize * featuresSize;
			//std::cout << "Centroids size:" << '\n';
			//std::cout << uCentroidsSize << '\n';
			//std::cout << centroidsActualSize << '\n';
			//
			//for (int i = 0; i < centroidsActualSize; ++i) {
			//	uCentroids[i] = i;
			//}

			pin_ptr<unsigned int> uAssignments = &assignments[0];
			unsigned int *uAssignmentsBasePtr = uAssignments;
			//unsigned int uAssignmentsSize = assignments->Length;

			pin_ptr<float> uAverageDistance = &average_distance;
			float *uAverageDistanceBasePtr = uAverageDistance;
			//unsigned int uAverage_distanceSize = average_distance->Length;
			
			KMCUDAResult unManagedResult = kmeans_cuda(
				unManagedInit,
				NULL, 
				tolerance, 
				yinyang_t,
				unmanagedMetric,
				samples_size,
				features_size,
				clusters_size,
				seed,
				device,
				device_ptrs,
				fp16x2, 
				verbosity, 
				uSamples,
				uCentroids,
				uAssignments,
				uAverageDistance,
				isAdded
			);

			KMCUDAResultM managedResult = static_cast<KMCUDAResultM>(unManagedResult);
			
			return managedResult;
		};
	};
}