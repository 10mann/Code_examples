#include "material.h"

#include "DoubleHelpers.h"

using DoubleHelpers::isEqualDouble;

namespace RayTracer
{
	// ========================= Constructors ==========================
	Material::Material()
		: color(Color(1, 1, 1)), 
		ambient(0.1), 
		diffuse(0.9), 
		specular(0.9), 
		shininess(200),
		reflective(0),
		transparency(0),
		refractiveIndex(1),
		pattern(nullptr)
	{
	}

	Color Material::getColor(Tuple point)
	{
		return (pattern == nullptr) ? color : pattern->colorAt(point);
	}

	// ============================ Methods ============================


	// =========================== Operators ===========================
	bool operator==(Material const& m1, Material const& m2)
	{
		return ((m1.color == m2.color) && 
			(isEqualDouble(m1.ambient, m2.ambient)) &&
			(isEqualDouble(m1.diffuse, m2.diffuse)) &&
			(isEqualDouble(m1.specular, m2.specular)) &&
			(isEqualDouble(m1.shininess, m2.shininess)));
	}
}