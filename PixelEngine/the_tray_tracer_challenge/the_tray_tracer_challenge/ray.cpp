#include "ray.h"

#include "DoubleHelpers.h"

using DoubleHelpers::isEqualDouble;

namespace RayTracer
{
	// ========================= Constructors ==========================
	Ray::Ray()
		:origin(point(0, 0, 0)), direction(vector(0, 0, 0))
	{
	}

	Ray::Ray(Tuple origin, Tuple direction)
		:origin(origin), direction(direction)
	{
	}


	// ============================ Methods ============================
	Tuple Ray::getPosition(double time)
	{
		return origin + (direction * time);
	}

	Ray Ray::transform(Matrix const& m)
	{
		return Ray(m * origin, m * direction);
	}

	// =========================== Operators ===========================


	// =========================== Helpers ===========================
	Tuple RayTracer::getReflection(Tuple in, Tuple normal)
	{
		return in - normal * 2 * in.dotProduct(normal);
	}

}

