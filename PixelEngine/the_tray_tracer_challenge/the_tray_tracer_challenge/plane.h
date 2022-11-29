#pragma once

#include "shape.h"

namespace RayTracer
{
	class Plane : public Shape
	{
	public:

		// Variables


		// Constructors
		Plane();

		// Methods
		Tuple getNormal(Tuple point) override;
		std::vector<double> getIntersectTime(Ray& ray) override;
		const Color& colorAt(Tuple point) override;
		// Operators
		bool operator== (Shape const& s1) override;
	};
}