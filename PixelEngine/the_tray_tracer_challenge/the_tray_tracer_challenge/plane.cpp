#include "plane.h"
#include "DoubleHelpers.h"


namespace RayTracer
{
	// ========================= Constructors ==========================


	// ============================ Methods ============================
	Plane::Plane()
	{
	}

	Tuple Plane::getNormal(Tuple point)
	{
		return invTransform * vector(0, 1, 0);
	}

	std::vector<double> Plane::getIntersectTime(Ray& ray)
	{
		std::vector<double> intersectTimes;
		if (std::abs(ray.direction.y) > DoubleHelpers::EPSILON)
		{
			intersectTimes.push_back(-ray.origin.y / ray.direction.y);
		}

		return intersectTimes;
	}

	// =========================== Operators ===========================




	// ============================ Helpers =============================
}