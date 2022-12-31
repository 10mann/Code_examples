#pragma once

#include "shape.h"

namespace RayTracer
{
	class TestShape : public Shape
	{
	public:

		// Variables
		bool intersected = false;

		// Constructors
		TestShape()
		{

		}

		// Methods
		Tuple getLocalNormal(Tuple point) override
		{
			return vector(0, 0, -1);
		}

		std::vector<Shape::ObjectHit> getIntersectTime(Ray& ray) override 
		{
			intersected = true;
			return std::vector<ObjectHit>();
		}

		Tuple getMinimumBound(void)
		{
			return Tuple();
		}

		Tuple getMaximumBound(void)
		{
			return Tuple();
		}

		BoundingBox getBoundingBox(void)
		{
			return BoundingBox(point(-1, -1, -1), point(1, 1, 1));
		}

		// Operators
		bool operator== (Shape const& s1)
		{
			return true;
		}
	};
}