#pragma once

#include "matrix.h"
#include "material.h"

namespace RayTracer
{
	class Shape
	{
	public:

		// Variables
		Matrix transform;
		Matrix invTransform;
		Material material;

		// Constructors
		Shape()
			: transform(Matrix::identityMatrix), invTransform(Matrix::identityMatrix)
		{

		}

		// Methods
		void setTransform(Matrix m)
		{
			transform = m;
			invTransform = m.getInverse();
		}

		// Operators

	};
}