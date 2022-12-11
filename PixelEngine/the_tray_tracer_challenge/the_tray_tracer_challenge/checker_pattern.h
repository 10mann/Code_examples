#pragma once

#include "pattern.h"

namespace RayTracer
{
	class CheckerPattern : public Pattern
	{
	public:

		// Variables


		// Constructors
		CheckerPattern();
		CheckerPattern(Color c1, Color c2);

		// Methods
		Color colorAt(Tuple point) override;
		void setTransform(Matrix m);

		// Operators

	};
}