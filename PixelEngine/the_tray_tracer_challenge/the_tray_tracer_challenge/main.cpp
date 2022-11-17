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

#include <iostream>
#include <chrono>
#include <fstream>

using RayTracer::Matrix;
using RayTracer::Tuple;
using RayTracer::rotationX;
using RayTracer::rotationY;
using RayTracer::rotationZ;
using RayTracer::translation;
using RayTracer::scaling;
using RayTracer::Ray;
using RayTracer::Sphere;
using RayTracer::Intersection;
using RayTracer::IntersectionList;
using DoubleHelpers::MATH_PI;

void benchmarkMatrixMult()
{
	RayTracer::Matrix matrix1;
	matrix1[0][0] = 1;
	matrix1[0][1] = 2;
	matrix1[0][2] = 3;
	matrix1[0][3] = 4;
	matrix1[1][0] = 5;
	matrix1[1][1] = 6;
	matrix1[1][2] = 7;
	matrix1[1][3] = 8;
	matrix1[2][0] = 9;
	matrix1[2][1] = 8;
	matrix1[2][2] = 7;
	matrix1[2][3] = 6;
	matrix1[3][0] = 5;
	matrix1[3][1] = 4;
	matrix1[3][2] = 3;
	matrix1[3][3] = 2;

	RayTracer::Matrix matrix2;
	matrix2[0][0] = -2;
	matrix2[0][1] = 1;
	matrix2[0][2] = 2;
	matrix2[0][3] = 3;
	matrix2[1][0] = 3;
	matrix2[1][1] = 2;
	matrix2[1][2] = 1;
	matrix2[1][3] = -1;
	matrix2[2][0] = 4;
	matrix2[2][1] = 3;
	matrix2[2][2] = 6;
	matrix2[2][3] = 5;
	matrix2[3][0] = 1;
	matrix2[3][1] = 2;
	matrix2[3][2] = 7;
	matrix2[3][3] = 8;

	RayTracer::Matrix matrix3 = matrix1 * matrix2;
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::microseconds(0));
	long long avgDuration = 0;
	const int testTimes = 100;
	for (int times = 0; times < testTimes; times++)
	{
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 1000000; i++)
		{
			matrix3 = matrix1 * matrix2;
		}
		auto end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		avgDuration += duration.count();
	}

	avgDuration /= testTimes;

	std::cout << "Exectuion time: " << avgDuration << std::endl;
}

void drawClock(olc::PixelGameEngine* engine)
{		
	// Draw clock using rotation matrix
	Tuple clockP = RayTracer::point(0, 1, 0);

	for (double rads = 0.0; rads < (2.0 * MATH_PI); rads += (MATH_PI / 6.0))
	{
		Tuple hourP = rotationZ(rads) * clockP;
		hourP = scaling(150, 150, 150) * hourP;
		hourP = translation(engine->ScreenWidth() / 2, engine->ScreenHeight() / 2, 0) * hourP;
		engine->FillCircle({ (int)(hourP.x), (int)(hourP.y) }, 3);
	}
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
		
		//benchmarkMatrixMult();

		//Tuple p = RayTracer::point(1, 0, 0);
		//Matrix halfQuart = rotationZ(DoubleHelpers::MATH_PI / 4.0);
		//Matrix fullQuart = rotationZ(DoubleHelpers::MATH_PI / 2.0);

		//Tuple halfQuartP = halfQuart * p;
		//Tuple fullQuartP = fullQuart * p;

		//halfQuartP.print();
		//fullQuartP.print();

		projectile = Projectile(
			RayTracer::Tuple(9.0, 14.0, 0.0, 0.0),
			RayTracer::Tuple(0.0, 0.0, 0.0, 0.0));

		environment = Environment(
			RayTracer::Tuple(-0.0, 0.0, 0.0, 0.0),
			RayTracer::Tuple(0.0, -0.4, 0.0, 0.0));

		drawClock(this);

		Sphere sphere;
		Intersection i1(1, &sphere);
		Intersection i2(2, &sphere);
		IntersectionList list(i1, i2);
		Intersection iHit = list.hit();
		std::cout << iHit.i << std::endl;
		return true;
	}

	bool OnUserUpdate(float dTime) override
	{
		//FillCircle({ 
		//	(int)(projectile.position.x), (int)(projectile.position.y) }, 
		//	3);
		//canvas.writePixel((int)(projectile.position.x), ScreenHeight() - (int)(projectile.position.y), RayTracer::Color(1, 1, 1));
		//projectile.position = projectile.position + projectile.velocity;
		//projectile.velocity = projectile.velocity + environment.gravity + environment.wind;

		//if (projectile.position.y < -0.1)
		//{
		//	std::string test = canvas.getPPM();
		//	std::ofstream ppmFile("projectile.PPM");
		//	ppmFile << canvas.getPPM();
		//	ppmFile.close();
		//	return false;
		//}
		return true;
	}

	bool Draw(int32_t x, int32_t y, olc::Pixel p) override
	{
		return PixelGameEngine::Draw(x, ScreenHeight() - y, p);
	}
};

Game::Game()
{

}


int main()
{
	Game game;
	if (game.Construct(680, 400, 1, 1))
	{
		game.Start();
	}

	return 0;
}