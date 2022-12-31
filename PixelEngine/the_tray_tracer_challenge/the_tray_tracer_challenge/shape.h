#pragma once

#include "matrix.h"
#include "material.h"
#include "ray.h"
#include "pattern.h"
#include "raytracer_config.h"
#include "bounding_box.h"

namespace RayTracer
{
	class Shape
	{
	public:
		class ObjectHit
		{
		public:
			Shape* object;
			double i;

			ObjectHit(double _i, Shape* s)
			{
				i = _i;
				object = s;
			}
		};

		// Variables
		Matrix transform;
		Matrix invTransform;
		Matrix invTranspose;
		Material material;

		Shape* parent;

		// Constructors
		Shape()
			: transform(Matrix::identityMatrix), 
			invTransform(Matrix::identityMatrix), 
			invTranspose(Matrix::identityMatrix),
			material(Material()),
			parent(nullptr)
		{

		}

		// Methods
		void setTransform(Matrix m)
		{
			transform = m;
			invTransform = m.getInverse();
			invTranspose = invTransform.getTranspose();
		}

		Tuple getNormal(Tuple point)
		{
			Tuple LocalPoint = worldToObjectSpace(point);
			Tuple localNormal = this->getLocalNormal(LocalPoint);
			return normalToWorld(localNormal);
		}

		virtual Tuple getLocalNormal(Tuple point) = 0;
		virtual std::vector<ObjectHit> getIntersectTime(Ray& ray) = 0;

		Color colorAt(Tuple point)
		{
			return (material.pattern == nullptr) ? material.color :
				material.pattern->colorAt(worldToObjectSpace(point));
		}

		Tuple worldToObjectSpace(Tuple p)
		{
			if (nullptr != parent)
			{
				p = parent->worldToObjectSpace(p);
			}

			return invTransform * p;
		}

		Tuple normalToWorld(Tuple n)
		{
			Tuple normal = invTranspose * n;
			normal.w = 0;
			normal = normal.getNormalized();

			if (nullptr != parent)
			{
				normal = parent->normalToWorld(normal);
			}

			return normal;
		}

		virtual BoundingBox getBoundingBox(void) = 0;

		virtual void divide(int threshold)
		{
			(void)threshold;
		}

		// Operators
		virtual bool operator== (Shape const& s1) = 0;
	};
}