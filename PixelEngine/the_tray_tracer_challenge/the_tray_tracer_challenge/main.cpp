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

using RayTracer::rotationX;
using RayTracer::rotationY;
using RayTracer::rotationZ;
using RayTracer::translation;
using RayTracer::scaling;
using RayTracer::getLighting;
using RayTracer::createDfaultWorld;

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
		hourP = translation(engine->ScreenWidth() / 2.0, engine->ScreenHeight() / 2.0, 0) * hourP;
		engine->FillCircle({ (int)(hourP.x), (int)(hourP.y) }, 3);
	}
}

void drawCirclebByRay(olc::PixelGameEngine* engine)
{
	int width = engine->ScreenWidth();
	int height = engine->ScreenHeight();
	Sphere s;
	//Matrix m = RayTracer::rotationY(DoubleHelpers::MATH_PI / 4);
	//m = m * RayTracer::scaling(1, 1, 0.5);
	//s.setTransform(m);
	double wallZ = 10;
	Tuple origin = RayTracer::point(0, 0, -5);
	double wallSize = ((wallZ - origin.z) / std::abs(origin.z)) * 2 + 1;
	double pixelSizeY = wallSize / height;
	double pixelSizeX = wallSize / height;

	for (int y = 0; y < height; y++)
	{
		double worldY = (wallSize / 2) - (pixelSizeY * y);
		for (int x = 0; x < width; x++)
		{
			double worldX = -(wallSize / 2) + (pixelSizeX * x);
			Tuple wallPoint = RayTracer::point(worldX, worldY, wallZ);
			Tuple dir = (wallPoint - origin);
			dir.normalize();
			Ray ray(origin, dir);
			if (ray.getIntersection(s).count() > 0)
			{
				engine->Draw({ x, y }, olc::Pixel(0, 255, 0));
			}
			else
			{
				engine->Draw({ x, y }, olc::Pixel(0, 0, 0));
			}
		}
	}
}

void drawSpherebByRay(olc::PixelGameEngine* engine)
{
	//int width = engine->ScreenWidth();
	//int height = engine->ScreenHeight();
	//Canvas canvas(width, height);
	//Sphere s;
	//s.material = Material();
	//s.material.color = Color(0.25, 0.74, 0.96);
	//s.material.shininess = 200;
	//PointLight light(Color(1, 1, 1), RayTracer::point(0, 0, -10));

	//double wallZ = 10;
	//Tuple origin = RayTracer::point(0, 0, -5);
	////double wallSize = ((wallZ - origin.z) / std::abs(origin.z)) * 2 + 1;
	//double wallSize = 10;
	//double pixelSizeY = wallSize / height;
	//double pixelSizeX = wallSize / height;
	//
	//for (int y = 0; y < height; y++)
	//{
	//	double worldY = (wallSize / 2) - (pixelSizeY * y);
	//	for (int x = 0; x < width; x++)
	//	{
	//		double worldX = -(wallSize / 2) + (pixelSizeX * x);
	//		Tuple wallPoint = RayTracer::point(worldX, worldY, wallZ);
	//		Tuple dir = (wallPoint - origin);
	//		dir.normalize();
	//		Ray ray(origin, dir);
	//		IntersectionList hits = ray.getIntersection(&s);
	//		if (hits.count() > 0)
	//		{
	//			Intersection hit = hits.hit();
	//			Tuple hitPos = ray.getPosition(hit.i);
	//			Tuple normal = s.getNormal(hitPos);
	//			Tuple eyeDir = -ray.direction;
	//			Color pixelColor = getLighting(hit.object->material, light, hitPos, eyeDir, normal);
	//			int16_t colorR = pixelColor.red * 255;
	//			if (colorR > 255)
	//			{
	//				colorR = 255;
	//			}

	//			int16_t colorG = pixelColor.green * 255;
	//			if (colorG > 255)
	//			{
	//				colorG = 255;
	//			}

	//			int16_t colorB = pixelColor.blue * 255;
	//			if (colorB > 255)
	//			{
	//				colorB = 255;
	//			}
	//			engine->Draw({ x, height - y }, olc::Pixel(colorR, colorG, colorB));
	//			canvas.writePixel(x, y, pixelColor);
	//		}
	//		else
	//		{
	//			engine->Draw({ x, y }, olc::Pixel(0, 0, 0));
	//		}
	//	}
	//}

	//std::ofstream file("sphere.ppm");
	//file << canvas.getPPM();
	//file.close();
}

