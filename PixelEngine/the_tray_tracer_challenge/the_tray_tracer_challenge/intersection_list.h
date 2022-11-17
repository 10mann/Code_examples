#pragma once

#include "intersection.h"

#include <vector>


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

		// Operators
		const Intersection& operator[](int n);
	};
}