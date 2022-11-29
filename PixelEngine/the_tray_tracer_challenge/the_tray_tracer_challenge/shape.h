#pragma once

#include "matrix.h"
#include "material.h"
#include "ray.h"
#include "pattern.h"

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
			: transform(Matrix::identityMatrix), invTransform(Matrix::identityMatrix), material(Material())
		{

		}

		// Methods
		void setTransform(Matrix m)
		{
			transform = m;
			invTransform = m.getInverse();
		}

		virtual Tuple getNormal(Tuple point) = 0;

		virtual std::vector<double> getIntersectTime(Ray& ray) = 0;

		virtual const Color& colorAt(Tuple point) = 0;

		// Operators
		//virtual bool operator==(Shape s) = 0;

		virtual bool operator== (Shape const& s1) = 0;
	};
}