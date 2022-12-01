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
			ComputeValues comp = i.getComputeValues(ray);

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
			ComputeValues comp = i.getComputeValues(ray);
			Color c = world.getReflectedColor(comp);

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
			ComputeValues comp = i.getComputeValues(ray);
			Color c = world.getHitColor(comp);

			Assert::IsTrue(c == Color(0.87676, 0.92435, 0.82917));
		}
	};
}