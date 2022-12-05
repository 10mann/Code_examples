#include "intersection.h"

#include "DoubleHelpers.h"

namespace RayTracer
{
	Intersection const Intersection::empty = Intersection(-1, nullptr);

	// ========================= Constructors ==========================
	Intersection::Intersection()
		: i(0), object(nullptr)
	{
	}

	Intersection::Intersection(double i, Shape* object)
		: i(i), object(object)
	{
	}

	// ============================ Methods ============================

	//ComputeValues Intersection::getComputeValues(Ray& ray)
	//{
	//	ComputeValues computeValues;
	//	computeValues.i = i;
	//	computeValues.object = object;
	//	computeValues.point = ray.getPosition(computeValues.i);
	//	computeValues.eyeDir = -ray.direction;
	//	computeValues.normal = computeValues.object->getNormal(computeValues.point);
	//	computeValues.inside = (computeValues.normal.dotProduct(computeValues.eyeDir) < 0);
	//	if (true == computeValues.inside)
	//	{
	//		computeValues.normal = -computeValues.normal;
	//	}
	//	computeValues.reflectVector = getReflection(ray.direction, computeValues.normal);
	//	computeValues.overPoint = computeValues.point + computeValues.normal * DoubleHelpers::EPSILON;
	//	return computeValues;
	//}

	// =========================== Operators ===========================
	bool Intersection::operator==(const Intersection& intersect)
	{
		return ((i == intersect.i) && (object == intersect.object));
	}

	bool Intersection::operator!=(const Intersection& intersect)
	{
		return !((i == intersect.i) && (object == intersect.object));
	}

	Intersection Intersection::operator=(Intersection intersect)
	{
		i = intersect.i;
		object = intersect.object;
		return *this;
	}
}