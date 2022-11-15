#include "DoubleHelpers.h"

namespace DoubleHelpers
{
	bool isEqualDouble(double a, double b)
	{
		{
			return (std::abs(a - b) < EPSILON);
		}
	}
}