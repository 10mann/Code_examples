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
		Pattern* pattern;

		// Constructors
		Material();

		// Methods
		const Color& getColor(Tuple point);

		// Operators
		friend bool operator== (Material const& t1, Material const& t2);
	};
}