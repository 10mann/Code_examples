#pragma once


#include "tuple.h"
#include "shape.h"


namespace RayTracer
{
	class Sphere : public Shape
	{
	public:

		// Variables
		Tuple center;
		double radius;

		// Constructors
		Sphere();

		// Methods
		//void setTransform(Matrix m);
		//Tuple getNormal(Tuple point);
		Tuple getNormal(Tuple point);

		// Operators
		friend bool operator== (Sphere const& t1, Sphere const& t2);
	};
}