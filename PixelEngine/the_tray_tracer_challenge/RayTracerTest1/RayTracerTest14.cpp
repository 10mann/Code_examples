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
#include "../the_tray_tracer_challenge/group.h"


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
using RayTracer::Group;

using DoubleHelpers::MATH_PI;
using RayTracer::point;
using RayTracer::vector;
using DoubleHelpers::isEqualDouble;
using RayTracer::getLighting;
using RayTracer::scaling;
using RayTracer::translation;
using RayTracer::rotationX;
using RayTracer::rotationY;
using RayTracer::rotationZ;
using RayTracer::createDfaultWorld;
using RayTracer::glassSphere;
using RayTracer::getSchlick;


namespace RayTracerTest14
{
	TEST_CLASS(RayTracerTest14)
	{
	public:

		TEST_METHOD(TestGroupDefault)
		{
			Logger::WriteMessage("Testing groupDefault");

			Group group;

			Assert::IsTrue(group.transform == Matrix::identityMatrix);
			Assert::IsTrue(group.objects.size() == 0);
		}

		TEST_METHOD(TestDefaultParent)
		{
			Logger::WriteMessage("Testing defaultParent");

			Cube cube;

			Assert::IsTrue(cube.parent == nullptr);
		}

		TEST_METHOD(TestAddChild)
		{
			Logger::WriteMessage("Testing defaultParent");

			Group group;
			Cube cube;

			group.addChild(&cube);

			Assert::IsTrue(cube.parent == &group);
			Assert::IsTrue(group.objects.size() == 1);
			Assert::IsTrue(group.objects[0] == &cube);
		}

		TEST_METHOD(TestIntersectEmptyGroup)
		{
			Logger::WriteMessage("Testing intersectEmptyGroup");

			Group group;
			IntersectionList list;
			Ray ray(point(0, 0, 0), vector(0, 0, 1));

			list.addIntersections(ray, &group);

			Assert::IsTrue(list.count() == 0);
		}

		TEST_METHOD(TestIntersectFilledGroup)
		{
			Logger::WriteMessage("Testing intersectFilledGroup");

			Group group;
			IntersectionList list;
			Ray ray(point(0, 0, -5), vector(0, 0, 1));
			Sphere s1;
			Sphere s2;
			Sphere s3;

			s2.setTransform(translation(0, 0, -3));
			s3.setTransform(translation(5, 0, 0));

			group.addChild(&s1);
			group.addChild(&s2);
			group.addChild(&s3);

			list.addIntersections(ray, &group);

			Assert::IsTrue(list.count() == 4);
			Assert::IsTrue(list[0].object == &s2);
			Assert::IsTrue(list[1].object == &s2);
			Assert::IsTrue(list[2].object == &s1);
			Assert::IsTrue(list[3].object == &s1);
		}

		TEST_METHOD(TestGroupTransform)
		{
			Logger::WriteMessage("Testing groupTransform");

			Group group;
			group.setTransform(scaling(2, 2, 2));

			Sphere s;
			s.setTransform(translation(5, 0, 0));

			group.addChild(&s);
			Ray ray(point(10, 0, -10), vector(0, 0, 1));

			IntersectionList list;
			list.addIntersections(ray, &group);

			Assert::IsTrue(list.count() == 2);
		}

		TEST_METHOD(TestWorldToObjectSpace)
		{
			Logger::WriteMessage("Testing worldToObjectSpace");

			Group g1;
			g1.setTransform(rotationY(DoubleHelpers::MATH_PI / 2));

			Group g2;
			g2.setTransform(scaling(2, 2, 2));
			g1.addChild(&g2);

			Sphere s;
			s.setTransform(translation(5, 0, 0));
			g2.addChild(&s);

			Tuple p = s.worldToObjectSpace(point(-2, 0, -10));

			Assert::IsTrue(p == point(0, 0, -1));
		}

		TEST_METHOD(TestNormalToWorldSpace)
		{
			Logger::WriteMessage("Testing normalToWorldSpace");

			Group g1;
			g1.setTransform(rotationY(DoubleHelpers::MATH_PI / 2));

			Group g2;
			g2.setTransform(scaling(1, 2, 3));
			g1.addChild(&g2);

			Sphere s;
			s.setTransform(translation(5, 0, 0));
			g2.addChild(&s);

			Tuple n = s.normalToWorld(vector(std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3));

			Assert::IsTrue(n == vector(0.285714, 0.42857, -0.85714));
		}

		TEST_METHOD(TestNormalChildObject)
		{
			Logger::WriteMessage("Testing normalChildObject");

			Group g1;
			g1.setTransform(rotationY(DoubleHelpers::MATH_PI / 2));

			Group g2;
			g2.setTransform(scaling(1, 2, 3));
			g1.addChild(&g2);

			Sphere s;
			s.setTransform(translation(5, 0, 0));
			g2.addChild(&s);

			Tuple n = s.getNormal(point(1.7321, 1.1547, -5.5774));

			Assert::IsTrue(n == vector(0.28570, 0.42854, -0.85716));
		}
	};
}