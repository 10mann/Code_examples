#pragma once

#include "matrix.h"
#include "ray.h"
#include "canvas.h"
#include "world.h"

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

		// Constructors
		Camera();
		Camera(int width, int height, double fieldOfView);

		// Methods
		void calculateInverseTransform(void);
		Ray getRay(double x, double y);
		Canvas render(World& world);

		// Operators

		// Helpers
		void renderPartScreen(World& world, Canvas& canvas, int startX, int startY, int width, int height);
		static void setRenderThreads(int nThreads);
	};
}


