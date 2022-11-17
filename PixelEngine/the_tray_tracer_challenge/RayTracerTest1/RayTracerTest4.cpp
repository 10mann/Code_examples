#include "pch.h"
#include "CppUnitTest.h"
#include "../the_tray_tracer_challenge/matrix.h"
#include "../the_tray_tracer_challenge/tuple.h"
#include "../the_tray_tracer_challenge/DoubleHelpers.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using RayTracer::Matrix;
using RayTracer::Tuple;
using DoubleHelpers::isEqualDouble;
using RayTracer::translation;
using RayTracer::scaling;
using RayTracer::rotationX;
using RayTracer::rotationY;
using RayTracer::rotationZ;
using RayTracer::shearing;
using DoubleHelpers::MATH_PI;

namespace RayTracerTest4
{
	TEST_CLASS(RayTracerTest4)
	{
	public:

		TEST_METHOD(TestTranslation)
		{
			Logger::WriteMessage("Testing translation");
			Tuple p = RayTracer::point(-3, 4, 5);
			Matrix transform = translation(5, -3, 2);

			Tuple newP = transform* p;
			Assert::IsTrue(newP == RayTracer::point(2, 1, 7));
		}

		TEST_METHOD(TestInverseTranslation)
		{
			Logger::WriteMessage("Testing inverseTranslation");
			Tuple p = RayTracer::point(-3, 4, 5);
			Matrix transform = translation(5, -3, 2);
			Matrix invTransform = transform.getInverse();

			Tuple newP = invTransform * p;
			Assert::IsTrue(newP == RayTracer::point(-8, 7, 3));
		}

		TEST_METHOD(TestTranslateVector)
		{
			Logger::WriteMessage("Testing translateVector");
			Tuple v = RayTracer::vector(-3, 4, 5);
			Matrix transform = translation(5, -3, 2);

			Tuple newV = transform * v;
			Assert::IsTrue(newV == v);
		}

		TEST_METHOD(TestScaling)
		{
			Logger::WriteMessage("Testing scaling");
			Tuple p = RayTracer::point(1, 2, 3);
			Matrix transform = scaling(12, 6, 4);

			Tuple newP = transform * p;
			Assert::IsTrue(newP == RayTracer::point(12, 12, 12));
		}

		TEST_METHOD(TestScaleVector)
		{
			Logger::WriteMessage("Testing scaleVector");
			Tuple v = RayTracer::vector(-3, 12, 8);
			Matrix transform = scaling(5, -3, 2);
			
			Tuple newV = transform * v;
			Assert::IsTrue(newV == RayTracer::vector(-15, -36, 16));
		}

		TEST_METHOD(TestInverseScaling)
		{
			Logger::WriteMessage("Testing inverseScaling");
			Tuple p = RayTracer::point(12, 12, 12);
			Matrix transform = scaling(12, 6, 4);
			Matrix invTransform = transform.getInverse();

			Tuple newP = invTransform * p;
			Assert::IsTrue(newP == RayTracer::point(1, 2, 3));
		}

		TEST_METHOD(TestReflecting)
		{
			Logger::WriteMessage("Testing reflecting");
			Tuple p = RayTracer::point(8, 10, 3);
			Matrix transform = scaling(-1, 1, 1);

			Tuple newP = transform * p;
			Assert::IsTrue(newP == RayTracer::point(-8, 10, 3));
		}

		TEST_METHOD(TestRotationX)
		{
			Logger::WriteMessage("Testing rotationX");
			Tuple p = RayTracer::point(0, 1, 0);
			Matrix halfQuart = rotationX(MATH_PI / 4.0); 
			Matrix fullQuart = rotationX(MATH_PI / 2.0); 

			Tuple halfQuartP = halfQuart * p;
			Tuple fullQuartP = fullQuart * p;
			Assert::IsTrue(halfQuartP == RayTracer::point(0, sqrt(2) / 2.0, sqrt(2) / 2.0));
			Assert::IsTrue(fullQuartP == RayTracer::point(0, 0, 1));
		}

		TEST_METHOD(TestRotationY)
		{
			Logger::WriteMessage("Testing rotationY");
			Tuple p = RayTracer::point(0, 0, 1);
			Matrix halfQuart = rotationY(MATH_PI / 4.0);
			Matrix fullQuart = rotationY(MATH_PI / 2.0);

			Tuple halfQuartP = halfQuart * p;
			Tuple fullQuartP = fullQuart * p;
			Assert::IsTrue(halfQuartP == RayTracer::point(sqrt(2) / 2.0, 0, sqrt(2) / 2.0));
			Assert::IsTrue(fullQuartP == RayTracer::point(1, 0, 0));
		}

		TEST_METHOD(TestRotationZ)
		{
			Logger::WriteMessage("Testing rotationZ");
			Tuple p = RayTracer::point(1, 0, 0);
			Matrix halfQuart = rotationZ(MATH_PI / 4.0);
			Matrix fullQuart = rotationZ(MATH_PI / 2.0);

			Tuple halfQuartP = halfQuart * p;
			Tuple fullQuartP = fullQuart * p;
			Assert::IsTrue(halfQuartP == RayTracer::point(sqrt(2) / 2.0, sqrt(2) / 2.0, 0));
			Assert::IsTrue(fullQuartP == RayTracer::point(0, 1, 0));
		}

		TEST_METHOD(TestShearing1)
		{
			Logger::WriteMessage("Testing shearing1");
			Tuple p = RayTracer::point(2, 3, 4);
			Matrix shearingTranform = shearing(1, 0, 0, 0, 0, 0);

			Tuple shearingP = shearingTranform * p;
			Assert::IsTrue(shearingP == RayTracer::point(5, 3, 4));
		}

		TEST_METHOD(TestShearing2)
		{
			Logger::WriteMessage("Testing shearing2");
			Tuple p = RayTracer::point(2, 3, 4);
			Matrix shearingTranform = shearing(0, 1, 0, 0, 0, 0);

			Tuple shearingP = shearingTranform * p;
			Assert::IsTrue(shearingP == RayTracer::point(6, 3, 4));
		}

		TEST_METHOD(TestShearing3)
		{
			Logger::WriteMessage("Testing shearing3");
			Tuple p = RayTracer::point(2, 3, 4);
			Matrix shearingTranform = shearing(0, 0, 1, 0, 0, 0);

			Tuple shearingP = shearingTranform * p;
			Assert::IsTrue(shearingP == RayTracer::point(2, 5, 4));
		}

		TEST_METHOD(TestShearing4)
		{
			Logger::WriteMessage("Testing shearing4");
			Tuple p = RayTracer::point(2, 3, 4);
			Matrix shearingTranform = shearing(0, 0, 0, 1, 0, 0);

			Tuple shearingP = shearingTranform * p;
			Assert::IsTrue(shearingP == RayTracer::point(2, 7, 4));
		}

		TEST_METHOD(TestShearing5)
		{
			Logger::WriteMessage("Testing shearing5");
			Tuple p = RayTracer::point(2, 3, 4);
			Matrix shearingTranform = shearing(0, 0, 0, 0, 1, 0);

			Tuple shearingP = shearingTranform * p;
			Assert::IsTrue(shearingP == RayTracer::point(2, 3, 6));
		}

		TEST_METHOD(TestShearing6)
		{
			Logger::WriteMessage("Testing shearing6");
			Tuple p = RayTracer::point(2, 3, 4);
			Matrix shearingTranform = shearing(0, 0, 0, 0, 0, 1);

			Tuple shearingP = shearingTranform * p;
			Assert::IsTrue(shearingP == RayTracer::point(2, 3, 7));
		}

		TEST_METHOD(TestChainMatrices)
		{
			Logger::WriteMessage("Testing chainMatrices");
			Tuple p = RayTracer::point(1, 0, 1);
			Matrix rotM = rotationX(MATH_PI / 2.0);
			Matrix scalM = scaling(5, 5, 5);
			Matrix tranM = translation(10, 5, 7);

			Tuple p2 = rotM * p;
			Assert::IsTrue(p2 == RayTracer::point(1, -1, 0));

			Tuple p3 = scalM * p2;
			Assert::IsTrue(p3 == RayTracer::point(5, -5, 0));

			Tuple p4 = tranM * p3;
			Assert::IsTrue(p4 == RayTracer::point(15, 0, 7));
		}

		TEST_METHOD(TestChainMatrices2)
		{
			Logger::WriteMessage("Testing chainMatrices2");
			Tuple p = RayTracer::point(1, 0, 1);
			Matrix rotM = rotationX(MATH_PI / 2.0);
			Matrix scalM = scaling(5, 5, 5);
			Matrix tranM = translation(10, 5, 7);
			Matrix transformMatrix = (tranM * scalM) * rotM;
			Tuple p2 = transformMatrix * p;

			Assert::IsTrue(p2 == RayTracer::point(15, 0, 7));
		}
	};
}