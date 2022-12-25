#include "bounding_box.h"


namespace RayTracer
{
	// ========================= Constructors ==========================


	// ============================ Methods ============================


	// =========================== Operators ===========================


	BoundingBox::BoundingBox()
		: min(point(0, 0, 0)), max(point(0, 0, 0))
	{
	}

	Tuple BoundingBox::getLocalNormal(Tuple point)
	{
		return vector(0, 1, 0);
	}

	std::vector<Shape::ObjectHit> BoundingBox::getIntersectTime(Ray& ray)
	{
		std::vector<ObjectHit> intersectTimes;
		Ray transformedRay = ray.transform(invTransform);

		double xMin, yMin, zMin, xMax, yMax, zMax, temp, tMin, tMax;

		xMin = (min.x - transformedRay.origin.x) / transformedRay.direction.x;
		xMax = (max.x - transformedRay.origin.x) / transformedRay.direction.x;

		if (xMin > xMax)
		{
			temp = xMin;
			xMin = xMax;
			xMax = temp;
		}

		yMin = (min.y - transformedRay.origin.y) / transformedRay.direction.y;
		yMax = (max.y - transformedRay.origin.y) / transformedRay.direction.y;

		if (yMin > yMax)
		{
			temp = yMin;
			yMin = yMax;
			yMax = temp;
		}

		zMin = (min.z - transformedRay.origin.z) / transformedRay.direction.z;
		zMax = (max.z - transformedRay.origin.z) / transformedRay.direction.z;

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

	// ============================ Helpers =============================
}