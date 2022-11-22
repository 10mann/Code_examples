#include "camera.h"
#include "DoubleHelpers.h"

#include <cmath>


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
		double xOffset = (x + 0.5) * pixelSize;
		double yOffset = (y + 0.5) * pixelSize;

		double worldX = halfViewX - xOffset;
		double worldY = halfViewY - yOffset;

		Tuple pixel = transform.getInverse() * point(worldX, worldY, -1);
		Tuple origin = transform.getInverse() * point(0, 0, 0);
		Tuple direction = (pixel - origin).getNormalized();

		return Ray(origin, direction);
	}

	Canvas Camera::render(World& world)
	{
		Canvas image(width, height);

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				Ray ray = getRay(x, y);
				Color color = world.getColor(ray);
				image.writePixel(x, y, color);
			}
		}
		return image;
	}

	// =========================== Operators ===========================

	

	// ============================ Helpers =============================
}