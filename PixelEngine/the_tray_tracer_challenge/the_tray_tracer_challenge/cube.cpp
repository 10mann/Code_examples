#include "cube.h"
#include "DoubleHelpers.h"

#include <limits>

namespace RayTracer
{
	// ========================= Constructors ==========================
	Cube::Cube()
	{
		transform = Matrix::identityMatrix;
		invTransform = Matrix::identityMatrix;
		material = Material();
	}

	// ============================ Methods ============================
	Tuple Cube::getNormal(Tuple point)
	{
		Tuple normal = vector(point.x, 0 ,0);

		double maxVal = std::abs(point.x);
		if (std::abs(point.y) > maxVal)
		{
			maxVal = std::abs(point.y);
			normal = vector(0, point.y, 0);
		}

		if (std::abs(point.z) > maxVal)
		{
			maxVal = std::abs(point.z);
			normal = vector(0, 0, point.z);
		}

		return normal;
	}

	std::vector<double> Cube::getIntersectTime(Ray& ray)
	{
		std::vector<double> intersectTimes;

		double xMin, yMin, zMin, xMax, yMax, zMax, temp, tMin, tMax;

		xMin = (-1 - ray.origin.x) / ray.direction.x;
		xMax = (1 - ray.origin.x) / ray.direction.x;

		if (xMin > xMax)
		{
			temp = xMin;
			xMin = xMax;
			xMax = temp;
		}

		yMin = (-1 - ray.origin.y) / ray.direction.y;
		yMax = (1 - ray.origin.y) / ray.direction.y;

		if (yMin > yMax)
		{
			temp = yMin;
			yMin = yMax;
			yMax = temp;
		}

		zMin = (-1 - ray.origin.z) / ray.direction.z;
		zMax = (1 - ray.origin.z) / ray.direction.z;

		if (zMin > zMax)
		{
			temp = zMin;
			zMin = zMax;
			zMax = temp;
		}

		temp = (xMin > yMin) ? xMin : yMin;
		tMin = (zMin > temp) ? zMin : temp;
		

		temp = (xMax < yMax) ? xMax : yMax;
		tMax = (zMax < temp) ? zMax : temp;
		if (tMax > tMin)
		{
			intersectTimes.push_back(tMin);
			intersectTimes.push_back(tMax);
		}

		return intersectTimes;
	}

	const Color& Cube::colorAt(Tuple point)
	{
		// TODO: insert return statement here
		return Color();
	}

	// =========================== Operators ===========================


	bool Cube::operator==(Shape const& s1)
	{
		return (transform == s1.transform);
	}

	// ============================ Helpers =============================
}