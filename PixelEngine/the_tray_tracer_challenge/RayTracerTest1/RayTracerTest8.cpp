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
#include "../the_tray_tracer_challenge/camera.h"
#include "../the_tray_tracer_challenge/canvas.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using RayTracer::Ray;
using RayTracer::Tuple;
using RayTracer::Color;
using RayTracer::Material;
using RayTracer::Matrix;
using RayTracer::Sphere;
using RayTracer::Intersection;
using RayTracer::IntersectionList;
using DoubleHelpers::MATH_PI;
using RayTracer::PointLight;
using RayTracer::World;
using RayTracer::ComputeValues;
using RayTracer::Camera;
using RayTracer::Canvas;
using RayTracer::point;
using RayTracer::vector;
using RayTracer::createDfaultWorld;
using RayTracer::getLighting;
using RayTracer::translation;
using RayTracer::scaling;
using RayTracer::rotationX;
using RayTracer::rotationY;
using RayTracer::rotationZ;
using RayTracer::getReflection;
using DoubleHelpers::isEqualDouble;
using RayTracer::viewTransform;

namespace RayTracerTest8
{
	TEST_CLASS(RayTracerTest8)
	{
	public:

		TEST_METHOD(TestGetLightingInShadow)
		{
			Logger::WriteMessage("Testing getShadowInLighting");

			Material m;
			Tuple position = point(0, 0, 0);
			Tuple eyeDir = vector(0, 0, -1);
			Tuple normal = vector(0, 0, -1);
			PointLight light = PointLight(Color(1, 1, 1), point(0, 0, -10));
			Color lighting = getLighting(m, light, position, eyeDir, normal, true);

			Assert::IsTrue(lighting == Color(0.1, 0.1, 0.1));
		}

		TEST_METHOD(TestIsPointInShadowFalse1)
		{
			Logger::WriteMessage("Testing pointInShadowFalse1");

			World world = createDfaultWorld();
			Tuple p = point(0, 10, 0);
			bool isInShadow = world.isInShadow(p, world.lights[0]);

			Assert::IsFalse(isInShadow);
		}

		TEST_METHOD(TestIsPointInShadowTrue1)
		{
			Logger::WriteMessage("Testing pointInShadowTrue1");

			World world = createDfaultWorld();
			world.calculateInverseTransforms();
			Tuple p = point(10, -10, 10);
			bool isInShadow = world.isInShadow(p, world.lights[0]);

			Assert::IsTrue(isInShadow);
		}

		TEST_METHOD(TestIsPointInShadowFalse2)
		{
			Logger::WriteMessage("Testing pointInShadowFalse2");

			World world = createDfaultWorld();
			Tuple p = point(-20, 20, -20);
			bool isInShadow = world.isInShadow(p, world.lights[0]);

			Assert::IsFalse(isInShadow);
		}

		TEST_METHOD(TestIsPointInShadowFalse3)
		{
			Logger::WriteMessage("Testing pointInShadowFalse3");

			World world = createDfaultWorld();
			Tuple p = point(-2, 2, -2);
			bool isInShadow = world.isInShadow(p, world.lights[0]);

			Assert::IsFalse(isInShadow);
		}

		TEST_METHOD(TestIsSphereIsInShadow)
		{
			Logger::WriteMessage("Testing sphereIsInShadow");

			World world;
			world.lights.push_back(PointLight(Color(1, 1, 1), point(0, 0, -10)));

			Sphere s1;
			world.objects.push_back(s1);

			Sphere s2;
			s2.transform = translation(0, 0, 10);
			world.objects.push_back(s2);

			Ray ray(point(0, 0, 5), vector(0, 0, 1));
			world.calculateInverseTransforms();

			Intersection intersect(4, s2);

			ComputeValues compValues = ray.getComputeValues(intersect);

			Color color = world.getHitColor(compValues);

			Assert::IsTrue(color == Color(0.1, 0.1, 0.1));
		}

		TEST_METHOD(TestOffsetShadowPoint)
		{
			Logger::WriteMessage("Testing offsetShadowPoint");

			Ray ray(point(0, 0, -5), vector(0, 0, 1));
			Sphere s1;
			s1.setTransform(translation(0, 0, 1));
			Intersection i(5, s1);
			ComputeValues compValues = ray.getComputeValues(i);

			Assert::IsTrue(compValues.overPoint.z < -(DoubleHelpers::EPSILON) / 2);
			Assert::IsTrue(compValues.overPoint.z < compValues.point.z);
		}
	};
}