long long benchmarkDrawSphere(int iterations)
{
	int width = 680;
	int height = 680;
	Canvas canvas(width, height);
	Sphere s;
	s.material = Material();
	s.material.color = Color(0.25, 0.74, 0.96);
	s.material.shininess = 200;
	PointLight light(Color(1, 1, 1), RayTracer::point(0, 0, -10));

	double wallZ = 10;
	Tuple origin = RayTracer::point(0, 0, -5);
	//double wallSize = ((wallZ - origin.z) / std::abs(origin.z)) * 2 + 1;
	double wallSize = 10;
	double pixelSizeY = wallSize / height;
	double pixelSizeX = wallSize / height;
	auto timeStart = std::chrono::high_resolution_clock::now();
	for (int it = 0; it < iterations; it++)
	{
		for (int y = 0; y < height; y++)
		{
			double worldY = (wallSize / 2) - (pixelSizeY * y);
			for (int x = 0; x < width; x++)
			{
				double worldX = -(wallSize / 2) + (pixelSizeX * x);
				Tuple wallPoint = RayTracer::point(worldX, worldY, wallZ);
				Tuple dir = (wallPoint - origin);
				dir.normalize();
				Ray ray(origin, dir);
				IntersectionList hits = ray.getIntersection(s);
				if (hits.count() > 0)
				{
					Intersection hit = hits.hit();
					Tuple hitPos = ray.getPosition(hit.i);
					Tuple normal = s.getNormal(hitPos);
					Tuple eyeDir = -ray.direction;
					Color pixelColor = getLighting(hit.object.material, light, hitPos, eyeDir, normal);
					int16_t colorR = pixelColor.red * 255;
					if (colorR > 255)
					{
						colorR = 255;
					}

					int16_t colorG = pixelColor.green * 255;
					if (colorG > 255)
					{
						colorG = 255;
					}

					int16_t colorB = pixelColor.blue * 255;
					if (colorB > 255)
					{
						colorB = 255;
					}
					canvas.writePixel(x, y, pixelColor);
				}
			}
		}
	}
	auto timeEnd = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);


	return duration.count();
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

		//drawClock(this);
		//drawCirclebByRay(this);

		//auto timeStart = std::chrono::high_resolution_clock::now();
		//drawSpherebByRay(this);
		//auto timeEnd = std::chrono::high_resolution_clock::now();
		//auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);

		//long long duration = benchmarkDrawSphere(10);
		//std::cout << "Time elapsed: " << duration << std::endl;

		//World world = createDfaultWorld();
		//Ray ray(RayTracer::point(0, 0, -5), RayTracer::vector(0, 0, 1));
		//IntersectionList intersections = world.getIntersections(ray);
		////intersections.sort();
		//std::cout << "Intersections: " << intersections.count() << std::endl;
		//for (auto& it : intersections.intersections)
		//{
		//	std::cout << it.i << ", ";
		//}
		//std::cout << std::endl;

		//World world = createDfaultWorld();
		//Ray ray(RayTracer::point(0, 0, -5), RayTracer::vector(0, 0, 1));
		//Sphere s = world.objects[0];
		//Intersection intersection(4, s);
		//ComputeValues computeValues = ray.getComputeValues(intersection);
		//Color color = world.getHitColor(computeValues);
		//color.print();


		//World world = createDfaultWorld();
		//Ray ray(RayTracer::point(0, 0, -5), RayTracer::vector(0, 1, 0));

		//Color color = world.getColor(ray);
		//color.print();

		//World world = createDfaultWorld();
		//Ray ray(RayTracer::point(0, 0, 0.75), RayTracer::vector(0, 0, -1));
		//Sphere sOuter = world.objects[0];
		//world.objects[0].material.ambient = 1;
		//Sphere sInner = world.objects[1];
		//world.objects[1].material.ambient = 1;

		//Color color = world.getColor(ray);
		//color.print();
		//sInner.material.color.print();

		Tuple from = RayTracer::point(0, 0, 8);
		Tuple to = RayTracer::point(0, 0, 0);
		Tuple up = RayTracer::vector(0, 1, 0);

		Matrix view = viewTransform(from, to, up);
		view.print();

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
	if (game.Construct(680, 680, 1, 1))
	{
		game.Start();
	}

	return 0;
}