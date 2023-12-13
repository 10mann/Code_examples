#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "tuple.h"
#include "canvas.h"
#include "color.h"
#include "matrix.h"
#include "DoubleHelpers.h"
#include "ray.h"
#include "sphere.h"
#include "intersection.h"
#include "intersection_list.h"
#include "material.h"
#include "point_light.h"
#include "world.h"
#include "camera.h"
#include "stripe_pattern.h"
#include "gradient_pattern.h"
#include "plane.h"
#include "test_pattern.h"
#include "cylinder.h"
#include "cone.h"
#include "group.h"
#include "bounding_box.h"

#include "scenes.h"
#include "benchmarks.h"

#include <iostream>
#include <chrono>
#include <fstream>
#include <thread>
#include <immintrin.h>

using RayTracer::Matrix;
using RayTracer::Tuple;
using RayTracer::Ray;
using RayTracer::Sphere;
using RayTracer::Intersection;
using RayTracer::IntersectionList;
using RayTracer::World;
using RayTracer::Material;
using RayTracer::Color;
using RayTracer::PointLight;
using RayTracer::Canvas;
using RayTracer::ComputeValues;
using RayTracer::Camera;
using RayTracer::StripePattern;
using RayTracer::GradientPattern;
using RayTracer::Plane;
using RayTracer::Shape;
using RayTracer::TestPattern;
using RayTracer::Cylinder;
using RayTracer::Cone;
using RayTracer::Group;
using RayTracer::BoundingBox;

using RayTracer::rotationX;
using RayTracer::rotationY;
using RayTracer::rotationZ;
using RayTracer::translation;
using RayTracer::scaling;
using RayTracer::getLighting;
using RayTracer::createDfaultWorld;
using RayTracer::benchmarkMatrixMult;
using RayTracer::benchmarkGetDistance;
using RayTracer::benchmarkIsInShadow;
using RayTracer::benchmarkGetSubMatrix;
using RayTracer::benchmarkGetInverse;
using RayTracer::benchmarkCompareCubeIntersect;
using RayTracer::glassSphere;
using RayTracer::drawCubeScene1;
using RayTracer::drawCubeScene2;
using RayTracer::drawCubeScene3;
using RayTracer::drawCubeScene4;
using RayTracer::drawCylinderScene1;
using RayTracer::drawCylinderScene2;
using RayTracer::drawConeScene1;
using RayTracer::drawConeScene2;
using RayTracer::drawGroupScene1;

using DoubleHelpers::MATH_PI;

void testFunc(void)
{
	std::cout << "Hello" << std::endl;
}

void testFunc2(int x, int y, int z, int w, int a, int b, int c)
{
	std::cout << "Hello, " << x << std::endl;
}


class Projectile
{
public:
	RayTracer::Tuple velocity;
	RayTracer::Tuple position;

	Projectile()
	{

	}

	Projectile(RayTracer::Tuple velocity, RayTracer::Tuple position)
	{
		this->velocity = velocity;
		this->position = position;
	}
};

class Environment
{
public:
	RayTracer::Tuple wind;
	RayTracer::Tuple gravity;

	Environment()
	{

	}

	Environment(RayTracer::Tuple wind, RayTracer::Tuple gravity)
	{
		this->wind = wind;
		this->gravity = gravity;
	}
};

class Game : public olc::PixelGameEngine
{
public:
	Game();
	Projectile projectile;
	Environment environment;
	RayTracer::Canvas canvas;

