#pragma once

#include "tuple.h"
#include "material.h"
#include "matrix.h"
#include "point_light.h"

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
		Ray transform(Matrix const& m);
		void transformed(Matrix const& m);

	};

	Tuple getReflection(Tuple in, Tuple normal);
}