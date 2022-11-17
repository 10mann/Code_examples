#include "intersection_list.h"

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


	// =========================== Operators ===========================
	const Intersection& IntersectionList::operator[](int n)
	{
		return intersections[n];
	}
}