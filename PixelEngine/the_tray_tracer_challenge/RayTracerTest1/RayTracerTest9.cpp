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
	};
}