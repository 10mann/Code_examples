#pragma once

#include "pattern.h"

namespace RayTracer
{
	class StripePattern : public Pattern
	{
	public:

		// Variables


		// Constructors
		StripePattern();
		StripePattern(Color c1, Color c2);

		// Methods
		Color colorAt(Tuple point) override;
		//const Color& colorAtObject(Shape* object, Tuple point);
		void setTransform(Matrix m);

		// Operators

	};
}