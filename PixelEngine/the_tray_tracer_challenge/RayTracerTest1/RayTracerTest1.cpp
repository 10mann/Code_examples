#include "pch.h"
#include "CppUnitTest.h"
#include "../the_tray_tracer_challenge/tuple.h"
#include "../the_tray_tracer_challenge/DoubleHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using RayTracer::Tuple;

namespace RayTracerTest1
{
	TEST_CLASS(RayTracerTest1)
	{
	public:
		
		TEST_METHOD(TestisPoint)
		{
			Logger::WriteMessage("Testing isPoint");
			Tuple point(4.3, -4.2, 3.1, 1.0);
			Assert::IsTrue(DoubleHelpers::isEqualDouble(point.x, 4.3));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(point.y, -4.2));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(point.z, 3.1));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(point.w, 1.0));
			Assert::IsTrue(point.isPoint());
		}

		TEST_METHOD(TestisVector)
		{
			Logger::WriteMessage("Testing isVector");
			Tuple vector(4.3, -4.2, 3.1, 0.0);
			Assert::IsTrue(DoubleHelpers::isEqualDouble(vector.x, 4.3));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(vector.y, -4.2));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(vector.z, 3.1));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(vector.w, 0.0));
			Assert::IsTrue(vector.isVector());
		}

		TEST_METHOD(TestCreatePoint)
		{
			Logger::WriteMessage("Testing createPoint");
			Tuple point = RayTracer::point(4.0, -4.0, 3.0);
			Assert::IsTrue(DoubleHelpers::isEqualDouble(point.x, 4.0));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(point.y, -4.0));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(point.z, 3.0));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(point.w, 1.0));
			Assert::IsTrue(point.isPoint());
		}

		TEST_METHOD(TestCreateVector)
		{
			Logger::WriteMessage("Testing createVector");
			Tuple vector = RayTracer::vector(4.0, -4.0, 3.0);
			Assert::IsTrue(DoubleHelpers::isEqualDouble(vector.x, 4.0));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(vector.y, -4.0));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(vector.z, 3.0));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(vector.w, 0.0));
			Assert::IsTrue(vector.isVector());
		}

		TEST_METHOD(TestAddTuple)
		{
			Logger::WriteMessage("Testing addTuple");
			Tuple point = Tuple(3.0, -2.0, 5.0, 1.0);
			Tuple vector = Tuple(-2.0, 3.0, 1.0, 0.0);
			Tuple newPoint = point + vector;
			Assert::IsTrue(newPoint.isPoint());
			Assert::IsTrue(true);
			Assert::IsTrue(newPoint.isEqual(Tuple(1.0, 1.0, 6.0, 1.0)));
		}

		TEST_METHOD(TestSubtractPoints)
		{
			Logger::WriteMessage("Testing subtractPoints");
			Tuple point1 = RayTracer::point(3.0, 2.0, 1.0);
			Tuple point2 = RayTracer::point(5.0, 6.0, 7.0);
			Tuple vectorSum = point1 - point2;
			Assert::IsTrue(vectorSum == RayTracer::vector(-2.0, -4.0, -6.0));
		}

		TEST_METHOD(TestSubtractVectorFromPoint)
		{
			Logger::WriteMessage("Testing subtractVectorFromPoint");
			Tuple point = RayTracer::point(3.0, 2.0, 1.0);
			Tuple vector = RayTracer::vector(5.0, 6.0, 7.0);
			Tuple newPoint = point - vector;
			Assert::IsTrue(newPoint == RayTracer::point(-2.0, -4.0, -6.0));
		}

		TEST_METHOD(TestSubtractVectors)
		{
			Logger::WriteMessage("Testing subtractVectors");
			Tuple vector1 = RayTracer::vector(3.0, 2.0, 1.0);
			Tuple vector2 = RayTracer::vector(5.0, 6.0, 7.0);
			Tuple newVector = vector1 - vector2;
			Assert::IsTrue(newVector == RayTracer::vector(-2.0, -4.0, -6.0));
		}

		TEST_METHOD(TestSubtractVectorFromZeroVector)
		{
			Logger::WriteMessage("Testing subtractVectorFromZeroVector");
			Tuple vector1 = RayTracer::vector(0.0, 0.0, 0.0);
			Tuple vector2 = RayTracer::vector(5.0, 6.0, 7.0);
			Tuple newVector = vector1 - vector2;
			Assert::IsTrue(newVector == RayTracer::vector(-5.0, -6.0, -7.0));
		}

		TEST_METHOD(TestInvertingVector)
		{
			Logger::WriteMessage("Testing invertingVector");
			Tuple t1 = Tuple(1.0, 2.0, 3.0, 4.0);
			Tuple t2 = -t1;
			Assert::IsTrue(t2 == Tuple(-1.0, -2.0, -3.0, -4.0));
		}

		TEST_METHOD(TestMultiplyScalar)
		{
			Logger::WriteMessage("Testing multiplyScalar");
			Tuple t1 = Tuple(1.0, -2.0, 3.0, -4.0);
			Tuple t2 = t1 * 4.0;
			Assert::IsTrue(t2 == Tuple(4.0, -8.0, 12.0, -16.0));
		}

		TEST_METHOD(TestMultiplyScalarFraction)
		{
			Logger::WriteMessage("Testing multiplyScalarFraction");
			Tuple t1 = Tuple(1.0, -2.0, 3.0, -4.0);
			Tuple t2 = t1 * 0.5;
			Assert::IsTrue(t2 == Tuple(0.5, -1.0, 1.5, -2.0));
		}

		TEST_METHOD(TestDivideScalar)
		{
			Logger::WriteMessage("Testing divideScalar");
			Tuple t1 = Tuple(1.0, -2.0, 3.0, -4.0);
			Tuple t2 = t1 / 2.0;
			Assert::IsTrue(t2 == Tuple(0.5, -1.0, 1.5, -2.0));
		}

		TEST_METHOD(TestMagnitude)
		{
			Logger::WriteMessage("Testing magnitude");
			Tuple vector = RayTracer::vector(1.0, 0.0, 0.0);
			double magnitude = vector.getMagnitude();
			Assert::IsTrue(DoubleHelpers::isEqualDouble(1.0, magnitude));

			vector = RayTracer::vector(0.0, 1.0, 0.0);
			magnitude = vector.getMagnitude();
			Assert::IsTrue(DoubleHelpers::isEqualDouble(1.0, magnitude));

			vector = RayTracer::vector(0.0, 0.0, 1.0);
			magnitude = vector.getMagnitude();
			Assert::IsTrue(DoubleHelpers::isEqualDouble(1.0, magnitude));

			vector = RayTracer::vector(1.0, 2.0, 3.0);
			magnitude = vector.getMagnitude();
			Assert::IsTrue(DoubleHelpers::isEqualDouble(std::sqrt(14.0), magnitude));

			vector = RayTracer::vector(-1.0, -2.0, -3.0);
			magnitude = vector.getMagnitude();
			Assert::IsTrue(DoubleHelpers::isEqualDouble(std::sqrt(14.0), magnitude));
		}

		TEST_METHOD(TestNormalize)
		{
			Logger::WriteMessage("Testing normalize");
			Tuple vector = RayTracer::vector(4.0, 0.0, 0.0);
			Tuple vectorNormalized = vector.getNormalized();
			Assert::IsTrue(vectorNormalized == Tuple(1.0, 0.0, 0.0, 0.0));

			vector = RayTracer::vector(1.0, 2.0, 3.0);
			vectorNormalized = vector.getNormalized();
			Assert::IsTrue(vectorNormalized == RayTracer::vector(0.26726, 0.53452, 0.80178));

			double magnitude = vectorNormalized.getMagnitude();
			Assert::IsTrue(DoubleHelpers::isEqualDouble(1.0, magnitude));
		}

		TEST_METHOD(TestDotProduct)
		{
			Logger::WriteMessage("Testing dotProduct");
			Tuple vector1 = RayTracer::vector(1.0, 2.0, 3.0);
			Tuple vector2 = RayTracer::vector(2.0, 3.0, 4.0);
			double dotProd = vector1.dotProduct(vector2);
			Assert::IsTrue(DoubleHelpers::isEqualDouble(dotProd, 20.0));
		}

		TEST_METHOD(TestCrosstProduct)
		{
			Logger::WriteMessage("Testing crossProduct");
			Tuple vector1 = RayTracer::vector(1.0, 2.0, 3.0);
			Tuple vector2 = RayTracer::vector(2.0, 3.0, 4.0);
			Tuple crossProd = vector1.crossProduct(vector2);
			Assert::IsTrue(crossProd == Tuple(-1.0, 2.0, -1.0, 0.0));
		}
	};
}
