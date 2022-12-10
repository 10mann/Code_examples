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

		for (int i = 0; i < this->count(); i++)
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

			bool exists = false;
			for (int j = 0; j < containers.size(); j++)
			{
				if (intersections[i].object == containers[j])
				{
					exists = true;
					containers.erase(containers.begin() + j);
					break;
				}
			}
			if (false == exists)
			{
				containers.push_back(intersections[i].object);
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

		return computeValues;
	}


	// =========================== Operators ===========================
	const Intersection& IntersectionList::operator[](int n)
	{
		return intersections[n];
	}
}