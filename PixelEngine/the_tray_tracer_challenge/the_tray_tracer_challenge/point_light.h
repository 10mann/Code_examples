#pragma once

#include "tuple.h"
#include "color.h"

namespace RayTracer
{
	class PointLight
	{
	public:

		// Variables
		Color intensity;
		Tuple position;

		// Constructors
		PointLight();
		PointLight(Color intensity, Tuple position);

		// Methods


		// Operators
		friend bool operator== (PointLight const& l1, PointLight const& l2);
	};
}