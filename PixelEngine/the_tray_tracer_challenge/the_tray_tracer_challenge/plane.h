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
		//Tuple getNormal(Tuple point) override;
		Tuple getLocalNormal(Tuple point) override;
		std::vector<ObjectHit> getIntersectTime(Ray& ray) override;
		//Color colorAt(Tuple point) override;
		// Operators
		bool operator== (Shape const& s1) override;
	};
}