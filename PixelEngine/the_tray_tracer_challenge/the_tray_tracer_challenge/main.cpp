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
#include "scenes.h"
//#include "benchmarks.h"

#include <iostream>
#include <chrono>
#include <fstream>

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

using RayTracer::rotationX;
using RayTracer::rotationY;
using RayTracer::rotationZ;
using RayTracer::translation;
using RayTracer::scaling;
using RayTracer::getLighting;
using RayTracer::createDfaultWorld;

using DoubleHelpers::MATH_PI;


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


		Canvas image(ScreenWidth(), ScreenHeight());

		auto timeStart = std::chrono::high_resolution_clock::now();
		drawDefaultScene(image);
		auto timeEnd = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);

		std::cout << "Time to draw: " << duration.count() << std::endl;

		drawCanvasToScreen(image);

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

	return 0;
}