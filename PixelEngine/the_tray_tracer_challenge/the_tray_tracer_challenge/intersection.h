#pragma once

#include "shape.h"
#include "sphere.h"


namespace RayTracer
{
	class Intersection
	{
	public:
		// Variables
		double i;
		Sphere object;

		static const Intersection empty;

		// Constructors
		Intersection();
		Intersection(double i, const Sphere object);

		// Methods

		// Operators
		bool operator==(const Intersection& intersect);
		Intersection operator=(Intersection intersect);
	};
}