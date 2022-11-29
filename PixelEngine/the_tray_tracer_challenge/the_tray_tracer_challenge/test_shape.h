#pragma once

#include "shape.h"

namespace RayTracer
{
	class TestShape : public Shape
	{
	public:

		// Variables


		// Constructors
		TestShape()
		{

		}

		// Methods
		Tuple getNormal(Tuple point) override
		{
			return vector(0, 0, -1);
		}

		std::vector<double> getIntersectTime(Ray& ray) override 
		{
			return std::vector<double>();
		}

		const Color& colorAt(Tuple point) override
		{
			return material.color;
		}

		// Operators
		bool operator== (Shape const& s1)
		{
			return true;
		}
	};
}