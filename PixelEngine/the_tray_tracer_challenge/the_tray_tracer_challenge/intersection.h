#pragma once

#include "shape.h"
#include "ray.h"

namespace RayTracer
{
	struct ComputeValues
	{
		double i;
		Shape* object;
		Tuple point;
		Tuple eyeDir;
		Tuple normal;
		Tuple overPoint;
		Tuple underPoint;
		Tuple reflectVector;
		double n1;
		double n2;
		double nRatio;
		double cos_i;
		double cos_t;
		double sin2t;
		bool inside;
	};

	class Intersection
	{
	public:
		// Variables
		double i;
		Shape* object;

		static const Intersection empty;

		// Constructors
		Intersection();
		Intersection(double i, Shape* object);

		// Methods
		//ComputeValues getComputeValues(Ray& ray);

		// Operators
		bool operator==(const Intersection& intersect);
		bool operator!= (const Intersection & intersect);
		Intersection operator=(Intersection intersect);
	};
}