#pragma once

#include "shape.h"

namespace RayTracer
{
	class BoundingBox : Shape
	{
	public:

		// Variables
		Tuple min;
		Tuple max;

		// Constructors
		BoundingBox();

		// Methods
		Tuple getLocalNormal(Tuple point);
		std::vector<ObjectHit> getIntersectTime(Ray& ray);

		// Operators

	};
}