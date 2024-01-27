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
	Color CheckerPattern::colorAt(Tuple point)
	{
		Tuple localPoint = point * invTransform;
		//int n = (int)std::floor(std::ceil(localPoint.x) + std::ceil(localPoint.y) + std::ceil(localPoint.z));
		int n = (int)std::floor(std::floor(localPoint.x + 0.001) + std::floor(localPoint.y + 0.001) + std::floor(localPoint.z + 0.001));
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