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

using DoubleHelpers::MATH_PI;
using RayTracer::point;
using RayTracer::vector;
using DoubleHelpers::isEqualDouble;
using RayTracer::getLighting;
using RayTracer::scaling;
using RayTracer::translation;
using RayTracer::createDfaultWorld;
using RayTracer::glassSphere;


namespace RayTracerTest11
{
	TEST_CLASS(RayTracerTest11)
	{
	public:

		TEST_METHOD(TestReflectiveProperty)
		{
			Material m;

			Assert::IsTrue(isEqualDouble(0, m.reflective));
		}

		TEST_METHOD(TestReflectVector)
		{
			Plane shape;
			Ray ray(point(0, 1, -1), vector(0, -std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));
			Intersection i(std::sqrt(2), &shape);
			IntersectionList list;
			ComputeValues comp = list.getComputeValues(i, ray);

			Assert::IsTrue(comp.reflectVector == vector(0, std::sqrt(2) / 2, std::sqrt(2) / 2));
		}

		TEST_METHOD(TestNonReflectiveMaterial)
		{
			Logger::WriteMessage("Testing nonReflectiveMaterial");

			World world = createDfaultWorld();
			Ray ray(point(0, 0, 0), vector(0, 0, 1));
			Shape* shape = world.objects[1];
			shape->material.ambient = 1;
			Intersection i(1, shape);
			IntersectionList list;
			ComputeValues comp = list.getComputeValues(i, ray);
			Color c = world.getReflectedColor(comp, 0);

			Assert::IsTrue(c == Color(0, 0, 0));
		}

		TEST_METHOD(TestReflectiveMaterial)
		{
			Logger::WriteMessage("Testing reflectiveMaterial");

			World world = createDfaultWorld();
			Plane plane;
			plane.material.reflective = 0.5;
			plane.setTransform(translation(0, -1, 0));
			world.objects.push_back(&plane);
			Ray ray(point(0, 0, -3), vector(0, -std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));
			Intersection i(std::sqrt(2), &plane);
			IntersectionList list;
			ComputeValues comp = list.getComputeValues(i, ray);
			Color c = world.getHitColor(comp, 0);

			Assert::IsTrue(c == Color(0.87676, 0.92435, 0.82917));
		}

		TEST_METHOD(TestReflectiveMaterialInfiniteRecursion)
		{
			Logger::WriteMessage("Testing reflectiveMaterialInfiniteRecursion");

			World world;
			Plane floor;
			floor.material.reflective = 1;
			floor.setTransform(translation(0, -1, 0));
			world.objects.push_back(&floor);

			Plane roof;
			roof.material.reflective = 1;
			roof.setTransform(translation(0, 1, 0));
			world.objects.push_back(&roof);
			Ray ray(point(0, 0, 0), vector(0, 1, 0));

			Color c = world.getColor(ray, 0);

			Assert::IsTrue(true);
		}

		TEST_METHOD(TestTransparencyAndRefractiveIndex)
		{
			Logger::WriteMessage("Testing transparencyAndRefractiveIndex");

			Material m;
			
			Assert::IsTrue(isEqualDouble(0, m.transparency));
			Assert::IsTrue(isEqualDouble(1.00, m.refractiveIndex));
		}

		TEST_METHOD(TestGlassSphere)
		{
			Logger::WriteMessage("Testing glassSphere");

			Sphere sphere = glassSphere();

			Assert::IsTrue(isEqualDouble(1, sphere.material.transparency));
			Assert::IsTrue(isEqualDouble(REFRACT_GLASS, sphere.material.refractiveIndex));
		}

		TEST_METHOD(TestN1N2Intersect)
		{
			Logger::WriteMessage("Testing findN1N2Intersect");
			Sphere A = glassSphere();
			A.setTransform(scaling(2, 2, 2));
			A.material.refractiveIndex = 1.5;

			Sphere B = glassSphere();
			B.setTransform(translation(0, 0, -0.25));
			B.material.refractiveIndex = 2.0;

			Sphere C = glassSphere();
			C.setTransform(translation(0, 0, 0.25));
			C.material.refractiveIndex = 2.5;

			Ray ray(point(0, 0, -4), vector(0, 0, 1));
			IntersectionList hits;
			hits.addIntersections(ray, &A);
			hits.addIntersections(ray, &B);
			hits.addIntersections(ray, &C);
			hits.sort();

			double n1List[] = 
			{
				1, 1.5, 2, 2.5, 2.5, 1.5
			};

			double n2List[] =
			{
				1.5, 2.0, 2.5, 2.5, 1.5, 1.0
			};

			for (int i = 0; i < hits.count(); i++)
			{
				Intersection hit = hits[i];
				Assert::IsTrue(isEqualDouble(hits.getComputeValues(hit, ray).n1, n1List[i]));
				Assert::IsTrue(isEqualDouble(hits.getComputeValues(hit, ray).n2, n2List[i]));
			}
		}
	};
}