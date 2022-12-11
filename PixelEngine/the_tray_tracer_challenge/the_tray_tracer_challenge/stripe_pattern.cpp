#include "stripe_pattern.h"

#include <cmath>

namespace RayTracer
{
	// ========================= Constructors ==========================


	StripePattern::StripePattern()
	{
	}

	StripePattern::StripePattern(Color c1, Color c2)
	{
		a = c1;
		b = c2;
		transform = Matrix::identityMatrix;
		invTransform = Matrix::identityMatrix;
	}

	// ============================ Methods ============================
	Color StripePattern::colorAt(Tuple point)
	{
		return ((int)(std::floor((invTransform * point).x)) % 2) ? b : a;
	}

	void StripePattern::setTransform(Matrix m)
	{
		transform = m;
		invTransform = m.getInverse();
	}

	// =========================== Operators ===========================


	// ============================ Helpers =============================
}