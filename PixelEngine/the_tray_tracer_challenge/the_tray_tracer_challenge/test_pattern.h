#pragma once

#include "pattern.h"

namespace RayTracer
{
	class TestPattern : public Pattern
	{
	public:

		// Variables


		// Constructors


		// Methods
		void setTransform(Matrix m)
		{

		}

		Color colorAt(Tuple point)
		{
			return Color(point.x, point.y, point.z);
		}

		// Operators

	};
}