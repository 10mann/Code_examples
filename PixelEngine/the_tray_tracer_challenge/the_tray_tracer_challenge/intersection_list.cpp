#include "intersection_list.h"

#include <algorithm>
#include <vector>

namespace RayTracer
{
	// ========================= Constructors ==========================
	IntersectionList::IntersectionList()
	{
	}

	IntersectionList::IntersectionList(Intersection intersection)
	{
		intersections.push_back(intersection);
	}

	IntersectionList::IntersectionList(Intersection intersection1, Intersection intersection2)
	{
		intersections.push_back(intersection1);
		intersections.push_back(intersection2);
	}

	// ============================ Methods ============================
	size_t IntersectionList::count(void)
	{
		return intersections.size();
	}

	Intersection IntersectionList::hit(void)
	{
		Intersection ret = Intersection::empty;

		double lowestValid = INT_MAX;

		for (int i = 0; i < intersections.size(); i++)
		{
			double t = intersections[i].i;
			if ((t > 0) && (t < lowestValid))
			{
				lowestValid = t;
				ret = intersections[i];
			}
		}

		return ret;
	}

	void IntersectionList::add(Intersection intersect)
	{
		intersections.push_back(intersect);
	}

	void IntersectionList::addList(IntersectionList intersect)
	{
		for (auto& in : intersect.intersections)
		{
			add(in);
		}
	}

	void IntersectionList::addIntersections(Ray& ray, Shape* shape)
	{
		Ray newRay = ray.transform(shape->invTransform);
		std::vector<double> intersectTimes = shape->getIntersectTime(newRay);

		for (auto& it : intersectTimes)
		{
			add(Intersection(it, shape));
		}
	}

	void IntersectionList::sort(void)
	{
		std::sort(intersections.begin(), intersections.end(), [](const Intersection& i1, const Intersection& i2) -> bool { return (i1.i < i2.i); });
	}


	// =========================== Operators ===========================
	const Intersection& IntersectionList::operator[](int n)
	{
		return intersections[n];
	}
}