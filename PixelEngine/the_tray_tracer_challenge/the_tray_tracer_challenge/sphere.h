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
		const Color& colorAt(Tuple point) override;

		// Operators
		friend bool operator== (Sphere const& t1, Sphere const& t2);
		bool operator== (Shape const& s1) override;
		//friend bool operator== (Sphere t1, Sphere t2);
	};
}