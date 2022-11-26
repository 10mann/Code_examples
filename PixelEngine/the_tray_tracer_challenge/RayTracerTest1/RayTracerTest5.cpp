#include "pch.h"
#include "CppUnitTest.h"
#include "../the_tray_tracer_challenge/matrix.h"
#include "../the_tray_tracer_challenge/tuple.h"
#include "../the_tray_tracer_challenge/DoubleHelpers.h"
#include "../the_tray_tracer_challenge/ray.h"
#include "../the_tray_tracer_challenge/sphere.h"
#include "../the_tray_tracer_challenge/intersection.h"
#include "../the_tray_tracer_challenge/intersection_list.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using RayTracer::Ray;
using RayTracer::Tuple;
using RayTracer::point;
using RayTracer::vector;
using RayTracer::Matrix;
using RayTracer::Sphere;
using RayTracer::Intersection;
using RayTracer::IntersectionList;
using DoubleHelpers::isEqualDouble;
using RayTracer::translation;
using RayTracer::scaling;

namespace RayTracerTest5
{
	TEST_CLASS(RayTracerTest5)
	{
	public:

		TEST_METHOD(TestCreateRay)
		{
			Logger::WriteMessage("Testing createRay");
			Tuple origin = point(1, 2, 3);
			Tuple direction = vector(4, 5, 6);
			Ray ray(origin, direction);

			Assert::IsTrue(ray.origin == origin);
			Assert::IsTrue(ray.direction == direction);
		}

		TEST_METHOD(TestShootRay)
		{
			Logger::WriteMessage("Testing shootRay");
			Ray ray(point(2, 3, 4), vector(1, 0, 0));

			Assert::IsTrue(ray.getPosition(0) == point(2, 3, 4));
			Assert::IsTrue(ray.getPosition(1) == point(3, 3, 4));
			Assert::IsTrue(ray.getPosition(2) == point(4, 3, 4));
			Assert::IsTrue(ray.getPosition(2.5) == point(4.5, 3, 4));
			Assert::IsTrue(ray.getPosition(3) == point(5, 3, 4));
			Assert::IsTrue(ray.getPosition(-1) == point(1, 3, 4));
		}

		//TEST_METHOD(TestIntersectSphereUnit)
		//{
		//	Logger::WriteMessage("Testing intersectSphereUnit");
		//	Ray ray(point(0, 0, -5), vector(0, 0, 1));
		//	Sphere sphere;
		//	
		//	std::vector<double> intersections = ray.getIntersection(sphere);
		//	Assert::IsTrue(2U == intersections.size());
		//	Assert::IsTrue(isEqualDouble(intersections[0], 4));
		//	Assert::IsTrue(isEqualDouble(intersections[1], 6));
		//}

		//TEST_METHOD(TestIntersectSphereUnitTangent)
		//{
		//	Logger::WriteMessage("Testing intersectSphereUnitTangent");
		//	Ray ray(point(0, 1, -5), vector(0, 0, 1));
		//	Sphere sphere;

		//	std::vector<double> intersections = ray.getIntersection(sphere);
		//	Assert::IsTrue(2U == intersections.size());
		//	Assert::IsTrue(isEqualDouble(intersections[0], 5));
		//	Assert::IsTrue(isEqualDouble(intersections[1], 5));
		//}

		//TEST_METHOD(TestIntersectSphereUnitInside)
		//{
		//	Logger::WriteMessage("Testing intersectSphereUnitInside");
		//	Ray ray(point(0, 0, 0), vector(0, 0, 1));
		//	Sphere sphere;

		//	std::vector<double> intersections = ray.getIntersection(sphere);
		//	Assert::IsTrue(2U == intersections.size());
		//	Assert::IsTrue(isEqualDouble(intersections[0], -1));
		//	Assert::IsTrue(isEqualDouble(intersections[1], 1));
		//}

		//TEST_METHOD(TestIntersectSphereUnitBehind)
		//{
		//	Logger::WriteMessage("Testing intersectSphereUnitBehind");
		//	Ray ray(point(0, 0, 5), vector(0, 0, 1));
		//	Sphere sphere;

		//	std::vector<double> intersections = ray.getIntersection(sphere);
		//	Assert::IsTrue(2U == intersections.size());
		//	Assert::IsTrue(isEqualDouble(intersections[0], -6));
		//	Assert::IsTrue(isEqualDouble(intersections[1], -4));
		//}

		TEST_METHOD(TestCreateIntersection)
		{
			Logger::WriteMessage("Testing createIntersection");
			Sphere sphere;
			Intersection intersection(3.5, &sphere);
			Assert::IsTrue(isEqualDouble(intersection.i, 3.5));
			Assert::IsTrue(sphere == *intersection.object);
		}

		TEST_METHOD(TestCreateIntersectionList)
		{
			Logger::WriteMessage("Testing createIntersectionList");
			Sphere sphere;
			Intersection intersection1(1, &sphere);
			Intersection intersection2(2, &sphere);

			IntersectionList intersections(intersection1, intersection2);
			Assert::IsTrue(intersections.count() == 2);
			Assert::IsTrue(sphere == *intersections[0].object);
			Assert::IsTrue(sphere == *intersections[1].object);
			Assert::IsTrue(isEqualDouble(1, intersections[0].i));
			Assert::IsTrue(isEqualDouble(2, intersections[1].i));
		}

		TEST_METHOD(TestGetIntersections)
		{
			Logger::WriteMessage("Testing getIntersections");
			Ray ray(point(0, 0, -5), vector(0, 0, 1));
			Sphere sphere;

			//IntersectionList intersections = ray.getIntersection(&sphere);
			IntersectionList intersections;
			intersections.addIntersections(ray, &sphere);
			Assert::IsTrue((*intersections[0].object == sphere));
			Assert::IsTrue((*intersections[1].object == sphere));
		}

		TEST_METHOD(TestGetHit)
		{
			Logger::WriteMessage("Testing getHit");
			Sphere sphere;
			Intersection i1(1, &sphere);
			Intersection i2(2, &sphere);
			IntersectionList list(i1, i2);
			Intersection iHit = list.hit();
			Assert::IsTrue(iHit == i1);
		}

		TEST_METHOD(TestGetHitOneInvalid)
		{
			Logger::WriteMessage("Testing getHitOneInvalid");
			Sphere sphere;
			Intersection i1(-1, &sphere);
			Intersection i2(2, &sphere);
			IntersectionList list(i1, i2);
			Intersection iHit = list.hit();
			Assert::IsTrue(iHit == i2);
		}

		TEST_METHOD(TestGetHitAllInvalid)
		{
			Logger::WriteMessage("Testing getHitAllInvalid");
			Sphere sphere;
			Intersection i1(-1, &sphere);
			Intersection i2(-2, &sphere);
			IntersectionList list(i1, i2);
			Intersection iHit = list.hit();
			Assert::IsTrue(iHit == Intersection::empty);
		}

		TEST_METHOD(TestGetHitFourIntersects)
		{
			Logger::WriteMessage("Testing getHitFourIntersects");
			Sphere sphere;
			Intersection i1(5, &sphere);
			Intersection i2(7, &sphere);
			Intersection i3(-3, &sphere);
			Intersection i4(2, &sphere);
			IntersectionList list(i1, i2);
			list.add(i3);
			list.add(i4);
			Intersection iHit = list.hit();
			Assert::IsTrue(iHit == i4);
		}

		TEST_METHOD(TestTransformRay)
		{
			Logger::WriteMessage("Testing TransformRay");
			Ray ray(point(1, 2, 3), vector(0, 1, 0));

			Matrix m = translation(3, 4, 5);
			Ray ray2 = ray.transform(m);

			Assert::IsTrue(ray2.origin == point(4, 6, 8));
			Assert::IsTrue(ray2.direction == vector(0, 1, 0));
		}

		TEST_METHOD(TestScaleRay)
		{
			Logger::WriteMessage("Testing scaleRay");
			Ray ray(point(1, 2, 3), vector(0, 1, 0));

			Matrix m = scaling(2, 3, 4);
			Ray ray2 = ray.transform(m);

			Assert::IsTrue(ray2.origin == point(2, 6, 12));
			Assert::IsTrue(ray2.direction == vector(0, 3, 0));
		}

		TEST_METHOD(TestSphereNoTransform)
		{
			Logger::WriteMessage("Testing sphereNoTransform");
			Sphere sphere;
			Assert::IsTrue(sphere.transform == Matrix::identityMatrix);
		}

		TEST_METHOD(TestSphereSetTransform)
		{
			Logger::WriteMessage("Testing sphereSetTransform");
			Sphere sphere;
			Matrix m = translation(2, 3, 4);
			sphere.setTransform(m);
			sphere.invTransform = sphere.transform.getInverse();
			Assert::IsTrue(sphere.transform == m);
		}

		TEST_METHOD(TestSphereIntersectTransformedScaled)
		{
			Logger::WriteMessage("Testing sphereIntersectTransformedScaled");
			Ray ray(point(0, 0, -5), vector(0, 0, 1));
			Sphere sphere;
			Matrix m = scaling(2, 2, 2);
			sphere.setTransform(m);
			sphere.invTransform = sphere.transform.getInverse();
			//IntersectionList intersects = ray.getIntersection(&sphere);
			IntersectionList intersects;
			intersects.addIntersections(ray, &sphere);
			Assert::IsTrue(intersects.count() == 2);
			Assert::IsTrue(isEqualDouble(intersects[0].i, 3));
			Assert::IsTrue(isEqualDouble(intersects[1].i, 7));
		}

		TEST_METHOD(TestSphereIntersectTransformedTranslated)
		{
			Logger::WriteMessage("Testing sphereIntersectTransformedTranslated");
			Ray ray(point(0, 0, -5), vector(0, 0, 1));
			Sphere sphere;
			Matrix m = translation(5, 0, 0);
			sphere.setTransform(m);
			sphere.invTransform = sphere.transform.getInverse();
			//IntersectionList intersects = ray.getIntersection(&sphere);
			IntersectionList intersects;
			intersects.addIntersections(ray, &sphere);
			Assert::IsTrue(intersects.count() == 0);
		}
	};
}