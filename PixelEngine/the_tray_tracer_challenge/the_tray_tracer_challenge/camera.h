#pragma once

#include "matrix.h"
#include "ray.h"
#include "canvas.h"
#include "world.h"

#include <future>

namespace RayTracer
{
	class Camera
	{
	public:

		// Variables
		int width;
		int height;
		static int renderThreads;
		double fieldOfView;
		Matrix transform;
		Matrix invTransform;
		double pixelSize;
		double halfViewX;
		double halfViewY;
		double aspectRatio;
		std::vector<std::future<void>> futures;

		// Constructors
		Camera();
		Camera(int width, int height, double fieldOfView);

		// Methods
		void calculateInverseTransform(void);
		Ray getRay(double x, double y);
		Canvas render(World& world);

		// Operators

		// Helpers
		void renderPartScreen(World& world, Canvas& canvas);
		static void setRenderThreads(int nThreads);
	};
}


