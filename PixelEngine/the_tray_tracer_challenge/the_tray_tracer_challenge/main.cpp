#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "tuple.h"
#include "canvas.h"
#include "color.h"
#include "matrix.h"

#include <iostream>
#include <chrono>
#include <fstream>


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

		double values1[] =
		{
			-5, 2, 6, -8,
			1, -5, 1, 8,
			7, 7, -6, -7,
			1, -3, 7, 4
		};
		RayTracer::Matrix matrix1 = RayTracer::Matrix(4, 4, values1);

		std::cout << "Cofactor(3, 2): " << matrix1.getCofactor(3, 2) << std::endl;
		std::cout << "Cofactor(2, 3): " << matrix1.getCofactor(2, 3) << std::endl;
		std::cout << "Determinant: " << matrix1.getDeterminant() << std::endl;
		std::cout << "Cofactor(3, 2) / Determinant: " << (matrix1.getCofactor(3, 2) / matrix1.getDeterminant()) << std::endl;
		std::cout << "105 / 532: " << (105.0 / 532.0) << std::endl;
		RayTracer::Matrix matrix2 = matrix1.getInverse();
		std::cout << "Matrix[2][3]: " << matrix2[2][3] << std::endl;
		matrix2.print();

		projectile = Projectile(
			RayTracer::Tuple(9.0, 14.0, 0.0, 0.0),
			RayTracer::Tuple(0.0, 0.0, 0.0, 0.0));

		environment = Environment(
			RayTracer::Tuple(-0.0, 0.0, 0.0, 0.0),
			RayTracer::Tuple(0.0, -0.4, 0.0, 0.0));
		
		return true;
	}

	bool OnUserUpdate(float dTime) override
	{
		FillCircle({ 
			(int)(projectile.position.x), (int)(projectile.position.y) }, 
			3);
		canvas.writePixel((int)(projectile.position.x), ScreenHeight() - (int)(projectile.position.y), RayTracer::Color(1, 1, 1));
		projectile.position = projectile.position + projectile.velocity;
		projectile.velocity = projectile.velocity + environment.gravity + environment.wind;

		if (projectile.position.y < -0.1)
		{
			std::string test = canvas.getPPM();
			std::ofstream ppmFile("projectile.PPM");
			ppmFile << canvas.getPPM();
			ppmFile.close();
			return false;
		}
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