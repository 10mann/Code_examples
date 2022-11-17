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

	IntersectionList Ray::getIntersection(const Sphere* sphere)
	{
		IntersectionList intersections;
		Tuple sphereVector = origin - sphere->center;
		double a = direction.dotProduct(direction);
		double b = 2 * direction.dotProduct(sphereVector);
		double c = sphereVector.dotProduct(sphereVector) - 1.0;
		double discriminant = (b * b) - (4 * a * c);
		double t0 = 0;
		double t1 = 0;
		if (discriminant > (-DoubleHelpers::EPSILON))
		{
			t0 = (-b - std::sqrt(discriminant)) / (2.0 * a);
			t1 = (-b + std::sqrt(discriminant)) / (2.0 * a);
			intersections = IntersectionList(Intersection(t0, sphere), Intersection(t1, sphere));
		}

		return intersections;
	}

	double Ray::getDiscriminant(Sphere sphere)
	{
		Tuple sphereVector = origin - sphere.center;
		double a = direction.dotProduct(direction);
		double b = 2 * direction.dotProduct(sphereVector);
		double c = sphereVector.dotProduct(sphereVector) - 1;
		return (b * b) - (4 * a * c);
	}



	// =========================== Operators ===========================
}

