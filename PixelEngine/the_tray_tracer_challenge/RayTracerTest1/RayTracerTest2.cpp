#include "pch.h"
#include "CppUnitTest.h"
#include "../the_tray_tracer_challenge/color.h"
#include "../the_tray_tracer_challenge/DoubleHelpers.h"
#include "../the_tray_tracer_challenge/canvas.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using RayTracer::Color;
using RayTracer::Canvas;

namespace RayTracerTest2
{
	TEST_CLASS(RayTracerTest2)
	{
	public:

		TEST_METHOD(TestColor)
		{
			Logger::WriteMessage("Testing color");
			Color color(-0.5, 0.4, 1.7);
			Assert::IsTrue(DoubleHelpers::isEqualDouble(color.red, -0.5));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(color.green, 0.4));
			Assert::IsTrue(DoubleHelpers::isEqualDouble(color.blue, 1.7));
		}

		TEST_METHOD(TestAddColor)
		{
			Logger::WriteMessage("Testing addColor");
			Color color1(0.9, 0.6, 0.75);
			Color color2(0.7, 0.1, 0.25);
			Color sumColor = color1 + color2;
			Assert::IsTrue(sumColor == (Color(1.6, 0.7, 1.0)));
		}

		TEST_METHOD(TestSubColor)
		{
			Logger::WriteMessage("Testing subColor");
			Color color1(0.9, 0.6, 0.75);
			Color color2(0.7, 0.1, 0.25);
			Color sumColor = color1 - color2;
			Assert::IsTrue(sumColor == (Color(0.2, 0.5, 0.5)));
		}

		TEST_METHOD(TestMultiplyScalar)
		{
			Logger::WriteMessage("Testing multiplyScalar");
			Color color(0.9, 0.6, 0.75);
			Color prodColor = color * 2;
			Assert::IsTrue(prodColor == (Color(1.8, 1.2, 1.5)));
		}

		TEST_METHOD(TestMultiplyColor)
		{
			Logger::WriteMessage("Testing multiplyColor");
			Color color1(0.9, 0.6, 0.75);
			Color color2(1.0, 0.5, 0.1);
			Color prodColor = color1 * color2;
			Assert::IsTrue(prodColor == (Color(0.9, 0.3, 0.075)));
		}

		TEST_METHOD(TestCreateCanvas)
		{
			Logger::WriteMessage("Testing createCanvas");
			Canvas canvas(10, 20);
			Assert::AreEqual(canvas.width, 10);
			Assert::AreEqual(canvas.height, 20);

			for (auto const& color : canvas.pixels)
			{
				Assert::IsTrue(color == Color(0, 0, 0));
			}
		}

		TEST_METHOD(TestWritePixel)
		{
			Logger::WriteMessage("Testing writePixel");
			Canvas canvas(10, 20);
			Color red(1, 0, 0);
			canvas.writePixel(2, 3, red);

			Assert::IsTrue(canvas.getPixel(2, 3) == red);
		}

		TEST_METHOD(TestGetPPM)
		{
			Logger::WriteMessage("Testing getPPM");
			Canvas canvas(5, 3);
			Color c1(1.5, 0, 0);
			Color c2(0, 0.5, 0);
			Color c3(-0.5, 0, 1);
			canvas.writePixel(0, 0, c1);
			canvas.writePixel(2, 1, c2);
			canvas.writePixel(4, 2, c3);

			std::string ppmStr = canvas.getPPM();
			Assert::IsTrue(
				std::string("P3\n5 3\n255\n255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n") == ppmStr);
		}

		TEST_METHOD(TestGetPPMLineBreak)
		{
			Logger::WriteMessage("Testing getPPMLineBreak");
			Canvas canvas(10, 2, Color(1, 0.8, 0.6));
			std::string ppmStr = canvas.getPPM();
			Assert::IsTrue(
				std::string("P3\n10 2\n255\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n") == ppmStr);
		}

		TEST_METHOD(TestPPMNewlineTerminated)
		{
			Logger::WriteMessage("Testing getPPMNewlineTerminated");
			Canvas canvas(10, 2);
			std::string ppmStr = canvas.getPPM();
			Assert::IsTrue(ppmStr[ppmStr.size() - 1] == '\n');
		}
	};
}
