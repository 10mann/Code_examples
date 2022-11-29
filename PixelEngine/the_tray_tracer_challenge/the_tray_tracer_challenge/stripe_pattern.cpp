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
	const Color& StripePattern::colorAt(Tuple point)
	{
		return ((int)(std::floor((invTransform * point).x)) % 2) ? b : a;
	}

	//const Color& StripePattern::colorAtObject(Shape* object, Tuple point)
	//{
	//	return colorAt(object->invTransform * point);
	//}

	void StripePattern::setTransform(Matrix m)
	{
		transform = m;
		invTransform = m.getInverse();
	}

	// =========================== Operators ===========================


	// ============================ Helpers =============================
}