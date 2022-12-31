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
		Tuple getLocalNormal(Tuple point) override;
		std::vector<ObjectHit> getIntersectTime(Ray& ray) override;
		BoundingBox getBoundingBox(void) override;

		// Operators
		bool operator== (Shape const& s1) override;
	};

	Sphere glassSphere();
}