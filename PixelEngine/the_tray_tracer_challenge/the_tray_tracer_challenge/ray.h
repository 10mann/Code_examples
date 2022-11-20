#pragma once

#include "tuple.h"
#include "sphere.h"
#include "intersection_list.h"
#include "matrix.h"
#include "point_light.h"

#include <vector>

namespace RayTracer
{
	struct ComputeValues
	{
		double i;
		Sphere object;
		Tuple point;
		Tuple eyeDir;
		Tuple normal;
		bool inside;
	};


	class Ray
	{
	public:

		// Variables
		Tuple origin;
		Tuple direction;

		// Constructors
		Ray();
		Ray(Tuple origin, Tuple direction);

		// Method
		Tuple getPosition(double time);
		IntersectionList getIntersection(Sphere sphere);
		double getDiscriminant(Sphere const& sphere);
		Ray transform(Matrix const& m);
		ComputeValues getComputeValues(Intersection& intersect);


	};

	Tuple getReflection(Tuple in, Tuple normal);
	Color getLighting(Material m, PointLight light, Tuple position, Tuple eyeDirection, Tuple normal);
}