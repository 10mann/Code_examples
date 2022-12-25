#include "benchmarks.h"

using RayTracer::Matrix;
using RayTracer::Tuple;
using RayTracer::Ray;
using RayTracer::Sphere;
using RayTracer::Intersection;
using RayTracer::IntersectionList;
using RayTracer::World;
using RayTracer::Material;
using RayTracer::Color;
using RayTracer::PointLight;
using RayTracer::Canvas;
using RayTracer::ComputeValues;
using RayTracer::Camera;
using RayTracer::Cube;

using RayTracer::rotationX;
using RayTracer::rotationY;
using RayTracer::rotationZ;
using RayTracer::translation;
using RayTracer::scaling;
using RayTracer::getLighting;
using RayTracer::createDfaultWorld;

using DoubleHelpers::MATH_PI;

namespace RayTracer
{
	void benchmarkMatrixMult(void)
	{
		RayTracer::Matrix matrix1;
		matrix1[0][0] = 1;
		matrix1[0][1] = 2;
		matrix1[0][2] = 3;
		matrix1[0][3] = 4;
		matrix1[1][0] = 5;
		matrix1[1][1] = 6;
		matrix1[1][2] = 7;
		matrix1[1][3] = 8;
		matrix1[2][0] = 9;
		matrix1[2][1] = 8;
		matrix1[2][2] = 7;
		matrix1[2][3] = 6;
		matrix1[3][0] = 5;
		matrix1[3][1] = 4;
		matrix1[3][2] = 3;
		matrix1[3][3] = 2;

		RayTracer::Matrix matrix2;
		matrix2[0][0] = -2;
		matrix2[0][1] = 1;
		matrix2[0][2] = 2;
		matrix2[0][3] = 3;
		matrix2[1][0] = 3;
		matrix2[1][1] = 2;
		matrix2[1][2] = 1;
		matrix2[1][3] = -1;
		matrix2[2][0] = 4;
		matrix2[2][1] = 3;
		matrix2[2][2] = 6;
		matrix2[2][3] = 5;
		matrix2[3][0] = 1;
		matrix2[3][1] = 2;
		matrix2[3][2] = 7;
		matrix2[3][3] = 8;

		RayTracer::Matrix matrix3 = matrix1 * matrix2;
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::microseconds(0));
		long long avgDuration = 0;
		const int testTimes = 100;
		for (int times = 0; times < testTimes; times++)
		{
			auto start = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < 1000000; i++)
			{
				matrix3 = matrix1 * matrix2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
			avgDuration += duration.count();
		}

		avgDuration /= testTimes;

