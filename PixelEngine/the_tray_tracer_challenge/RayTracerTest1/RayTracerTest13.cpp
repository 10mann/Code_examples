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
#include "../the_tray_tracer_challenge/cylinder.h"
#include "../the_tray_tracer_challenge/cone.h"


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
using RayTracer::Cylinder;
using RayTracer::Cone;

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


namespace RayTracerTest13
{
	TEST_CLASS(RayTracerTest13)
	{
	public:

		TEST_METHOD(TestMissCylinder1)
		{
			Logger::WriteMessage("Testing missCylinder1");

			Cylinder cylinder;
			Ray ray(point(1, 0, 0), vector(0, 1, 0));

			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 0);
		}

		TEST_METHOD(TestMissCylinder2)
		{
			Logger::WriteMessage("Testing missCylinder2");

			Cylinder cylinder;
			Ray ray(point(0, 0, 0), vector(0, 1, 0));

			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 0);
		}

		TEST_METHOD(TestMissCylinder3)
		{
			Logger::WriteMessage("Testing missCylinder3");

			Cylinder cylinder;
			Ray ray(point(0, 0, -5), vector(1, 1, 1).getNormalized());

			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 0);
		}

		TEST_METHOD(TestHitCylinder1)
		{
			Logger::WriteMessage("Testing hitCylinder1");

			Cylinder cylinder;
			Ray ray(point(1, 0, -5), vector(0, 0, 1).getNormalized());

			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 2);
			Assert::IsTrue(DoubleHelpers::isEqualDouble(5, list[0].i));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(5, list[1].i));
		}

		TEST_METHOD(TestHitCylinder2)
		{
			Logger::WriteMessage("Testing hitCylinder2");

			Cylinder cylinder;
			Ray ray(point(0, 0, -5), vector(0, 0, 1).getNormalized());

			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 2);
			Assert::IsTrue(DoubleHelpers::isEqualDouble(4, list[0].i));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(6, list[1].i));
		}

		TEST_METHOD(TestHitCylinder3)
		{
			Logger::WriteMessage("Testing hitCylinder3");

			Cylinder cylinder;
			Ray ray(point(0.5, 0, -5), vector(0.1, 1, 1).getNormalized());

			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 2);
			Assert::IsTrue(DoubleHelpers::isEqualDouble(6.80798, list[0].i));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(7.08872, list[1].i));
		}

		TEST_METHOD(TestCylinderNormal1)
		{
			Logger::WriteMessage("Testing cylinderNormal1");

			Cylinder cylinder;
			Tuple normal = cylinder.getNormal(point(1, 0, 0));

			Assert::IsTrue(normal == vector(1, 0, 0));
		}

		TEST_METHOD(TestCylinderNormal2)
		{
			Logger::WriteMessage("Testing cylinderNormal2");

			Cylinder cylinder;
			Tuple normal = cylinder.getNormal(point(0, 5, -1));

			Assert::IsTrue(normal == vector(0, 0, -1));
		}

		TEST_METHOD(TestCylinderNormal3)
		{
			Logger::WriteMessage("Testing cylinderNormal3");

			Cylinder cylinder;
			Tuple normal = cylinder.getNormal(point(0, -2, 1));

			Assert::IsTrue(normal == vector(0, 0, 1));
		}

		TEST_METHOD(TestCylinderNormal4)
		{
			Logger::WriteMessage("Testing cylinderNormal4");

			Cylinder cylinder;
			Tuple normal = cylinder.getNormal(point(-1, 1, 0));

			Assert::IsTrue(normal == vector(-1, 0, 0));
		}

		TEST_METHOD(TestCylinderDefaultMinMax)
		{
			Logger::WriteMessage("Testing cylinderDefaultMinMax");

			Cylinder cylinder;

			Assert::IsTrue(((INFINITY - 1) <= cylinder.maxY));
			Assert::IsTrue(((-INFINITY + 1) >= cylinder.minY));
		}

		TEST_METHOD(TestMissCylinderTruncated1)
		{
			Logger::WriteMessage("Testing missCylinderTruncated1");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;

			Ray ray(point(0, 1.5, 0), vector(0.1, 1, 0).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 0);
		}

		TEST_METHOD(TestMissCylinderTruncated2)
		{
			Logger::WriteMessage("Testing missCylinderTruncated2");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;

			Ray ray(point(0, 3, -5), vector(0, 0, 1).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 0);
		}

		TEST_METHOD(TestMissCylinderTruncated3)
		{
			Logger::WriteMessage("Testing missCylinderTruncated3");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;

			Ray ray(point(0, 0, -5), vector(0, 0, 1).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 0);
		}

		TEST_METHOD(TestMissCylinderTruncated4)
		{
			Logger::WriteMessage("Testing missCylinderTruncated4");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;

			Ray ray(point(0, 2, -5), vector(0, 0, 1).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 0);
		}

		TEST_METHOD(TestMissCylinderTruncated5)
		{
			Logger::WriteMessage("Testing missCylinderTruncated5");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;

			Ray ray(point(0, 1, -5), vector(0, 0, 1).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 0);
		}

		TEST_METHOD(TestHitCylinderTruncated)
		{
			Logger::WriteMessage("Testing hitCylinderTruncated");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;

			Ray ray(point(0, 1.5, -2), vector(0, 0, 1).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 2);
		}

		TEST_METHOD(TestCylinderClosed)
		{
			Logger::WriteMessage("Testing cylinderClosed");

			Cylinder cylinder;

			Assert::IsFalse(cylinder.closed);
		}

		TEST_METHOD(TestHitCylinderClosed)
		{
			Logger::WriteMessage("Testing hitCylinderClosed");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;
			cylinder.closed = true;

			Ray ray(point(0, 3, 0), vector(0, -1, 0).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 2);
		}

		TEST_METHOD(TestHitCylinderClosed1)
		{
			Logger::WriteMessage("Testing hitCylinderClosed1");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;
			cylinder.closed = true;

			Ray ray(point(0, 3, -2), vector(0, -1, 2).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 2);
		}

		TEST_METHOD(TestHitCylinderClosed2)
		{
			Logger::WriteMessage("Testing hitCylinderClosed2");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;
			cylinder.closed = true;

			Ray ray(point(0, 4, -2), vector(0, -1, 1).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 2);
		}

		TEST_METHOD(TestHitCylinderClosed3)
		{
			Logger::WriteMessage("Testing hitCylinderClosed3");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;
			cylinder.closed = true;

			Ray ray(point(0, 0, -2), vector(0, 1, 2).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 2);
		}

		TEST_METHOD(TestHitCylinderClosed4)
		{
			Logger::WriteMessage("Testing hitCylinderClosed4");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;
			cylinder.closed = true;

			Ray ray(point(0, -1, -2), vector(0, 1, 1).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cylinder);

			Assert::IsTrue(list.count() == 2);
		}

		TEST_METHOD(TestNormalCylinderClosed)
		{
			Logger::WriteMessage("Testing normalCylinderClosed");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;
			cylinder.closed = true;

			Tuple normal = cylinder.getNormal(point(0, 1, 0));

			Assert::IsTrue(normal == vector(0, -1, 0));
		}

		TEST_METHOD(TestNormalCylinderClosed1)
		{
			Logger::WriteMessage("Testing normalCylinderClosed1");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;
			cylinder.closed = true;

			Tuple normal = cylinder.getNormal(point(0.5, 1, 0));

			Assert::IsTrue(normal == vector(0, -1, 0));
		}

		TEST_METHOD(TestNormalCylinderClosed2)
		{
			Logger::WriteMessage("Testing normalCylinderClosed2");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;
			cylinder.closed = true;

			Tuple normal = cylinder.getNormal(point(0, 1, 0.5));

			Assert::IsTrue(normal == vector(0, -1, 0));
		}

		TEST_METHOD(TestNormalCylinderClosed3)
		{
			Logger::WriteMessage("Testing normalCylinderClosed3");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;
			cylinder.closed = true;

			Tuple normal = cylinder.getNormal(point(0, 2, 0));

			Assert::IsTrue(normal == vector(0, 1, 0));
		}

		TEST_METHOD(TestNormalCylinderClosed4)
		{
			Logger::WriteMessage("Testing normalCylinderClosed4");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;
			cylinder.closed = true;

			Tuple normal = cylinder.getNormal(point(0.5, 2, 0));

			Assert::IsTrue(normal == vector(0, 1, 0));
		}

		TEST_METHOD(TestNormalCylinderClosed5)
		{
			Logger::WriteMessage("Testing normalCylinderClosed5");

			Cylinder cylinder;
			cylinder.minY = 1;
			cylinder.maxY = 2;
			cylinder.closed = true;

			Tuple normal = cylinder.getNormal(point(0, 2, 0.5));

			Assert::IsTrue(normal == vector(0, 1, 0));
		}

		TEST_METHOD(TestHitCone)
		{
			Logger::WriteMessage("Testing hitCone");

			Cone cone;

			Ray ray(point(0, 0, -5), vector(0, 0, 1).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cone);

			Assert::IsTrue(list.count() == 2);
			Assert::IsTrue(isEqualDouble(5.0000, 5.0));
			Assert::IsTrue(isEqualDouble(list[1].i, 5.0));
		}

		TEST_METHOD(TestHitCone1)
		{
			Logger::WriteMessage("Testing hitCone1");

			Cone cone;

			Ray ray(point(0, 0, -5), vector(1, 1, 1).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cone);

			Assert::IsTrue(list.count() == 2);
			Assert::IsTrue(DoubleHelpers::isEqualDouble(list[0].i, 8.66025));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(list[1].i, 8.66025));
		}

		TEST_METHOD(TestHitCone2)
		{
			Logger::WriteMessage("Testing hitCone2");

			Cone cone;

			Ray ray(point(1, 1, -5), vector(-0.5, -1, 1).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cone);

			Assert::IsTrue(list.count() == 2);
			Assert::IsTrue(DoubleHelpers::isEqualDouble(list[0].i, 4.55006));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(list[1].i, 49.44994));
		}

		TEST_METHOD(TestHitConeParallell)
		{
			Logger::WriteMessage("Testing hitConeParallell");

			Cone cone;

			Ray ray(point(0, 0, -1), vector(0, 1, 1).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cone);

			Assert::IsTrue(list.count() == 1);
			Assert::IsTrue(isEqualDouble(list[0].i, 0.35355));
		}

		TEST_METHOD(TestHitoneClosed)
		{
			Logger::WriteMessage("Testing hitCylinderClosed");

			Cone cone;
			cone.minY = -0.5;
			cone.maxY = 0.5;
			cone.closed = true;

			Ray ray(point(0, 0, -5), vector(0, 1, 0).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cone);

			Assert::IsTrue(list.count() == 0);
		}

		TEST_METHOD(TestHitoneClosed1)
		{
			Logger::WriteMessage("Testing hitCylinderClosed1");

			Cone cone;
			cone.minY = -0.5;
			cone.maxY = 0.5;
			cone.closed = true;

			Ray ray(point(0, 0, -0.25), vector(0, 1, 1).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cone);

			Assert::IsTrue(list.count() == 2);
		}

		TEST_METHOD(TestHitoneClosed2)
		{
			Logger::WriteMessage("Testing hitCylinderClosed2");

			Cone cone;
			cone.minY = -0.5;
			cone.maxY = 0.5;
			cone.closed = true;

			Ray ray(point(0, 0, -0.25), vector(0, 1, 0).getNormalized());
			IntersectionList list;
			list.addIntersections(ray, &cone);

			Assert::IsTrue(list.count() == 4);
		}

		//TEST_METHOD(TestNormalCone)
		//{
		//	Logger::WriteMessage("Testing normalCone");

		//	Cone cone;

		//	Tuple normal = cone.getNormal(point(0, 0, 0));

		//	Assert::IsTrue(normal == vector(0, 0, 0));
		//}

		//TEST_METHOD(TestNormalCone1)
		//{
		//	Logger::WriteMessage("Testing normalCone1");

		//	Cone cone;

		//	Tuple normal = cone.getNormal(point(1, 1, 1));

		//	Assert::IsTrue(normal == vector(1, -sqrt(2), 1));
		//}

		//TEST_METHOD(TestNormalCone2)
		//{
		//	Logger::WriteMessage("Testing normalCone2");

		//	Cone cone;

		//	Tuple normal = cone.getNormal(point(-1, -1, 0));

		//	Assert::IsTrue(normal == vector(-1, 1, 0));
		//}
	};
}