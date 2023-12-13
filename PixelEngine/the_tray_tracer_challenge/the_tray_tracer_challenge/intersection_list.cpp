#include "intersection_list.h"
#include "DoubleHelpers.h"

#include <algorithm>
#include <vector>
#include <iostream>

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

		for (const auto& i : intersections)
		{
			if ((i.i > 0) && (i.i < lowestValid))
			{
				lowestValid = i.i;
				ret = i;
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
		std::vector<Shape::ObjectHit> intersectTimes;
		shape->getIntersectTime(ray, intersectTimes);

		for (auto& it : intersectTimes)
		{
			intersections.emplace_back(Intersection(it.i, it.object));
		}
	}

	void IntersectionList::sort(void)
	{
		std::sort(intersections.begin(), intersections.end(), [](const Intersection& i1, const Intersection& i2) -> bool { return (i1.i < i2.i); });
	}

	ComputeValues IntersectionList::getComputeValues(Intersection intersect, Ray& ray)
	{
		ComputeValues computeValues;
		computeValues.i = intersect.i;
		computeValues.object = intersect.object;
		computeValues.point = ray.getPosition(computeValues.i);
		computeValues.eyeDir = -ray.direction;
		computeValues.normal = computeValues.object->getNormal(computeValues.point);
		computeValues.inside = (computeValues.normal.dotProduct(computeValues.eyeDir) < (DoubleHelpers::EPSILON_HALF));
		if (true == computeValues.inside)
		{
			computeValues.normal = -computeValues.normal;
		}
		computeValues.reflectVector = getReflection(ray.direction, computeValues.normal);
		computeValues.overPoint = computeValues.point + computeValues.normal * DoubleHelpers::EPSILON;
		computeValues.underPoint = computeValues.point - computeValues.normal * DoubleHelpers::EPSILON;

		int objects = intersections.size();
		for (int i = 0; i < objects; i++)
		{
			if (intersect == intersections[i])
			{
				if (containers.size() == 0)
				{
					computeValues.n1 = 1;
				}
				else
				{
					computeValues.n1 = containers[containers.size() - 1]->material.refractiveIndex;
				}
			}

			auto it = std::find(containers.begin(), containers.end(), (intersections[i].object));
			if(containers.end() != it)
			{
				containers.erase(it);
			}
			else
			{
				containers.emplace_back(intersections[i].object);
			}

			if (intersect == intersections[i])
			{
				if (containers.size() == 0)
				{
					computeValues.n2 = 1;
				}
				else
				{
					computeValues.n2 = containers[containers.size() - 1]->material.refractiveIndex;
				}
			}
		}

		computeValues.cos_i = computeValues.eyeDir.dotProduct(computeValues.normal);
		computeValues.nRatio = computeValues.n1 / computeValues.n2;
		computeValues.sin2t = (computeValues.nRatio * computeValues.nRatio) * (1 - (computeValues.cos_i * computeValues.cos_i));
		computeValues.cos_t = std::sqrt(1 - computeValues.sin2t);

		return computeValues;
	}


	// =========================== Operators ===========================
	const Intersection& IntersectionList::operator[](int n)
	{
		return intersections[n];
	}
}