		std::cout << "Exectuion time: " << avgDuration << std::endl;
	}

	long long benchmarkDrawSphere(int iterations)
	{
		int width = 680;
		int height = 680;
		Canvas canvas(width, height);
		Sphere s;
		s.material = Material();
		s.material.color = Color(0.25, 0.74, 0.96);
		s.material.shininess = 200;
		PointLight light(Color(1, 1, 1), RayTracer::point(0, 0, -10));

		double wallZ = 10;
		Tuple origin = RayTracer::point(0, 0, -5);
		//double wallSize = ((wallZ - origin.z) / std::abs(origin.z)) * 2 + 1;
		double wallSize = 10;
		double pixelSizeY = wallSize / height;
		double pixelSizeX = wallSize / height;
		auto timeStart = std::chrono::high_resolution_clock::now();
		for (int it = 0; it < iterations; it++)
		{
			for (int y = 0; y < height; y++)
			{
				double worldY = (wallSize / 2) - (pixelSizeY * y);
				for (int x = 0; x < width; x++)
				{
					double worldX = -(wallSize / 2) + (pixelSizeX * x);
					Tuple wallPoint = RayTracer::point(worldX, worldY, wallZ);
					Tuple dir = (wallPoint - origin);
					dir.normalize();
					Ray ray(origin, dir);
					//IntersectionList hits = ray.getIntersection(&s);
					IntersectionList hits;
					hits.addIntersections(ray, &s);
					if (hits.count() > 0)
					{
						Intersection hit = hits.hit();
						//ComputeValues compValues = ray.getComputeValues(hit);
						ComputeValues compValues = hits.getComputeValues(hit, ray);
						Color pixelColor = getLighting(compValues.object, light, compValues.point, compValues.eyeDir, compValues.normal, false);
						//Tuple hitPos = ray.getPosition(hit.i);
						//Tuple normal = s.getNormal(hitPos);
						//Tuple eyeDir = -ray.direction;
						//Color pixelColor = getLighting(hit.object.material, light, hitPos, eyeDir, normal, false);
						int16_t colorR = pixelColor.red * 255;
						if (colorR > 255)
						{
							colorR = 255;
						}

						int16_t colorG = pixelColor.green * 255;
						if (colorG > 255)
						{
							colorG = 255;
						}

						int16_t colorB = pixelColor.blue * 255;
						if (colorB > 255)
						{
							colorB = 255;
						}
						canvas.writePixel(x, y, pixelColor);
					}
				}
			}
		}
		auto timeEnd = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);


		return duration.count();
	}

	long long benchmarkMatrixMult(int iterations)
	{
		double values1[] =
		{
			-2, -8, 3, 5,
			-3, 1, 7, 3,
			1, 2, -9, 6,
			-6, 7, 7, -9
		};
		Matrix m1(4, 4, values1);

		double values2[] =
		{
			6, 4, 4, 4,
			5, 5, 7, 6,
			4, -9, 3, -7,
			9, 1, 7, -6
		};
		Matrix m2(4, 4, values2);

		Matrix m3;

		auto timeStart = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < iterations; i++)
		{
			m3 = m1 * m2;
		}

		m3.print();

		auto timeEnd = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);

		return duration.count();
	}

	long long benchmarkGetDistance(int iterations)
	{
		Tuple p1 = point(1, 2, 3);
		Tuple p2 = point(4, 5, 6);

		Tuple v = p2 - p1;
		double distance = 0;

		auto timeStart = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < iterations; i++)
		{
			distance = v.getMagnitude();
			//distance = v.getMagnitudeSquared();
		}

		auto timeEnd = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);

		return duration.count();
	}

	long long benchmarkIsInShadow(int iterations)
	{
		World world = createDfaultWorld();
		Tuple p = point(10, -10, 10);
		bool isInShadow = false;

		auto timeStart = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < iterations; i++)
		{
			isInShadow = world.isInShadow(p, world.lights[0]);
		}

		auto timeEnd = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);
		return duration.count();
	}

	long long benchmarkGetInverse(int iterations)
	{
		double values[] =
		{
			6, 4, 4, 4,
			5, 5, 7, 6,
			4, -9, 3, -7,
			9, 1, 7, -6
		};
		Matrix m(4, 4, values);

		Matrix m2;

		auto timeStart = std::chrono::steady_clock::now();

		for (int i = 0; i < iterations; i++)
		{
			m2 = m.getInverse();
		}

		auto timeEnd = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);

		m2.print();

		return duration.count();
	}

	long long benchmarkGetSubMatrix(int iterations)
	{
		double values[] =
		{
			6, 4, 4, 4,
			5, 5, 7, 6,
			4, -9, 3, -7,
			9, 1, 7, -6
		};
		Matrix m(4, 4, values);

		Matrix m2;

		auto timeStart = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < iterations; i++)
		{
			m2 = m.getSubMatrix(0, 0);
		}

		auto timeEnd = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);


		m2.print();


		return duration.count();
	}

	long long benchmarkCompareCubeIntersect(int iterations)
	{
		//Cube cube;

		//Ray ray(point(5, 0.5, 0), vector(-1, 0, 0));
		//std::vector<double> intersects;

		//auto timeStart = std::chrono::high_resolution_clock::now();
		//for (int i = 0; i < iterations; i++)
		//{
		//	intersects = cube.getIntersectTime(ray);
		//}
		//auto timeEnd = std::chrono::high_resolution_clock::now();
		//auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);

		//intersects[0] += 1;

		//return duration.count();
		return 0;
	}
}
