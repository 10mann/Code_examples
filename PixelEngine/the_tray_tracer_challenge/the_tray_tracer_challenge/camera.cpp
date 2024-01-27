#include "camera.h"
#include "DoubleHelpers.h"
#include "raytracer_config.h"

#include <cmath>
#include <thread>
#include <iostream>
#include <chrono>
#include <future>


using DoubleHelpers::EPSILON;

namespace RayTracer
{
	int Camera::renderThreads = DEFAULT_RENDER_THREADS;

	// ========================= Constructors ==========================
	Camera::Camera()
		: width(0), height(0), fieldOfView(0), transform(Matrix::identityMatrix), pixelSize(0),
		aspectRatio(1), halfViewX(0), halfViewY(0)
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

		invTransform = transform.getInverse();
	}

	// ============================ Methods ============================

	void Camera::calculateInverseTransform(void)
	{
		invTransform = transform.getInverse();
	}

	Ray Camera::getRay(double x, double y)
	{
		Tuple pixel = point(
			(halfViewX - ((x + 0.5) * pixelSize)),
			(halfViewY - ((y + 0.5) * pixelSize)), -1) * invTransform;

		Tuple origin = point(0, 0, 0) * invTransform;
		Tuple direction = (pixel - origin).getNormalized();

		return Ray(origin, direction);
	}

	Canvas Camera::render(World& world)
	{
		Canvas image(width, height);
		int threads = renderThreads;

		int subWidth = width / threads;
		int startX = 0;
		int startY = 0;

		world.calculateInverseTransforms();
		calculateInverseTransform();


		for (int i = 0; i < threads - 1; i++)
		{
			futures.push_back(std::async(std::launch::async, &Camera::renderPartScreen, this,
				std::ref(world),
				std::ref(image)));
		}

		for (auto& f : futures)
		{
			f.wait();
		}

		return image;
	}

	// =========================== Operators ===========================

	

	// ============================ Helpers =============================

	void Camera::renderPartScreen(World& world, Canvas& canvas)
	{
		int index = 0;
		while (index < canvas.width)
		{
			index = canvas.getNextIndex();
			for (int y = 0; y < canvas.height; y++)
			{
				RayTracer::Ray ray = getRay(index, y);
				canvas.writePixel(index, y, world.getColor(ray, MAX_REFLECTIONS));
			}
		}
	}

	void Camera::setRenderThreads(int nThreads)
	{
		Camera::renderThreads = nThreads;
	}
}
