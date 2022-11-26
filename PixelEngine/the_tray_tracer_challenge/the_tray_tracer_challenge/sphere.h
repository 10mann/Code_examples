#pragma once


#include "tuple.h"
#include "shape.h"
#include "ray.h"

#include <vector>

namespace RayTracer
{
	class Sphere : public Shape
	{
	public:

		// Variables
		Tuple center;
		double radius;

		// Constructors
		Sphere();

		// Methods
		Tuple getNormal(Tuple point) override;
		std::vector<double> getIntersectTime(Ray& ray) override;

		// Operators
		friend bool operator== (Sphere const& t1, Sphere const& t2);
	};
}