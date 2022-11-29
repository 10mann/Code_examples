#pragma once

#include "color.h"
#include "tuple.h"
//#include "shape.h"
#include "matrix.h"

namespace RayTracer
{
	class Pattern
	{
	public:

		// Variables
		Color a;
		Color b;
		Matrix transform;
		Matrix invTransform;

		// Constructors
		Pattern()
			: a(Color::White), b(Color::Black), transform(Matrix::identityMatrix), invTransform(Matrix::identityMatrix)
		{

		}
		Pattern(Color c1, Color c2)
			: a(c1), b(c2), transform(Matrix::identityMatrix), invTransform(Matrix::identityMatrix)
		{

		}

		// Methods
		virtual const Color& colorAt(Tuple point) = 0;
		//virtual const Color& colorAtObject(Shape* object, Tuple point) = 0;
		virtual void setTransform(Matrix m) = 0;

		// Operators

	};
}