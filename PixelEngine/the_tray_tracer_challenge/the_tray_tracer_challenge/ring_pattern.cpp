#include "ring_pattern.h"

#include <cmath>

namespace RayTracer
{
	// ========================= Constructors ==========================
	RingPattern::RingPattern()
	{
	}

	RingPattern::RingPattern(Color c1, Color c2)
	{
		a = c1;
		b = c2;
		transform = Matrix::identityMatrix;
		invTransform = Matrix::identityMatrix;
	}

	// ============================ Methods ============================
	Color RingPattern::colorAt(Tuple point)
	{
		Tuple localPoint = invTransform * point;
		double n = std::sqrt((localPoint.x * localPoint.x) + (localPoint.z * localPoint.z));
		return (((int)std::floor(n) % 2) == 0 ? a : b);
	}

	void RingPattern::setTransform(Matrix m)
	{
		transform = m;
		invTransform = m.getInverse();
	}

	// =========================== Operators ===========================


	// ============================ Helpers =============================
}