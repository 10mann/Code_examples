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

#include "scenes.h"
#include "benchmarks.h"

#include <iostream>
#include <chrono>
#include <fstream>
#include <thread>

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

		projectile = Projectile(
			RayTracer::Tuple(9.0, 14.0, 0.0, 0.0),
			RayTracer::Tuple(0.0, 0.0, 0.0, 0.0));

		environment = Environment(
			RayTracer::Tuple(-0.0, 0.0, 0.0, 0.0),
			RayTracer::Tuple(0.0, -0.4, 0.0, 0.0));

		//double values[] =
		//{
		//	1, 3, 5, 9,
		//	1, 3, 1, 7,
		//	4, 3, 9, 7,
		//	5, 2, 0, 9
		//};
		//Matrix m(4, 4, values);
		//m.getSubMatrix(0, 0);

		//double values[] =
		//{
		//	4, 2, 3, 
		//	4, 5, 6,
		//	7, 8, 9
		//};
		//Matrix m(3, 3, values);

		//double det = m.getDeterminant();
		//std::cout << "Det: " << det << std::endl;

		//long long duration = benchmarkGetInverse(1000000);
		//std::cout << "GetSubMatrix time: " << duration << std::endl;
		
		//Canvas image(ScreenWidth(), ScreenHeight());
		//auto timeStart = std::chrono::steady_clock::now();
		////drawDefaultScene(image);
		//drawDefaultScene3(image);
		//auto timeEnd = std::chrono::steady_clock::now();
		//auto drawDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);
		//std::cout << "Time to draw: " << drawDuration.count() << std::endl;
		//
		//drawCanvasToScreen(image);

		World world = createDfaultWorld();

		PointLight light(Color(1, 1, 1), RayTracer::point(-10, 10, -10));

		Sphere s1;
		Material m;
		m.color = Color(0.8, 1, 0.6);
		m.diffuse = 0.7;
		m.specular = 0.2;
		s1.material = m;

		Sphere s2;
		s2.transform = scaling(0.5, 0.5, 0.5);

		std::cout << "World contains s2: " << world.containsObject(s2) << std::endl;

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
};

Game::Game()
{

}


int main()
{
	Game game;
	if (game.Construct(680, 680, 1, 1))
	{
		game.Start();
	}

	//benchmarkGetInverse(1000000);

	return 0;
}