	bool OnUserCreate() override
	{
		sAppName = "TheRayTracerChallenge";
		canvas = RayTracer::Canvas(ScreenWidth(), ScreenHeight());

		//projectile = Projectile(
		//	RayTracer::Tuple(9.0, 14.0, 0.0, 0.0),
		//	RayTracer::Tuple(0.0, 0.0, 0.0, 0.0));

		//environment = Environment(
		//	RayTracer::Tuple(-0.0, 0.0, 0.0, 0.0),
		//	RayTracer::Tuple(0.0, -0.4, 0.0, 0.0));


		unsigned int threadCount = DEFAULT_RENDER_THREADS;

		if (OVERRIDE_THREAD_COUNT == 0)
		{
			threadCount = std::thread::hardware_concurrency() * 4;
			if (threadCount == 0)
			{
				threadCount = DEFAULT_RENDER_THREADS;
			}
			else if (threadCount > MAX_RENDER_THREADS)
			{
				threadCount = MAX_RENDER_THREADS;
			}
		}
		std::cout << "Render threads: " << threadCount << std::endl;
		Camera::setRenderThreads(threadCount);

		Canvas image(ScreenWidth(), ScreenHeight());
		auto timeStart = std::chrono::steady_clock::now();
		//drawDefaultScene(image);
		//drawDefaultScene(image);
		//drawDefaultScene4(image);
		//drawMarbleMadness(image);
		//drawDefaultRefractionScene1(image);
		drawSphereGrid(image);
		//drawCubeScene1(image);
		//drawCubeScene2(image);
		//drawCubeScene3(image);
		//drawCubeScene4(image);
		//drawCylinderScene1(image);
		//drawCylinderScene2(image);
		//drawConeScene1(image);
		//drawConeScene2(image);
		//drawGroupScene1(image);
		auto timeEnd = std::chrono::steady_clock::now();
		auto drawDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);
		std::cout << "Time to draw: " << drawDuration.count() << "ms" << std::endl;
		drawCanvasToScreen(image);
		//saveToFile(image, "MarbleMadness.ppm");

		//Sphere s1;
		//s1.setTransform(translation(-2, -2, 0));

		//Sphere s2;
		//s2.setTransform(translation(-2, 2, 0));

		//Sphere s3;
		//s3.setTransform(scaling(4, 4, 4));

		//std::cout << "S1: " << &s1 << "\n";
		//std::cout << "S2: " << &s2 << "\n";
		//std::cout << "S3: " << &s3 << "\n";

		//Group g;
		//g.addChild(&s1);
		//g.addChild(&s2);
		//g.addChild(&s3);
		//g.divide(1);

		//Group* sg = (Group*)(g.objects[1]);
		//Group* ssg1 = (Group*)(sg->objects[0]);
		//Group* ssg2 = (Group*)(sg->objects[1]);
		//std::cout << "G count: " << g.objects.size() << std::endl;
		//std::cout << "SubG count: " << sg->objects.size() << std::endl;
		//std::cout << "G[0]: " << g.objects[0] << "\n";
		//std::cout << "SG[0]: " << sg->objects[0] << "\n";
		//std::cout << "SG[1]: " << sg->objects[1] << "\n";
		//std::cout << "SSG1[0]: " << ssg1->objects[0] << "\n";
		//std::cout << "SSG2[0]: " << ssg2->objects[0] << "\n";
		////std::cout << "Left count: " << list[0].size() << std::endl;
		////std::cout << "Right count: " << list[1].size() << std::endl;

		////Group* g = new Group();
		////delete g;

		////Group g;

		return true;
	}

	bool OnUserUpdate(float dTime) override
	{
		return true;
	}

	bool Draw(int32_t x, int32_t y, olc::Pixel p) override
	{
		return PixelGameEngine::Draw(x, ScreenHeight() - y, p);
	}

	void drawCanvasToScreen(Canvas& canvas)
	{
		int width = canvas.width;
		int height = canvas.height;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				Color color = canvas.getPixel(x, y);
				uint16_t red = (color.red * 255) > 255 ? 255: (color.red * 255);
				uint16_t green = (color.green * 255) > 255 ? 255: (color.green * 255);
				uint16_t blue = (color.blue * 255) > 255 ? 255: (color.blue * 255);
				olc::Pixel pixel(red, green, blue);
				Draw(x, y, pixel);
			}
		}
	}

	void saveToFile(Canvas& image, std::string fileName)
	{
		std::ofstream file;
		file.open(fileName);
		file << image.getPPM();
		file.close();
	}
};

Game::Game()
{

}


int main()
{
	Game game;
	if (game.Construct(1024, 576, 1, 1))
	{
		game.Start();
	}

	//benchmarkGetInverse(1000000);

	return 0;
}