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
#include "../the_tray_tracer_challenge/gradient_pattern.h"
#include "../the_tray_tracer_challenge/ring_pattern.h"
#include "../the_tray_tracer_challenge/checker_pattern.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using RayTracer::Tuple;
using RayTracer::Color;
using RayTracer::StripePattern;
using RayTracer::Material;
using RayTracer::PointLight;
using RayTracer::Sphere;
using RayTracer::Matrix;
using RayTracer::GradientPattern;
using RayTracer::RingPattern;
using RayTracer::CheckerPattern;
using DoubleHelpers::MATH_PI;
using RayTracer::point;
using RayTracer::vector;
using DoubleHelpers::isEqualDouble;
using RayTracer::getLighting;
using RayTracer::scaling;
using RayTracer::translation;


namespace RayTracerTest10
{
	TEST_CLASS(RayTracerTest10)
	{
	public:

		TEST_METHOD(TestCreateStripePattern)
		{
			Logger::WriteMessage("Testing createStripePattern");

			StripePattern pattern(Color::White, Color::Black);

			Assert::IsTrue(pattern.a == Color::White);
			Assert::IsTrue(pattern.b == Color::Black);
		}

		TEST_METHOD(TestStripeAtYConstant)
		{
			Logger::WriteMessage("Testing stripeAtYConstant");

			StripePattern pattern(Color::White, Color::Black);

			Assert::IsTrue(pattern.colorAt(point(0, 0, 0)) == Color::White);
			Assert::IsTrue(pattern.colorAt(point(0, 1, 0)) == Color::White);
			Assert::IsTrue(pattern.colorAt(point(0, 2, 0)) == Color::White);
		}

		TEST_METHOD(TestStripeAtZConstant)
		{
			Logger::WriteMessage("Testing stripeAtZConstant");

			StripePattern pattern(Color::White, Color::Black);

			Assert::IsTrue(pattern.colorAt(point(0, 0, 0)) == Color::White);
			Assert::IsTrue(pattern.colorAt(point(0, 0, 1)) == Color::White);
			Assert::IsTrue(pattern.colorAt(point(0, 0, 2)) == Color::White);
		}

		TEST_METHOD(TestStripeAtX)
		{
			Logger::WriteMessage("Testing stripeAtX");

			StripePattern pattern(Color::White, Color::Black);

			Assert::IsTrue(pattern.colorAt(point(0, 0, 0)) == Color::White);
			Assert::IsTrue(pattern.colorAt(point(0.9, 0, 0)) == Color::White);
			Assert::IsTrue(pattern.colorAt(point(1, 0, 0)) == Color::Black);
			Assert::IsTrue(pattern.colorAt(point(-0.1, 0, 0)) == Color::Black);
			Assert::IsTrue(pattern.colorAt(point(-1, 0, 0)) == Color::Black);
			Assert::IsTrue(pattern.colorAt(point(-1.1, 0, 0)) == Color::White);
		}

		TEST_METHOD(TestMaterialPattern)
		{
			Logger::WriteMessage("Testing MaterialPattern");

			Material m;
			m.ambient = 1;
			m.specular = 0;
			m.diffuse = 0;
			Tuple eyeDir = vector(0, 0, -1);
			Tuple norm = vector(0, 0, -1);
			PointLight light(Color(1, 1, 1), point(0, 0, -10));
			StripePattern pattern(Color::White, Color::Black);
			m.pattern = &pattern;
			Sphere s;
			s.material = m;
			
			Color c1 = getLighting(&s, light, point(0.9, 0, 0), eyeDir, norm, false);
			Color c2 = getLighting(&s, light, point(1.1, 0, 0), eyeDir, norm, false);

			Assert::IsTrue(c1 == Color::White);
			Assert::IsTrue(c2 == Color::Black);
		}

		TEST_METHOD(TestPatternSphereScaled)
		{
			Logger::WriteMessage("Testing PatternSphereScaled");

			Sphere s;
			s.setTransform(scaling(2, 2, 2));
			StripePattern pattern(Color::White, Color::Black);
			s.material.pattern = &pattern;
			Color c = s.colorAt(point(1.5, 0, 0));

			Assert::IsTrue(c == Color::White);
		}

		TEST_METHOD(TestPatternScaled)
		{
			Logger::WriteMessage("Testing PatternScaled");

			Sphere s;
			s.setTransform(scaling(2, 2, 2));
			StripePattern pattern(Color::White, Color::Black);
			s.material.pattern = &pattern;
			Color c = s.colorAt(point(1.5, 0, 0));

			Assert::IsTrue(c == Color::White);
		}

		TEST_METHOD(TestPatternSphereScaledPatternTranslated)
		{
			Logger::WriteMessage("Testing sphereScaledPatternTranslated");

			Sphere s;
			s.setTransform(scaling(2, 2, 2));
			StripePattern pattern(Color::White, Color::Black);
			pattern.setTransform(translation(0.5, 0, 0));
			s.material.pattern = &pattern;
			Color c = s.colorAt(point(2.5, 0, 0));

			Assert::IsTrue(c == Color::White);
		}

		TEST_METHOD(TestPatternDefaultTransform)
		{
			Logger::WriteMessage("Testing patternDefaultTransform");

			StripePattern pattern(Color::White, Color::Black);

			Assert::IsTrue(Matrix::identityMatrix == pattern.transform);
		}

		TEST_METHOD(TestPatternSetTransform)
		{
			Logger::WriteMessage("Testing patternSetTransform");

			StripePattern pattern(Color::White, Color::Black);
			pattern.setTransform(translation(1, 2, 3));

			Assert::IsTrue(translation(1, 2, 3) == pattern.transform);
		}

		TEST_METHOD(TestGradientPattern)
		{
			Logger::WriteMessage("Testing gradientPattern");

			GradientPattern pattern(Color::White, Color::Black);

			Assert::IsTrue(pattern.colorAt(point(0, 0, 0)) == Color::White);
			Assert::IsTrue(pattern.colorAt(point(0.25, 0, 0)) == Color(0.75, 0.75, 0.75));
			Assert::IsTrue(pattern.colorAt(point(0.5, 0, 0)) == Color(0.5, 0.5, 0.5));
			Assert::IsTrue(pattern.colorAt(point(0.75, 0, 0)) == Color(0.25, 0.25, 0.25));
		}

		TEST_METHOD(TestRingtPattern)
		{
			Logger::WriteMessage("Testing ringPattern");

			RingPattern pattern(Color::White, Color::Black);

			Assert::IsTrue(pattern.colorAt(point(0, 0, 0)) == Color::White);
			Assert::IsTrue(pattern.colorAt(point(1, 0, 0)) == Color::Black);
			Assert::IsTrue(pattern.colorAt(point(0, 0, 1)) == Color::Black);
		}

		TEST_METHOD(TestCheckerPattern1)
		{
			Logger::WriteMessage("Testing checkerPattern1");

			CheckerPattern pattern(Color::White, Color::Black);

			Assert::IsTrue(pattern.colorAt(point(0, 0, 0)) == Color::White);
			Assert::IsTrue(pattern.colorAt(point(0.99, 0, 0)) == Color::White);
			Assert::IsTrue(pattern.colorAt(point(1.01, 0, 0)) == Color::Black);
		}

		TEST_METHOD(TestCheckerPattern2)
		{
			Logger::WriteMessage("Testing checkerPattern2");

			CheckerPattern pattern(Color::White, Color::Black);

			Assert::IsTrue(pattern.colorAt(point(0, 0, 0)) == Color::White);
			Assert::IsTrue(pattern.colorAt(point(0, 0.99, 0)) == Color::White);
			Assert::IsTrue(pattern.colorAt(point(0, 1.01, 0)) == Color::Black);
		}

		TEST_METHOD(TestCheckerPattern3)
		{
			Logger::WriteMessage("Testing checkerPattern3");

			CheckerPattern pattern(Color::White, Color::Black);

			Assert::IsTrue(pattern.colorAt(point(0, 0, 0)) == Color::White);
			Assert::IsTrue(pattern.colorAt(point(0, 0, 0.99)) == Color::White);
			Assert::IsTrue(pattern.colorAt(point(0, 0, 1.01)) == Color::Black);
		}
	};
}