#pragma once

#include "pattern.h"

namespace RayTracer
{
	class RingPattern : public Pattern
	{
	public:

		// Variables


		// Constructors
		RingPattern();
		RingPattern(Color c1, Color c2);

		// Methods
		Color colorAt(Tuple point) override;
		void setTransform(Matrix m);

		// Operators

	};
}