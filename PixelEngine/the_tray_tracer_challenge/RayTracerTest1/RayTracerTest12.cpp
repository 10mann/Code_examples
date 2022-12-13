#include "pch.h"
#include "CppUnitTest.h"

#include "../the_tray_tracer_challenge/tuple.h"
#include "../the_tray_tracer_challenge/DoubleHelpers.h"
#include "../the_tray_tracer_challenge/color.h"	
#include "../the_tray_tracer_challenge/stripe_pattern.h"	
#include "../the_tray_tracer_challenge/material.h"	
#include "../the_tray_tracer_challenge/point_light.h"
#include "../the_tray_tracer_challenge/ray.h"
#include "../the_tray_tracer_challenge/sphere.h"
#include "../the_tray_tracer_challenge/world.h"
#include "../the_tray_tracer_challenge/matrix.h"
#include "../the_tray_tracer_challenge/plane.h"
#include "../the_tray_tracer_challenge/ray.h"
#include "../the_tray_tracer_challenge/intersection.h"
#include "../the_tray_tracer_challenge/world.h"
#include "../the_tray_tracer_challenge/test_pattern.h"
#include "../the_tray_tracer_challenge/cube.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using RayTracer::Tuple;
using RayTracer::Color;
using RayTracer::StripePattern;
using RayTracer::Material;
using RayTracer::PointLight;
using RayTracer::Sphere;
using RayTracer::Matrix;
using RayTracer::Plane;
using RayTracer::Ray;
using RayTracer::Intersection;
using RayTracer::IntersectionList;
using RayTracer::ComputeValues;
using RayTracer::World;
using RayTracer::Shape;
using RayTracer::TestPattern;
using RayTracer::Cube;

using DoubleHelpers::MATH_PI;
using RayTracer::point;
using RayTracer::vector;
using DoubleHelpers::isEqualDouble;
using RayTracer::getLighting;
using RayTracer::scaling;
using RayTracer::translation;
using RayTracer::createDfaultWorld;
using RayTracer::glassSphere;
using RayTracer::getSchlick;


namespace RayTracerTest12
{
	TEST_CLASS(RayTracerTest12)
	{
	public:
		
		TEST_METHOD(TestRayIntersectCube)
		{
			Logger::WriteMessage("Testing rayIntersectCube");

			Cube cube;
			Ray ray(point(5, 0.5, 0), vector(-1, 0, 0));

			IntersectionList list;
			list.addIntersections(ray, &cube);

			Assert::IsTrue(list.count() == 2);
			Assert::IsTrue(isEqualDouble(list[0].i, 4));
			Assert::IsTrue(isEqualDouble(list[1].i, 6));
		}

		TEST_METHOD(TestRayIntersectCube1)
		{
			Logger::WriteMessage("Testing rayIntersectCube1");

			Cube cube;
			Ray ray(point(-5, 0.5, 0), vector(1, 0, 0));

			IntersectionList list;
			list.addIntersections(ray, &cube);

			Assert::IsTrue(list.count() == 2);
			Assert::IsTrue(isEqualDouble(list[0].i, 4));
			Assert::IsTrue(isEqualDouble(list[1].i, 6));
		}

		TEST_METHOD(TestRayIntersectCube2)
		{
			Logger::WriteMessage("Testing rayIntersectCube2");

			Cube cube;
			Ray ray(point(0.5, 0, -5), vector(0, 0, 1));

			IntersectionList list;
			list.addIntersections(ray, &cube);

			Assert::IsTrue(list.count() == 2);
			Assert::IsTrue(isEqualDouble(list[0].i, 4));
			Assert::IsTrue(isEqualDouble(list[1].i, 6));
		}

		TEST_METHOD(TestRayIntersectCubeInside)
		{
			Logger::WriteMessage("Testing rayIntersectCubeInside");

			Cube cube;
			Ray ray(point(0, 0.5, 0), vector(0, 0, 1));

			IntersectionList list;
			list.addIntersections(ray, &cube);

			Assert::IsTrue(list.count() == 2);
			Assert::IsTrue(isEqualDouble(list[0].i, -1));
			Assert::IsTrue(isEqualDouble(list[1].i, 1));
		}

		TEST_METHOD(TestRayIntersectCubeMiss)
		{
			Logger::WriteMessage("Testing rayIntersectCubeMiss");

			Cube cube;
			Ray ray(point(-2, 0, 0), vector(0, 0, -1));

			IntersectionList list;
			list.addIntersections(ray, &cube);

			Assert::IsTrue(list.count() == 0);
		}

		TEST_METHOD(TestRayIntersectCubeMiss1)
		{
			Logger::WriteMessage("Testing rayIntersectCubeMiss1");

			Cube cube;
			Ray ray(point(2, 1, 0), vector(0, 1, 0));

			IntersectionList list;
			list.addIntersections(ray, &cube);

			Assert::IsTrue(list.count() == 0);
		}

		TEST_METHOD(TestRayIntersectCubeMiss2)
		{
			Logger::WriteMessage("Testing rayIntersectCubeMiss2");

			Cube cube;
			Ray ray(point(0, 0, -3), vector(0, 1, -1));

			IntersectionList list;
			list.addIntersections(ray, &cube);

			Assert::IsTrue(list.count() == 0);
		}

		TEST_METHOD(TestRayIntersectCubeMiss3)
		{
			Logger::WriteMessage("Testing rayIntersectCubeMiss3");

			Cube cube;
			Ray ray(point(-2, 0, 0), vector(0.2637, 0.5345, 0.8018));

			IntersectionList list;
			list.addIntersections(ray, &cube);

			Assert::IsTrue(list.count() == 0);
		}

		TEST_METHOD(TestCubeNormal)
		{
			Logger::WriteMessage("Testing cubeNormal");

			Cube cube;
			Tuple p = point(1, 0.5, -0.8);

			Tuple normal = cube.getNormal(p);

			Assert::IsTrue(normal == vector(1, 0, 0));
		}

		TEST_METHOD(TestCubeNormal1)
		{
			Logger::WriteMessage("Testing cubeNormal1");

			Cube cube;
			Tuple p = point(-1, -0.2, 0.9);

			Tuple normal = cube.getNormal(p);

			Assert::IsTrue(normal == vector(-1, 0, 0));
		}

		TEST_METHOD(TestCubeNormal2)
		{
			Logger::WriteMessage("Testing cubeNormal2");

			Cube cube;
			Tuple p = point(-1, -1, -1);

			Tuple normal = cube.getNormal(p);

			Assert::IsTrue(normal == vector(-1, 0, 0));
		}

		TEST_METHOD(TestCubeNormal3)
		{
			Logger::WriteMessage("Testing cubeNormal3");

			Cube cube;
			Tuple p = point(1, 1, 1);

			Tuple normal = cube.getNormal(p);

			Assert::IsTrue(normal == vector(1, 0, 0));
		}
	};
}