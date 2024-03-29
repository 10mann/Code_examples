#include "gradient_pattern.h"

#include <cmath>

namespace RayTracer
{
	// ========================= Constructors ==========================
	GradientPattern::GradientPattern()
	{
	}

	GradientPattern::GradientPattern(Color c1, Color c2)
	{
		a = c1;
		b = c2;
		transform = Matrix::identityMatrix;
		invTransform = Matrix::identityMatrix;
	}

	// ============================ Methods ============================
	Color GradientPattern::colorAt(Tuple point)
	{
		Tuple localPoint = point * invTransform;
		double frac = localPoint.x - std::floor(localPoint.x);
		Color dist = b - a;
		return a + dist * frac;
	}

	void GradientPattern::setTransform(Matrix m)
	{
		transform = m;
		invTransform = m.getInverse();
	}

	// =========================== Operators ===========================


	// ============================ Helpers =============================
}