#pragma once

#include "pattern.h"

namespace RayTracer
{
	class GradientPattern : public Pattern
	{
	public:

		// Variables


		// Constructors
		GradientPattern();
		GradientPattern(Color c1, Color c2);

		// Methods
		const Color colorAt(Tuple point);
		void setTransform(Matrix m);

		// Operators

	};
}