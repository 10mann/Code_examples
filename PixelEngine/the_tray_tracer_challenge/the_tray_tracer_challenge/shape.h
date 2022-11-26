#pragma once

#include "matrix.h"
#include "material.h"
#include "ray.h"

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

		virtual Tuple getNormal(Tuple point)
		{
			return point;
		}

		virtual std::vector<double> getIntersectTime(Ray& ray)
		{
			return std::vector<double>();
		}

		// Operators
		virtual bool operator==(Shape s)
		{
			return true;
		}
	};
}