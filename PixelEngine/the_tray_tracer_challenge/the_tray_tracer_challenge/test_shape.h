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
		Tuple getLocalNormal(Tuple point) override
		{
			return vector(0, 0, -1);
		}

		std::vector<Shape::ObjectHit> getIntersectTime(Ray& ray) override 
		{
			return std::vector<ObjectHit>();
		}

		//Color colorAt(Tuple point) override
		//{
		//	return material.color;
		//}

		// Operators
		bool operator== (Shape const& s1)
		{
			return true;
		}
	};
}