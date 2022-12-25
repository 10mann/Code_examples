#pragma once

#include "color.h"
#include "pattern.h"

namespace RayTracer
{
	class Material
	{
	public:

		// Variables
		Color color;
		double ambient;
		double diffuse;
		double specular;
		double shininess;
		double reflective;
		double transparency;
		double refractiveIndex;
		Pattern* pattern;

		// Constructors
		Material();

		// Methods
		Color getColor(Tuple point);

		// Operators
		friend bool operator== (Material const& t1, Material const& t2);
	};
}