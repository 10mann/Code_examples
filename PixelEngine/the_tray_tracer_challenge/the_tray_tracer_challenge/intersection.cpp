#include "intersection.h"


namespace RayTracer
{
	Intersection const Intersection::empty = Intersection(-1, nullptr);

	// ========================= Constructors ==========================
	Intersection::Intersection()
		: i(0), object(nullptr)
	{
	}

	Intersection::Intersection(double i, const Shape* object)
		: i(i), object(object)
	{
	}

	// ============================ Methods ============================


	// =========================== Operators ===========================
	bool Intersection::operator==(const Intersection& intersect)
	{
		return ((i == intersect.i) && (object == intersect.object));
	}
}