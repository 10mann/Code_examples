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


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using RayTracer::Ray;
using RayTracer::Tuple;
using RayTracer::point;
using RayTracer::vector;
using RayTracer::Color;
using RayTracer::Material;
using RayTracer::Matrix;
using RayTracer::Sphere;
using RayTracer::Intersection;
using RayTracer::IntersectionList;
using DoubleHelpers::isEqualDouble;
using DoubleHelpers::MATH_PI;
using RayTracer::translation;
using RayTracer::scaling;
using RayTracer::rotationX;
using RayTracer::rotationY;
using RayTracer::rotationZ;
using RayTracer::getReflection;
using RayTracer::PointLight;
using RayTracer::getLighting;

namespace RayTracerTest6
{
	TEST_CLASS(RayTracerTest6)
	{
	public:

		TEST_METHOD(TestGetNormal1)
		{
			Logger::WriteMessage("Testing sphereGetNormal1");
			Sphere sphere;
			Tuple norm = sphere.getNormal(point(1, 0, 0));

			Assert::IsTrue(norm == vector(1, 0, 0));
		}

		TEST_METHOD(TestGetNormal2)
		{
			Logger::WriteMessage("Testing sphereGetNormal2");
			Sphere sphere;
			Tuple norm = sphere.getNormal(point(0, 1, 0));

			Assert::IsTrue(norm == vector(0, 1, 0));
		}

		TEST_METHOD(TestGetNormal3)
		{
			Logger::WriteMessage("Testing sphereGetNormal3");
			Sphere sphere;
			Tuple norm = sphere.getNormal(point(0, 0, 1));

			Assert::IsTrue(norm == vector(0, 0, 1));
		}

		TEST_METHOD(TestGetNormal4)
		{
			Logger::WriteMessage("Testing sphereGetNormal4");
			Sphere sphere;
			Tuple norm = sphere.getNormal(point(std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3));

			Assert::IsTrue(norm == vector(std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3));
		}

		TEST_METHOD(TestGetNormalNormalize)
		{
			Logger::WriteMessage("Testing sphereGetNormalNormalize");
			Sphere sphere;
			Tuple norm = sphere.getNormal(point(std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3));
			Tuple vecNorm = vector(std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3);
			vecNorm.normalize();
			Assert::IsTrue(norm == vecNorm);
		}

		TEST_METHOD(TestGetNormalTranslated)
		{
			Logger::WriteMessage("Testing sphereGetNormalTranslated");
			Sphere sphere;
			Matrix m = translation(0, 1, 0);
			sphere.setTransform(m);
			Tuple norm = sphere.getNormal(point(0, 1.70711, -0.70711));
			//Tuple vecNorm = vector(0, 1.70711, -0.70711);
			//vecNorm.normalize();
			Assert::IsTrue(norm == vector(0, 0.70711, -0.70711));
		}

		TEST_METHOD(TestGetNormalScaledRotated)
		{
			Logger::WriteMessage("Testing sphereGetNormalScaledRotated");
			Sphere sphere;
			Matrix m = scaling(1, 0.5, 1) * rotationZ(MATH_PI / 5);
			sphere.setTransform(m);
			Tuple norm = sphere.getNormal(point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2));
			Assert::IsTrue(norm == vector(0, 0.97014, -0.24254));
		}

		TEST_METHOD(TestGetReflectionFlat)
		{
			Logger::WriteMessage("Testing getReflectionFlat");
			Tuple normal = vector(0, 1, 0).getNormalized();
			Tuple in = vector(1, -1, 0);

			Tuple out = getReflection(in, normal);
			Assert::IsTrue(out == vector(1, 1, 0));
		}

		TEST_METHOD(TestGetReflectionSlanted)
		{
			Logger::WriteMessage("Testing getReflectionSlanted");
			Tuple normal = vector(-1, 1, 0).getNormalized();
			Tuple in = vector(1, 0, 0);

			Tuple out = getReflection(in, normal);
			Assert::IsTrue(out == vector(0, 1, 0));
		}

