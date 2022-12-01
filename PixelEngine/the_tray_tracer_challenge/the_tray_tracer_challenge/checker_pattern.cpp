#include "checker_pattern.h"

#include <cmath>

namespace RayTracer
{
	// ========================= Constructors ==========================
	CheckerPattern::CheckerPattern()
	{
	}

	CheckerPattern::CheckerPattern(Color c1, Color c2)
	{
		a = c1;
		b = c2;
		transform = Matrix::identityMatrix;
		invTransform = Matrix::identityMatrix;
	}

	// ============================ Methods ============================
	const Color CheckerPattern::colorAt(Tuple point)
	{
		Tuple localPoint = invTransform * point;
		int n = std::floor(std::floor(localPoint.x) + std::floor(localPoint.y) + std::floor(localPoint.z));
		return ((n % 2) == 0) ? a : b;
	}

	void CheckerPattern::setTransform(Matrix m)
	{
		transform = m;
		invTransform = m.getInverse();
	}

	// =========================== Operators ===========================



	// ============================ Helpers =============================
}