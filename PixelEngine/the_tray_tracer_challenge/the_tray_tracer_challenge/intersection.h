#pragma once

#include "shape.h"


namespace RayTracer
{
	class Intersection
	{
	public:
		// Variables
		double i;
		const Shape* object;

		static const Intersection empty;

		// Constructors
		Intersection();
		Intersection(double i, const Shape* object);

		// Methods


		// Operators
		bool operator==(const Intersection& intersect);
	};
}