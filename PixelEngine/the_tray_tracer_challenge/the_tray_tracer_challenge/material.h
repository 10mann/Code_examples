#pragma once

#include "color.h"

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

		// Constructors
		Material();

		// Methods


		// Operators
		friend bool operator== (Material const& t1, Material const& t2);
	};
}