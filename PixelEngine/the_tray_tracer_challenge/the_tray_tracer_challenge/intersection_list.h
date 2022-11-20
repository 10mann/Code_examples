#pragma once

#include <vector>

#include "intersection.h"

namespace RayTracer
{
	class IntersectionList
	{
	public:

		// Variables
		//std::vector<Intersection> intersections;

		std::vector<Intersection> intersections;
		// Constructors
		IntersectionList();
		IntersectionList(Intersection intersection);
		IntersectionList(Intersection intersection1, Intersection intersection2);
		// Methods
		size_t count(void);
		Intersection hit(void);
		void add(Intersection& intersect);
		void addList(IntersectionList& intersect);
		void sort(void);

		// Operators
		const Intersection& operator[](int n);
	};
}