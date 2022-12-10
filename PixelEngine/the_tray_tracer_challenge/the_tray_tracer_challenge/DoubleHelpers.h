#pragma once

#include <cmath>

namespace DoubleHelpers
{
	constexpr double EPSILON =      1e-5;
	constexpr double EPSILON_HALF = EPSILON / 2.0;
	constexpr double MATH_PI =      3.141592653589;

	bool isEqualDouble(double a, double b);
}