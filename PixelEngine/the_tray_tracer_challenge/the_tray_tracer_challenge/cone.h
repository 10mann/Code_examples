#pragma once

#include "shape.h"

namespace RayTracer
{
	class Cone : public Shape
	{
	public:

		// Variables
		double minY;
		double maxY;
		bool closed;

		// Constructors
		Cone();

		// Methods
		Tuple getLocalNormal(Tuple point) override;
		std::vector<ObjectHit> getIntersectTime(Ray& ray) override;
		void getIntersectTime(Ray& ray, std::vector<Shape::ObjectHit>& intersectTimes) override;
		void getIntersections(Ray ray, std::vector<Shape::ObjectHit>& intersectTimes) override;
		BoundingBox getBoundingBox(void) override;

		// Operators
		bool operator== (Shape const& s1) override;

	};
}