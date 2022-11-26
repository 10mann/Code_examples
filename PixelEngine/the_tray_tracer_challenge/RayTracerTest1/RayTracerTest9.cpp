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
#include "../the_tray_tracer_challenge/test_shape.h"
#include "../the_tray_tracer_challenge/plane.h"


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
using RayTracer::TestShape;
using RayTracer::Plane;
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

namespace RayTracerTest9
{
	TEST_CLASS(RayTracerTest9)
	{
	public:
		TEST_METHOD(TestGetTestShape)
		{
			Logger::WriteMessage("Testing getTestShape");

			TestShape s;

			Assert::IsTrue(s.transform == Matrix::identityMatrix);
		}

		TEST_METHOD(TestTestShapeSetTransform)
		{
			Logger::WriteMessage("Testing TestShapeSetTransform");

			TestShape s;
			s.setTransform(translation(2, 3, 4));

			Assert::IsTrue(s.transform == translation(2, 3, 4));
		}

		TEST_METHOD(TestTestShapeDefaultMaterial)
		{
			Logger::WriteMessage("Testing TestShapeDefaultMaterial");

			TestShape s;

			Assert::IsTrue(s.material == Material());
		}

		TEST_METHOD(TestTestShapeMaterial)
		{
			Logger::WriteMessage("Testing TestShapeMaterial");

			TestShape s;
			Material m;
			m.ambient = 1;

			s.material = m;

			Assert::IsTrue(s.material == m);
		}

		TEST_METHOD(TestTestPlaneNormal)
		{
			Logger::WriteMessage("Testing TestPlaneNormal");

			Plane plane;
			Tuple n1 = plane.getNormal(point(0, 0, 0));
			Tuple n2 = plane.getNormal(point(10, 0, -10));
			Tuple n3 = plane.getNormal(point(-5, 0, 150));

			Assert::IsTrue(n1 == vector(0, 1, 0));
			Assert::IsTrue(n2 == vector(0, 1, 0));
			Assert::IsTrue(n3 == vector(0, 1, 0));
		}

		TEST_METHOD(TestPlaneParallell)
		{
			Logger::WriteMessage("Testing planeParallell");

			Plane p;
			Ray ray(point(0, 10, 0), vector(0, 0, 1));
			IntersectionList intersects;
			intersects.addIntersections(ray, &p);

			Assert::IsTrue(intersects.count() == 0);
		}

		TEST_METHOD(TestPlaneCoplanar)
		{
			Logger::WriteMessage("Testing planeCoplanar");

			Plane p;
			Ray ray(point(0, 0, 0), vector(0, 0, 1));
			IntersectionList intersects;
			intersects.addIntersections(ray, &p);

			Assert::IsTrue(intersects.count() == 0);
		}

		TEST_METHOD(TestPlaneIntersectFromAbove)
		{
			Logger::WriteMessage("Testing planeIntersectFromAbove");

			Plane p;
			Ray ray(point(0, 1, 0), vector(0, -1, 0));
			IntersectionList intersects;
			intersects.addIntersections(ray, &p);

			Assert::IsTrue(intersects.count() == 1);
			Assert::IsTrue(isEqualDouble(intersects[0].i, 1));
			Assert::IsTrue(intersects[0].object == &p);
		}

		TEST_METHOD(TestPlaneIntersectFromBelow)
		{
			Logger::WriteMessage("Testing planeIntersectFromBelow");

			Plane p;
			Ray ray(point(0, -1, 0), vector(0, 1, 0));
			IntersectionList intersects;
			intersects.addIntersections(ray, &p);

			Assert::IsTrue(intersects.count() == 1);
			Assert::IsTrue(isEqualDouble(intersects[0].i, 1));
			Assert::IsTrue(intersects[0].object == &p);
		}
	};
}