		TEST_METHOD(TestCreatePointLight)
		{
			Logger::WriteMessage("Testing createPointLight");
			Tuple pos = point(0, 0, 0);
			Color intensity(1, 1, 1);
			PointLight light(intensity, pos);

			Assert::IsTrue(light.position == pos);
			Assert::IsTrue(light.intensity == intensity);
		}

		TEST_METHOD(TestCreateMaterial)
		{
			Logger::WriteMessage("Testing createMaterial");
			Material m;

			Assert::IsTrue(isEqualDouble(m.ambient, 0.1));
			Assert::IsTrue(isEqualDouble(m.diffuse, 0.9));
			Assert::IsTrue(isEqualDouble(m.specular, 0.9));
			Assert::IsTrue(isEqualDouble(m.shininess, 200.0));
			Assert::IsTrue(m.color == Color(1, 1, 1));
		}

		TEST_METHOD(TestAddMaterialSphere)
		{
			Logger::WriteMessage("Testing addMaterialSphere");
			Sphere s;
			Material m;
			s.material = m;

			Assert::IsTrue(m == s.material);
		}

		TEST_METHOD(TestAddMaterialSphere2)
		{
			Logger::WriteMessage("Testing addMaterialSphere2");
			Sphere s;
			Material m;
			m.ambient = 1;
			s.material = m;

			Assert::IsTrue(m == s.material);
		}

		TEST_METHOD(TestGetLightingSimple)
		{
			Logger::WriteMessage("Testing getLightingSimple");
			Material m;
			Tuple position = point(0, 0, 0);
			Tuple eyeDir = vector(0, 0, -1);
			Tuple normal = vector(0, 0, -1);
			PointLight light = PointLight(Color(1, 1, 1), point(0, 0, -10));
			Color lighting = getLighting(m, light, position, eyeDir, normal);

			Assert::IsTrue(lighting == Color(1.9, 1.9, 1.9));
		}

		TEST_METHOD(TestGetLightingEyeSlanted)
		{
			Logger::WriteMessage("Testing getLightingEyeSlanted");
			Material m;
			Tuple position = point(0, 0, 0);
			Tuple eyeDir = vector(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);
			Tuple normal = vector(0, 0, -1);
			PointLight light = PointLight(Color(1, 1, 1), point(0, 0, -10));
			Color lighting = getLighting(m, light, position, eyeDir, normal);

			Assert::IsTrue(lighting == Color(1.0, 1.0, 1.0));
		}

		TEST_METHOD(TestGetLightingLightSlanted)
		{
			Logger::WriteMessage("Testing getLightingLightSlanted");
			Material m;
			Tuple position = point(0, 0, 0);
			Tuple eyeDir = vector(0, 0, -1);
			Tuple normal = vector(0, 0, -1);
			PointLight light = PointLight(Color(1, 1, 1), point(0, 10, -10));
			Color lighting = getLighting(m, light, position, eyeDir, normal);

			Assert::IsTrue(lighting == Color(0.7364, 0.7364, 0.7364));
		}

		TEST_METHOD(TestGetLightingLighEyetSlanted)
		{
			Logger::WriteMessage("Testing getLightingLightEyeSlanted");
			Material m;
			Tuple position = point(0, 0, 0);
			Tuple eyeDir = vector(0, -std::sqrt(2) / 2, -std::sqrt(2) / 2);
			Tuple normal = vector(0, 0, -1);
			PointLight light = PointLight(Color(1, 1, 1), point(0, 10, -10));
			Color lighting = getLighting(m, light, position, eyeDir, normal);

			Assert::IsTrue(lighting == Color(1.6364, 1.6364, 1.6364));
		}

		TEST_METHOD(TestGetLightingLightBehind)
		{
			Logger::WriteMessage("Testing getLightingLightBehind");
			Material m;
			Tuple position = point(0, 0, 0);
			Tuple eyeDir = vector(0, 0, -1);
			Tuple normal = vector(0, 0, -1);
			PointLight light = PointLight(Color(1, 1, 1), point(0, 0, 10));
			Color lighting = getLighting(m, light, position, eyeDir, normal);

			Assert::IsTrue(lighting == Color(0.1, 0.1, 0.1));
		}
	};
}