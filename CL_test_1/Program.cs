using System;
using System.ComponentModel.DataAnnotations;
using CLRCoreLibrary;

namespace CL_test_1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");

            var wrapper = new TestWrapper();
            wrapper.DoWork();

            var wrapper2 = new StudentWrapper("Student A", 8.46);
            Console.WriteLine($"Student's name is {wrapper2.Name}");
            Console.WriteLine($"Student's gpa is {wrapper2.Gpa}");

            var display = new Display();
            display.Print("Hello world 2");

            var e = new EntityWrapper("The Wallman", 20, 35);
            e.Move(5, -10);

            var sa = new MyNamesSplitterClass("Firstname Surname");
            sa.Print();

            MyPoint point = new MyPoint();
            point.x = 1;
            point.x = 2;
            point.x = 3;

            var enum1 = SomeColors.Yellow;
            var enum2 = SomeColorsTyped.Yellow;

            sa.Arrays();
            sa.Avg("Result is", 1, 2, 3, 4, 5, 6, 7, 8, 50);

            uint clustersSize = 3;
            float[,] samples = new float[,]
            {
                { 0.9f, 2.75f }, // g1 -> .
                { 0.9f, 2.85f }, // g1 -> g2
                { 1f, 3.1f }, // g2 -> .
                { 1.1f, 2.9f }, // g1 -> g2
                { 0.9f, 4f } // g3 -> .
            };

            uint samplesSize = (uint)samples.GetLength(0);
            ushort featuresSize = (ushort)samples.GetLength(1);

            float[,] centroids = new float[clustersSize, featuresSize];
            uint[] assignments = new uint[samplesSize];
            float avgDistance = 0;

            KMCudaWrapper.Clusterize(
                init: KMCUDAInitMethodM.kmcudaInitMethodPlusPlus,
                tolerance: 0.05f,
                yinyang_t: 0.1f,
                metric: KMCUDADistanceMetricM.kmcudaDistanceMetricL2,
                samples_size: samplesSize,
                features_size: featuresSize,
                clusters_size: clustersSize,
                seed: 777,
                device: 1,
                device_ptrs: -1,
                fp16x2: false,
                verbosity: 2,
                samples: samples,
                centroids: ref centroids,
                assignments: ref assignments,
                average_distance: ref avgDistance,
                false
                );

            Console.WriteLine("End");
        }
    }
}
