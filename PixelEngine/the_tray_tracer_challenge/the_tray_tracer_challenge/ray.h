#pragma once

#include "tuple.h"
#include "sphere.h"
#include "intersection_list.h"

#include <vector>

namespace RayTracer
{
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
		IntersectionList getIntersection(const Sphere* sphere);
		double getDiscriminant(Sphere sphere);
	};
}