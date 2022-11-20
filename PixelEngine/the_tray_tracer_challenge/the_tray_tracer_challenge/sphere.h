#pragma once


#include "tuple.h"
#include "shape.h"
#include "matrix.h"
#include "material.h"

namespace RayTracer
{
	class Sphere : public Shape
	{
	public:

		// Variables
		Tuple center;
		double radius;
		Matrix transform;
		Material material;

		// Constructors
		Sphere();

		// Methods
		void setTransform(Matrix m);
		//Tuple getNormal(Tuple point);
		Tuple getNormal(Tuple point);

		// Operators
		friend bool operator== (Sphere const& t1, Sphere const& t2);
	};
}