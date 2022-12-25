#include "group.h"

#include <algorithm>
#include <iostream>

namespace RayTracer
{
	// ========================= Constructors ==========================
	Group::Group()
	{
	}

	// ============================ Methods ============================
	Tuple Group::getLocalNormal(Tuple point)
	{
		std::cout << "Calling getNormal on group object\n";
		return Tuple();
	}

	std::vector<Shape::ObjectHit> Group::getIntersectTime(Ray& ray)
	{
		std::vector<ObjectHit> intersectTimes;
		Ray transformedRay = ray.transform(invTransform);

		for (const auto s : objects)
		{
			std::vector<ObjectHit> shapeIntersectTimes = s->getIntersectTime(transformedRay);
			for (const auto t : shapeIntersectTimes)
			{
				intersectTimes.push_back(t);
			}
		}

		std::sort(intersectTimes.begin(), intersectTimes.end(), [](ObjectHit x, ObjectHit y) {return x.i < y.i; });
		return intersectTimes;
	}

	void Group::addChild(Shape* child)
	{
		objects.push_back(child);
		child->parent = this;
	}

	// =========================== Operators ===========================
	bool Group::operator==(Shape const& s1)
	{
		return false;
	}

	// ============================ Helpers =============================
}