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
		//Tuple getNormal(Tuple point) override;
		Tuple getLocalNormal(Tuple point) override;
		std::vector<ObjectHit> getIntersectTime(Ray& ray) override;
		//Color colorAt(Tuple point) override;

		// Operators
		bool operator== (Shape const& s1) override;
	};

	Sphere glassSphere();
}