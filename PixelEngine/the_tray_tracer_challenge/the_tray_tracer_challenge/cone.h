#pragma once

#include "shape.h"

namespace RayTracer
{
	class Cone : public Shape
	{
	public:

		// Variables
		double minY;
		double maxY;
		bool closed;

		// Constructors
		Cone();

		// Methods
		//Tuple getNormal(Tuple point) override;
		Tuple getLocalNormal(Tuple point) override;
		//std::vector<double> getIntersectTime(Ray& ray) override;
		std::vector<ObjectHit> getIntersectTime(Ray& ray) override;
		//Color colorAt(Tuple point) override;

		// Operators
		bool operator== (Shape const& s1) override;

	};
}