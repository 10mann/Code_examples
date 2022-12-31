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
#include "../the_tray_tracer_challenge/bounding_box.h"
#include "../the_tray_tracer_challenge/test_shape.h"


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
using RayTracer::BoundingBox;
using RayTracer::TestShape;

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


namespace RayTracerTestBonus1
{
	TEST_CLASS(RayTracerTestBonus1)
	{
	public:

		TEST_METHOD(TestCreateEmptyBoundingBox)
		{
			Logger::WriteMessage("Testing createEmptyBoundingBox");

			BoundingBox bbox;

			Assert::IsTrue(bbox.max.x < 0);
			Assert::IsTrue(bbox.max.y < 0);
			Assert::IsTrue(bbox.max.z < 0);

			Assert::IsTrue(bbox.min.x > 0);
			Assert::IsTrue(bbox.min.y > 0);
			Assert::IsTrue(bbox.min.z > 0);
		}

		TEST_METHOD(TestCreteBoundingBox)
		{
			Logger::WriteMessage("Testing createBoundingBox");

			BoundingBox bbox(point(-1, -2, -3), point(3, 2, 1));

			Assert::IsTrue(bbox.min == point(-1, -2, -3));
			Assert::IsTrue(bbox.max == point(3, 2, 1));
		}

		TEST_METHOD(TestAddPoint)
		{
			Logger::WriteMessage("Testing addPoint");

			BoundingBox bbox;

			bbox.addPoint(point(-5, 2, 0));
			bbox.addPoint(point(7, 0, -3));

			Assert::IsTrue(bbox.min == point(-5, 0, -3));
			Assert::IsTrue(bbox.max == point(7, 2, 0));
		}

		TEST_METHOD(TestBboxSphere)
		{
			Logger::WriteMessage("Testing bboxSphere");

			Sphere s;
			BoundingBox bbox = s.getBoundingBox();

			Assert::IsTrue(bbox.min == point(-1, -1, -1));
			Assert::IsTrue(bbox.max == point(1, 1, 1));
		}

		//TEST_METHOD(TestBboxPlane)
		//{
		//	Logger::WriteMessage("Testing bboxPlane");

		//	Plane p;
		//	BoundingBox bbox = p.getBoundingBox();

		//	Assert::IsTrue(bbox.min.x < -1000000);
		//	Assert::IsTrue(bbox.min.z < -1000000);

		//	Assert::IsTrue(bbox.max.x > 1000000);
		//	Assert::IsTrue(bbox.max.z > 1000000);
		//}

		TEST_METHOD(TestBboxCube)
		{
			Logger::WriteMessage("Testing bboxCube");

			Cube c;
			BoundingBox bbox = c.getBoundingBox();

			Assert::IsTrue(bbox.min == point(-1, -1, -1));
			Assert::IsTrue(bbox.max == point(1, 1, 1));
		}

		//TEST_METHOD(TestBboxCylinderOpen)
		//{
		//	Logger::WriteMessage("Testing bboxCylinderOpen");

		//	Cylinder c;
		//	BoundingBox bbox = c.getBoundingBox();

		//	Assert::IsTrue(isEqualDouble(bbox.min.x, -1));
		//	Assert::IsTrue(bbox.min.y < -1000000);
		//	Assert::IsTrue(isEqualDouble(bbox.min.z, -1));

		//	Assert::IsTrue(isEqualDouble(bbox.max.x, 1));
		//	Assert::IsTrue(bbox.max.y > 1000000);
		//	Assert::IsTrue(isEqualDouble(bbox.max.z, 1));
		//}

		TEST_METHOD(TestBboxCylinderClosed)
		{
			Logger::WriteMessage("Testing bboxCylinderClosed");

			Cylinder c;
			c.closed = true;
			c.maxY = 5;
			c.minY = -10;
			BoundingBox bbox = c.getBoundingBox();

			Assert::IsTrue(isEqualDouble(bbox.min.x, -1));
			Assert::IsTrue(isEqualDouble(bbox.min.y, -10));
			Assert::IsTrue(isEqualDouble(bbox.min.z, -1));

			Assert::IsTrue(isEqualDouble(bbox.max.x, 1));
			Assert::IsTrue(isEqualDouble(bbox.max.y, 5));
			Assert::IsTrue(isEqualDouble(bbox.max.z, 1));
		}

		//TEST_METHOD(TestBboxConeOpen)
		//{
		//	Logger::WriteMessage("Testing bboxConeOpen");

		//	Cone c;
		//	BoundingBox bbox = c.getBoundingBox();

		//	Assert::IsTrue(bbox.min.x < -1000000);
		//	Assert::IsTrue(bbox.min.y < -1000000);
		//	Assert::IsTrue(bbox.min.z < -1000000);

		//	Assert::IsTrue(bbox.max.x > 1000000);
		//	Assert::IsTrue(bbox.max.y > 1000000);
		//	Assert::IsTrue(bbox.max.z > 1000000);
		//}

		TEST_METHOD(TestBboxConeClosed)
		{
			Logger::WriteMessage("Testing bboxConeClosed");

			Cone c;
			c.closed = true;
			c.maxY = 5;
			c.minY = -10;
			BoundingBox bbox = c.getBoundingBox();

			Assert::IsTrue(isEqualDouble(bbox.min.x, -10));
			Assert::IsTrue(isEqualDouble(bbox.min.y, -10));
			Assert::IsTrue(isEqualDouble(bbox.min.z, -10));

			Assert::IsTrue(isEqualDouble(bbox.max.x, 10));
			Assert::IsTrue(isEqualDouble(bbox.max.y, 5));
			Assert::IsTrue(isEqualDouble(bbox.max.z, 10));
		}

		TEST_METHOD(TestBboxTestShape)
		{
			Logger::WriteMessage("Testing bboxTestShape");

			TestShape t;
			BoundingBox bbox = t.getBoundingBox();

			Assert::IsTrue(bbox.min == point(-1, -1, -1));
			Assert::IsTrue(bbox.max == point(1, 1, 1));
		}

		TEST_METHOD(TestAddBox)
		{
			Logger::WriteMessage("Testing addBox");

			BoundingBox bbox1(point(-5, -2, 0), point(7, 4, 4));
			BoundingBox bbox2(point(8, -7, -2), point(14, 2, 8));

			bbox1.addBox(bbox2);

			Assert::IsTrue(bbox1.min == point(-5, -7, -2));
			Assert::IsTrue(bbox1.max == point(14, 4, 8));
		}

		TEST_METHOD(TestContainsPoint)
		{
			Logger::WriteMessage("Testing containsPoint");

			BoundingBox bbox(point(5, -2, 0), point(11, 4, 7));

			Assert::IsTrue(bbox.containsPoint(point(5, -2, 0)));
		}

		TEST_METHOD(TestContainsPoint1)
		{
			Logger::WriteMessage("Testing containsPoint1");

			BoundingBox bbox(point(5, -2, 0), point(11, 4, 7));

			Assert::IsTrue(bbox.containsPoint(point(11, 4, 7)));
		}

		TEST_METHOD(TestContainsPoint2)
		{
			Logger::WriteMessage("Testing containsPoint2");

			BoundingBox bbox(point(5, -2, 0), point(11, 4, 7));

			Assert::IsTrue(bbox.containsPoint(point(8, 1, 3)));
		}

		TEST_METHOD(TestContainsPoint3)
		{
			Logger::WriteMessage("Testing containsPoint3");

			BoundingBox bbox(point(5, -2, 0), point(11, 4, 7));

			Assert::IsFalse(bbox.containsPoint(point(3, 0, 3)));
		}

		TEST_METHOD(TestContainsPoint4)
		{
			Logger::WriteMessage("Testing containsPoint4");

			BoundingBox bbox(point(5, -2, 0), point(11, 4, 7));

			Assert::IsFalse(bbox.containsPoint(point(8, -4, 3)));
		}

		TEST_METHOD(TestContainsPoint5)
		{
			Logger::WriteMessage("Testing containsPoint5");

			BoundingBox bbox(point(5, -2, 0), point(11, 4, 7));

			Assert::IsFalse(bbox.containsPoint(point(8, 1, -1)));
		}

		TEST_METHOD(TestContainsPoint6)
		{
			Logger::WriteMessage("Testing containsPoint6");

			BoundingBox bbox(point(5, -2, 0), point(11, 4, 7));

			Assert::IsFalse(bbox.containsPoint(point(13, 1, 3)));
		}

		TEST_METHOD(TestContainsPoint7)
		{
			Logger::WriteMessage("Testing containsPoint7");

			BoundingBox bbox(point(5, -2, 0), point(11, 4, 7));

			Assert::IsFalse(bbox.containsPoint(point(8, 5, 3)));
		}

		TEST_METHOD(TestContainsPoint8)
		{
			Logger::WriteMessage("Testing containsPoint8");

			BoundingBox bbox(point(5, -2, 0), point(11, 4, 7));

			Assert::IsFalse(bbox.containsPoint(point(8, 1, 8)));
		}

		TEST_METHOD(TestContainsBox)
		{
			Logger::WriteMessage("Testing containsBox");

			BoundingBox bbox(point(5, -2, 0), point(11, 4, 7));
			BoundingBox bbox1(point(5, -2, 0), point(11, 4, 7));

			Assert::IsTrue(bbox.containsBox(bbox1));
		}

		TEST_METHOD(TestContainsBox1)
		{
			Logger::WriteMessage("Testing containsBox1");

			BoundingBox bbox(point(5, -2, 0), point(11, 4, 7));
			BoundingBox bbox1(point(6, -1, 1), point(10, 3, 6));

			Assert::IsTrue(bbox.containsBox(bbox1));
		}

		TEST_METHOD(TestContainsBox2)
		{
			Logger::WriteMessage("Testing containsBox2");

			BoundingBox bbox(point(5, -2, 0), point(11, 4, 7));
			BoundingBox bbox1(point(4, -3, -1), point(10, 3, 6));

			Assert::IsFalse(bbox.containsBox(bbox1));
		}

		TEST_METHOD(TestContainsBox3)
		{
			Logger::WriteMessage("Testing containsBox3");

			BoundingBox bbox(point(5, -2, 0), point(11, 4, 7));
			BoundingBox bbox1(point(6, -1, 1), point(12, 5, 8));

			Assert::IsFalse(bbox.containsBox(bbox1));
		}

		TEST_METHOD(TestSetTranform)
		{
			Logger::WriteMessage("Testing setTransform");

			BoundingBox bbox(point(-1, -1, -1), point(1, 1, 1));
			Matrix m = rotationX(DoubleHelpers::MATH_PI / 4) * rotationY(DoubleHelpers::MATH_PI / 4);
			bbox.setTransform(m);

			Assert::IsTrue(bbox.min == point(-1.41421, -1.70711, -1.70711));
			Assert::IsTrue(bbox.max == point(1.41421, 1.70711, 1.70711));
		}

		TEST_METHOD(TestSpherBoundingBox)
		{
			Logger::WriteMessage("Testing sphereBoundingBox");

			Sphere s;
			s.setTransform(translation(1, -3, 5) * scaling(0.5, 2, 4));

			BoundingBox bbox = s.getBoundingBox();

			Assert::IsTrue(bbox.min == point(0.5, -5, 1));
			Assert::IsTrue(bbox.max == point(1.5, -1, 9));
		}

		TEST_METHOD(TestGroupBoundingBox)
		{
			Logger::WriteMessage("Testing groupBoundingBox");
			Sphere s;
			s.setTransform(translation(2, 5, -3) * scaling(2, 2, 2));

			Cylinder c;
			c.closed = true;
			c.minY = -2;
			c.maxY = 2;
			c.setTransform(translation(-4, -1, 4) * scaling(0.5, 1, 0.5));

			Group g;
			g.addChild(&s);
			g.addChild(&c);

			BoundingBox bbox = g.getBoundingBox();

			Assert::IsTrue(bbox.min == point(-4.5, -3, -5));
			Assert::IsTrue(bbox.max == point(4, 7, 4.5));
		}

		TEST_METHOD(TestIntersectBbox)
		{
			Logger::WriteMessage("Testing intersectBbox");

			BoundingBox b(point(-1, -1, -1), point(1, 1, 1));

			Tuple dir = vector(-1, 0, 0).getNormalized();
			Ray r(point(5, 0.5, 0), dir);

			Assert::IsTrue(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBbox1)
		{
			Logger::WriteMessage("Testing intersectBbox1");

			BoundingBox b(point(-1, -1, -1), point(1, 1, 1));

			Tuple dir = vector(1, 0, 0).getNormalized();
			Ray r(point(-5, 0.5, 0), dir);

			Assert::IsTrue(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBbox2)
		{
			Logger::WriteMessage("Testing intersectBbox2");

			BoundingBox b(point(-1, -1, -1), point(1, 1, 1));

			Tuple dir = vector(0, -1, 0).getNormalized();
			Ray r(point(0.5, 5, 0), dir);

			Assert::IsTrue(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBbox3)
		{
			Logger::WriteMessage("Testing intersectBbox3");

			BoundingBox b(point(-1, -1, -1), point(1, 1, 1));

			Tuple dir = vector(0, 1, 0).getNormalized();
			Ray r(point(0.5, -5, 0), dir);

			Assert::IsTrue(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBbox4)
		{
			Logger::WriteMessage("Testing intersectBbox4");

			BoundingBox b(point(-1, -1, -1), point(1, 1, 1));

			Tuple dir = vector(0, 0, -1).getNormalized();
			Ray r(point(0.5, 0, 5), dir);

			Assert::IsTrue(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBbox5)
		{
			Logger::WriteMessage("Testing intersectBbox5");

			BoundingBox b(point(-1, -1, -1), point(1, 1, 1));

			Tuple dir = vector(0, 0, 1).getNormalized();
			Ray r(point(0.5, 0, -5), dir);

			Assert::IsTrue(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBbox6)
		{
			Logger::WriteMessage("Testing intersectBbox6");

			BoundingBox b(point(-1, -1, -1), point(1, 1, 1));

			Tuple dir = vector(0, 0, 1).getNormalized();
			Ray r(point(0, 0.5, 0), dir);

			Assert::IsTrue(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBbox7)
		{
			Logger::WriteMessage("Testing intersectBbox7");

			BoundingBox b(point(-1, -1, -1), point(1, 1, 1));

			Tuple dir = vector(2, 4, 6).getNormalized();
			Ray r(point(-2, 0, 0), dir);

			Assert::IsFalse(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBbox8)
		{
			Logger::WriteMessage("Testing intersectBbox8");

			BoundingBox b(point(-1, -1, -1), point(1, 1, 1));

			Tuple dir = vector(6, 2, 4).getNormalized();
			Ray r(point(0, -2, 0), dir);

			Assert::IsFalse(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBbox9)
		{
			Logger::WriteMessage("Testing intersectBbox9");

			BoundingBox b(point(-1, -1, -1), point(1, 1, 1));

			Tuple dir = vector(4, 6, 2).getNormalized();
			Ray r(point(0, 0, -2), dir);

			Assert::IsFalse(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBbox10)
		{
			Logger::WriteMessage("Testing intersectBbox10");

			BoundingBox b(point(-1, -1, -1), point(1, 1, 1));

			Tuple dir = vector(0, 0, -1).getNormalized();
			Ray r(point(2, 0, 2), dir);

			Assert::IsFalse(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBbox11)
		{
			Logger::WriteMessage("Testing intersectBbox11");

			BoundingBox b(point(-1, -1, -1), point(1, 1, 1));

			Tuple dir = vector(0, -1, 0).getNormalized();
			Ray r(point(0, 2, 2), dir);

			Assert::IsFalse(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBbox12)
		{
			Logger::WriteMessage("Testing intersectBbox12");

			BoundingBox b(point(-1, -1, -1), point(1, 1, 1));

			Tuple dir = vector(-1, 0, 0).getNormalized();
			Ray r(point(2, 2, 0), dir);

			Assert::IsFalse(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBboxNonUnit)
		{
			Logger::WriteMessage("Testing intersectBboxNonUnit");

			BoundingBox b(point(5, -2, 0), point(11, 4, 7));

			Tuple dir = vector(-1, 0, 0).getNormalized();
			Ray r(point(15, 1, 2), dir);

			Assert::IsTrue(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBboxNonUnit1)
		{
			Logger::WriteMessage("Testing intersectBboxNonUnit1");

			BoundingBox b(point(5, -2, 0), point(11, 4, 7));

			Tuple dir = vector(1, 0, 0).getNormalized();
			Ray r(point(-5, -1, 4), dir);

			Assert::IsTrue(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBboxNonUnit2)
		{
			Logger::WriteMessage("Testing intersectBboxNonUnit2");

			BoundingBox b(point(5, -2, 0), point(11, 4, 7));

			Tuple dir = vector(0, -1, 0).getNormalized();
			Ray r(point(7, 6, 5), dir);

			Assert::IsTrue(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBboxNonUnit3)
		{
			Logger::WriteMessage("Testing intersectBboxNonUnit3");

			BoundingBox b(point(5, -2, 0), point(11, 4, 7));

			Tuple dir = vector(0, 1, 0).getNormalized();
			Ray r(point(9, -5, 6), dir);

			Assert::IsTrue(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBboxNonUnit4)
		{
			Logger::WriteMessage("Testing intersectBboxNonUnit4");

			BoundingBox b(point(5, -2, 0), point(11, 4, 7));

			Tuple dir = vector(0, 0, -1).getNormalized();
			Ray r(point(8, 2, 12), dir);

			Assert::IsTrue(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBboxNonUnit5)
		{
			Logger::WriteMessage("Testing intersectBboxNonUnit5");

			BoundingBox b(point(5, -2, 0), point(11, 4, 7));

			Tuple dir = vector(0, 0, 1).getNormalized();
			Ray r(point(6, 0, -5), dir);

			Assert::IsTrue(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBboxNonUnit6)
		{
			Logger::WriteMessage("Testing intersectBboxNonUnit6");

			BoundingBox b(point(5, -2, 0), point(11, 4, 7));

			Tuple dir = vector(0, 0, 1).getNormalized();
			Ray r(point(8, 1, 3.5), dir);

			Assert::IsTrue(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBboxNonUnit7)
		{
			Logger::WriteMessage("Testing intersectBboxNonUnit7");

			BoundingBox b(point(5, -2, 0), point(11, 4, 7));

			Tuple dir = vector(2, 4, 6).getNormalized();
			Ray r(point(9, -1, -8), dir);

			Assert::IsFalse(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBboxNonUnit8)
		{
			Logger::WriteMessage("Testing intersectBboxNonUnit8");

			BoundingBox b(point(5, -2, 0), point(11, 4, 7));

			Tuple dir = vector(6, 2, 4).getNormalized();
			Ray r(point(8, 3, -4), dir);

			Assert::IsFalse(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBboxNonUnit9)
		{
			Logger::WriteMessage("Testing intersectBboxNonUnit9");

			BoundingBox b(point(5, -2, 0), point(11, 4, 7));

			Tuple dir = vector(4, 6, 2).getNormalized();
			Ray r(point(9, -1, -2), dir);

			Assert::IsFalse(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBboxNonUnit10)
		{
			Logger::WriteMessage("Testing intersectBboxNonUnit10");

			BoundingBox b(point(5, -2, 0), point(11, 4, 7));

			Tuple dir = vector(0, 0, -1).getNormalized();
			Ray r(point(4, 0, 9), dir);

			Assert::IsFalse(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBboxNonUnit11)
		{
			Logger::WriteMessage("Testing intersectBboxNonUnit11");

			BoundingBox b(point(5, -2, 0), point(11, 4, 7));

			Tuple dir = vector(0, -1, 0).getNormalized();
			Ray r(point(8, 6, -1), dir);

			Assert::IsFalse(b.intersects(r));
		}

		TEST_METHOD(TestIntersectBboxNonUnit12)
		{
			Logger::WriteMessage("Testing intersectBboxNonUnit12");

			BoundingBox b(point(5, -2, 0), point(11, 4, 7));

			Tuple dir = vector(-1, 0, 0).getNormalized();
			Ray r(point(12, 5, 4), dir);

			Assert::IsFalse(b.intersects(r));
		}

		TEST_METHOD(TestGroupBbox)
		{
			Logger::WriteMessage("Testing groupBbox");

			TestShape s;
			Group g;
			g.addChild(&s);

			Ray r(point(0, 0, -5), vector(0, 1, 0));

			IntersectionList list;
			list.addIntersections(r, &g);

			Assert::IsFalse(s.intersected);
		}

		TEST_METHOD(TestGroupBbox1)
		{
			Logger::WriteMessage("Testing groupBbox1");

			TestShape s;
			Group g;
			g.addChild(&s);

			Ray r(point(0, 0, -5), vector(0, 0, 1));

			IntersectionList list;
			list.addIntersections(r, &g);

			Assert::IsTrue(s.intersected);
		}

		TEST_METHOD(TestSplitBboxCube)
		{
			Logger::WriteMessage("Testing splitBboxCube");

			BoundingBox b(point(-1, -4, -5), point(9, 6, 5));
			std::vector<BoundingBox> boxes = b.splitBounds();

			Assert::IsTrue(boxes[0].min == point(-1, -4, -5));
			Assert::IsTrue(boxes[0].max == point(4, 6, 5));

			Assert::IsTrue(boxes[1].min == point(4, -4, -5));
			Assert::IsTrue(boxes[1].max == point(9, 6, 5));
		}

		TEST_METHOD(TestSplitBboxX)
		{
			Logger::WriteMessage("Testing splitBboxX");

			BoundingBox b(point(-1, -2, -3), point(9, 5.5, 3));
			std::vector<BoundingBox> boxes = b.splitBounds();

			Assert::IsTrue(boxes[0].min == point(-1, -2, -3));
			Assert::IsTrue(boxes[0].max == point(4, 5.5, 3));

			Assert::IsTrue(boxes[1].min == point(4, -2, -3));
			Assert::IsTrue(boxes[1].max == point(9, 5.5, 3));
		}

		TEST_METHOD(TestSplitBboxY)
		{
			Logger::WriteMessage("Testing splitBboxY");

			BoundingBox b(point(-1, -2, -3), point(5, 8, 3));
			std::vector<BoundingBox> boxes = b.splitBounds();

			Assert::IsTrue(boxes[0].min == point(-1, -2, -3));
			Assert::IsTrue(boxes[0].max == point(5, 3, 3));

			Assert::IsTrue(boxes[1].min == point(-1, 3, -3));
			Assert::IsTrue(boxes[1].max == point(5, 8, 3));
		}

		TEST_METHOD(TestSplitBboxZ)
		{
			Logger::WriteMessage("Testing splitBboxZ");

			BoundingBox b(point(-1, -2, -3), point(5, 3, 7));
			std::vector<BoundingBox> boxes = b.splitBounds();

			Assert::IsTrue(boxes[0].min == point(-1, -2, -3));
			Assert::IsTrue(boxes[0].max == point(5, 3, 2));

			Assert::IsTrue(boxes[1].min == point(-1, -2, 2));
			Assert::IsTrue(boxes[1].max == point(5, 3, 7));
		}

		TEST_METHOD(TestPartitionChildren)
		{
			Logger::WriteMessage("Testing partitionChildren");

			Sphere s1;
			s1.setTransform(translation(-2, 0, 0));

			Sphere s2;
			s2.setTransform(translation(2, 0, 0));

			Sphere s3;

			Group g;
			g.addChild(&s1);
			g.addChild(&s2);
			g.addChild(&s3);

			std::vector<std::vector<Shape*>> list = g.partitionChildren();

			Assert::IsTrue(g.objects[0] == &s3);
			Assert::IsTrue(list[0][0] == &s1);
			Assert::IsTrue(list[1][0] == &s2);
		}

		TEST_METHOD(TestCreateSubGroup)
		{
			Logger::WriteMessage("Testing createSubGroup");

			Sphere s1;
			Sphere s2;

			std::vector<Shape*> shapes;
			shapes.push_back(&s1);
			shapes.push_back(&s2);

			Group g;
			g.makeSubGroup(shapes);

			Assert::IsTrue(g.objects.size() == 1);
			Group* gPtr = (Group*)(g.objects[0]);
			Assert::IsTrue(gPtr->objects[0] == &s1);
			Assert::IsTrue(gPtr->objects[1] == &s2);
		}

		TEST_METHOD(TestDivideSphere)
		{
			Logger::WriteMessage("Testing divideSphere");

			Sphere s;
			s.divide(1);
			Sphere s1;

			Assert::IsTrue(s == s1);
		}

		TEST_METHOD(TestDivideGroup)
		{
			Logger::WriteMessage("Testing divideGroup");

			Sphere s1;
			s1.setTransform(translation(-2, -2, 0));

			Sphere s2;
			s2.setTransform(translation(-2, 2, 0));

			Sphere s3;
			s3.setTransform(scaling(4, 4, 4));

			Group g;
			g.addChild(&s1);
			g.addChild(&s2);
			g.addChild(&s3);
			g.divide(1);

			Group* sg = (Group*)(g.objects[1]);
			Group* ssg1 = (Group*)(sg->objects[0]);
			Group* ssg2 = (Group*)(sg->objects[1]);

			Assert::IsTrue(g.objects[0] == &s3);
			Assert::IsTrue(sg->objects.size() == 2);
			Assert::IsTrue(ssg1->objects[0] == &s1);
			Assert::IsTrue(ssg2->objects[0] == &s2);
		}
	};
}