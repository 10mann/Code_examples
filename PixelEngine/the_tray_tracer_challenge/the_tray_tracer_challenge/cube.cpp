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
	Tuple Cube::getLocalNormal(Tuple point)
	{
		Tuple normal = vector(point.x, 0, 0);

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

	std::vector<Shape::ObjectHit> Cube::getIntersectTime(Ray& ray)
	{
		std::vector<ObjectHit> intersectTimes;
		Ray transformedRay = ray.transform(invTransform);

		double xMin, yMin, zMin, xMax, yMax, zMax, temp, tMin, tMax;

		xMin = (-1 - transformedRay.origin.x) / transformedRay.direction.x;
		xMax = (1 - transformedRay.origin.x) / transformedRay.direction.x;

		if (xMin > xMax)
		{
			temp = xMin;
			xMin = xMax;
			xMax = temp;
		}

		yMin = (-1 - transformedRay.origin.y) / transformedRay.direction.y;
		yMax = (1 - transformedRay.origin.y) / transformedRay.direction.y;

		if (yMin > yMax)
		{
			temp = yMin;
			yMin = yMax;
			yMax = temp;
		}

		zMin = (-1 - transformedRay.origin.z) / transformedRay.direction.z;
		zMax = (1 - transformedRay.origin.z) / transformedRay.direction.z;

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
			ObjectHit objHit1(tMin, this);
			ObjectHit objHit2(tMax, this);
			intersectTimes.push_back(objHit1);
			intersectTimes.push_back(objHit2);
		}

		return intersectTimes;
	}

	// =========================== Operators ===========================
	bool Cube::operator==(Shape const& s1)
	{
		return (transform == s1.transform);
	}

	// ============================ Helpers =============================
}