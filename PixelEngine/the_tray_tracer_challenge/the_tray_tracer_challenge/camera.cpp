#include "camera.h"
#include "DoubleHelpers.h"
#include "raytracer_config.h"

#include <cmath>
#include <thread>
#include <iostream>
#include <chrono>


using DoubleHelpers::EPSILON;

namespace RayTracer
{
	// ========================= Constructors ==========================
	Camera::Camera()
		: width(0), height(0), fieldOfView(0), transform(Matrix::identityMatrix), pixelSize(0)
	{
	}

	Camera::Camera(int width, int height, double fieldOfView)
		: width(width), height(height), fieldOfView(fieldOfView), transform(Matrix::identityMatrix)
	{
		double halfView = tan(fieldOfView / 2.0);
		aspectRatio = (double)width / (double)height;

		if (aspectRatio > (1.0 - EPSILON))
		{
			halfViewX = halfView;
			halfViewY = halfView / aspectRatio;
		}
		else
		{
			halfViewY = halfView;
			halfViewX = halfView * aspectRatio;
		}
		
		pixelSize = (halfViewX * 2) / width;
	}

	// ============================ Methods ============================
	Ray Camera::getRay(double x, double y)
	{
		Tuple pixel = transform.getInverse() * point(
			(halfViewX - ((x + 0.5) * pixelSize)),
			(halfViewY - ((y + 0.5) * pixelSize)), -1);

		Tuple origin = transform.getInverse() * point(0, 0, 0);
		Tuple direction = (pixel - origin).getNormalized();

		return Ray(origin, direction);
	}

	Canvas Camera::render(World& world)
	{
		Canvas image(width, height);

		int subWidth = width / MAX_RENDER_THREADS;
		int startX = 0;
		int startY = 0;

		std::thread threads[MAX_RENDER_THREADS];
		for (int i = 0; i < (MAX_RENDER_THREADS - 1); i++)
		{
			threads[i] = std::thread(&Camera::renderPartScreen, this,
				std::ref(world),
				std::ref(image),
				startX + subWidth * i, 
				startY, 
				subWidth, 
				height);
		}

		threads[MAX_RENDER_THREADS - 1] = std::thread(&Camera::renderPartScreen, this,
			std::ref(world),
			std::ref(image),
			startX + subWidth * (MAX_RENDER_THREADS - 1),
			startY,
			width - (startX + subWidth * (MAX_RENDER_THREADS - 1)),
			height);


		for (int i = 0; i < MAX_RENDER_THREADS; i++)
		{
			threads[i].join();
		}

		return image;
	}

	// =========================== Operators ===========================

	

	// ============================ Helpers =============================

	void Camera::renderPartScreen(World& world, Canvas& canvas, int startX, int startY, int width, int height)
	{
		for (int y = startY; y < height; y++)
		{
			for (int x = startX; x < (startX + width); x++)
			{
				RayTracer::Ray ray = getRay(x, y);
				canvas.writePixel(x, y, world.getColor(ray));
			}
		}
	}


}

