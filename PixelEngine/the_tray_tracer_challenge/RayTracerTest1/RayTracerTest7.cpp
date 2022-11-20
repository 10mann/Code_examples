#include "pch.h"
#include "CppUnitTest.h"
#include "../the_tray_tracer_challenge/matrix.h"
#include "../the_tray_tracer_challenge/tuple.h"
#include "../the_tray_tracer_challenge/DoubleHelpers.h"
#include "../the_tray_tracer_challenge/ray.h"
#include "../the_tray_tracer_challenge/sphere.h"
#include "../the_tray_tracer_challenge/intersection.h"
#include "../the_tray_tracer_challenge/intersection_list.h"
#include "../the_tray_tracer_challenge/color.h"	
#include "../the_tray_tracer_challenge/point_light.h"	
#include "../the_tray_tracer_challenge/material.h"	
#include "../the_tray_tracer_challenge/world.h"	


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using RayTracer::Ray;
using RayTracer::Tuple;
using RayTracer::point;
using RayTracer::vector;
using RayTracer::Color;
using RayTracer::Material;
using RayTracer::Matrix;
using RayTracer::Sphere;
using RayTracer::Intersection;
using RayTracer::IntersectionList;
using DoubleHelpers::isEqualDouble;
using DoubleHelpers::MATH_PI;
using RayTracer::translation;
using RayTracer::scaling;
using RayTracer::rotationX;
using RayTracer::rotationY;
using RayTracer::rotationZ;
using RayTracer::getReflection;
using RayTracer::PointLight;
using RayTracer::getLighting;
using RayTracer::World;
using RayTracer::createDfaultWorld;
using RayTracer::ComputeValues;

namespace RayTracerTest6
{
	TEST_CLASS(RayTracerTest6)
	{
	public:

		TEST_METHOD(TestCreateWorld)
		{
			Logger::WriteMessage("Testing createWorld");
			World world;

			Assert::IsTrue(world.objects.size() == 0);
			Assert::IsTrue(world.lights.size() == 0);
		}

		TEST_METHOD(TestCreateDefaultWorld)
		{
			Logger::WriteMessage("Testing createDefaultWorld");
			World world = createDfaultWorld();

			PointLight light(Color(1, 1, 1), point(-10, 10, -10));

			Sphere s1;
			Material m;
			m.color = Color(0.8, 1, 0.6);
			m.diffuse = 0.7;
			m.specular = 0.2;
			s1.material = m;

			Sphere s2;
			s2.transform = scaling(0.5, 0.5, 0.5);

			Assert::IsTrue(world.objects.size() == 2);
			Assert::IsTrue(world.lights.size() == 1);
			Assert::IsTrue(world.containsObject(s1));
			Assert::IsTrue(world.containsObject(s2));
			Assert::IsTrue(world.containsLight(light));
		}

		TEST_METHOD(TestWorldRayIntersect)
		{
			Logger::WriteMessage("Testing worldRayIntersect");
			World world = createDfaultWorld();
			Ray ray(point(0, 0, -5), vector(0, 0, 1));
			IntersectionList intersections = world.getIntersections(ray);

			Assert::IsTrue(intersections.count() == 4);

			Assert::IsTrue(isEqualDouble(intersections[0].i, 4));
			Assert::IsTrue(isEqualDouble(intersections[1].i, 4.5));
			Assert::IsTrue(isEqualDouble(intersections[2].i, 5.5));
			Assert::IsTrue(isEqualDouble(intersections[3].i, 6));
		}

		TEST_METHOD(TestGetIntersectValues)
		{
			Logger::WriteMessage("Testing getIntersectValues");
			World world = createDfaultWorld();
			Ray ray(point(0, 0, -5), vector(0, 0, 1));
			Sphere s;
			Intersection intersection(4, s);
			ComputeValues computeValues = ray.getComputeValues(intersection);

			Assert::IsTrue(isEqualDouble (computeValues.i, intersection.i));
			Assert::IsTrue(computeValues.object == intersection.object);
			Assert::IsTrue(computeValues.point == point(0, 0, -1));
			Assert::IsTrue(computeValues.eyeDir == vector(0, 0, -1));
			Assert::IsTrue(computeValues.normal == vector(0, 0, -1));
		}

		TEST_METHOD(TestCheckRayInsideObjectFalse)
		{
			Logger::WriteMessage("Testing checkRayInsideObjectFalse");
			World world = createDfaultWorld();
			Ray ray(point(0, 0, -5), vector(0, 0, 1));
			Sphere s;
			Intersection intersection(4, s);
			ComputeValues computeValues = ray.getComputeValues(intersection);

			Assert::IsTrue((computeValues.inside == false));
		}

		TEST_METHOD(TestCheckRayInsideObjectTrue)
		{
			Logger::WriteMessage("Testing checkRayInsideObjectTrue");
			World world = createDfaultWorld();
			Ray ray(point(0, 0, 0), vector(0, 0, 1));
			Sphere s;
			Intersection intersection(1, s);
			ComputeValues computeValues = ray.getComputeValues(intersection);

			Assert::IsTrue((computeValues.inside == true));
			Assert::IsTrue(computeValues.object == intersection.object);
			Assert::IsTrue(computeValues.point == point(0, 0, 1));
			Assert::IsTrue(computeValues.eyeDir == vector(0, 0, -1));
			Assert::IsTrue(computeValues.normal == vector(0, 0, -1));
		}

		TEST_METHOD(TestGetHitColor)
		{
			Logger::WriteMessage("Testing getHitColor");
			World world = createDfaultWorld();
			Ray ray(point(0, 0, -5), vector(0, 0, 1));
			Sphere s = world.objects[0];
			Intersection intersection(4, s);
			ComputeValues computeValues = ray.getComputeValues(intersection);
			Color color = world.getHitColor(computeValues);

			Assert::IsTrue(color == Color(0.38066, 0.47583, 0.2855));
		}

		TEST_METHOD(TestGetHitColorInside)
		{
			Logger::WriteMessage("Testing getHitColorInside");
			World world = createDfaultWorld();
			world.lights[0] = PointLight(Color(1, 1, 1), point(0, 0.25, 0));
			Ray ray(point(0, 0, 0), vector(0, 0, 1));
			Sphere s = world.objects[1];
			Intersection intersection(0.5, s);
			ComputeValues computeValues = ray.getComputeValues(intersection);
			Color color = world.getHitColor(computeValues);

			Assert::IsTrue(color == Color(0.90498, 0.90498, 0.90498));
		}

		TEST_METHOD(TestGetColorWorldMiss)
		{
			Logger::WriteMessage("Testing getColorWorldMiss");
			World world = createDfaultWorld();
			Ray ray(point(0, 0, -5), vector(0, 1, 0));

			Color color = world.getColor(ray);

			Assert::IsTrue(color == Color(0, 0, 0));
		}

		TEST_METHOD(TestGetColorWorldHit)
		{
			Logger::WriteMessage("Testing getColorWorldHit");
			World world = createDfaultWorld();
			Ray ray(point(0, 0, -5), vector(0, 0, 1));

			Color color = world.getColor(ray);

			Assert::IsTrue(color == Color(0.38066, 0.47583, 0.2855));
		}
	};
}