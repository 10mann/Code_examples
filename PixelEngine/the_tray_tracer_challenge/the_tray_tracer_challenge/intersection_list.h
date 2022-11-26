#pragma once

#include <vector>

#include "intersection.h"
#include "ray.h"
#include "shape.h"

namespace RayTracer
{
	class IntersectionList
	{
	public:

		// Variables

		std::vector<Intersection> intersections;
		// Constructors
		IntersectionList();
		IntersectionList(Intersection intersection);
		IntersectionList(Intersection intersection1, Intersection intersection2);
		// Methods
		size_t count(void);
		Intersection hit(void);
		void add(Intersection intersect);
		void addList(IntersectionList intersect);
		void addIntersections(Ray& ray, Shape* shape);
		void sort(void);

		// Operators
		const Intersection& operator[](int n);
	};
}