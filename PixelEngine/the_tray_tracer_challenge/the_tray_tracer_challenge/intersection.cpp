#include "intersection.h"


namespace RayTracer
{
	//Intersection const Intersection::empty = Intersection(-1, nullptr);
	Intersection const Intersection::empty = Intersection(-1, Sphere());

	// ========================= Constructors ==========================
	Intersection::Intersection()
		: i(0), object(Sphere())
	{
	}

	Intersection::Intersection(double i, const Sphere object)
		: i(i), object(object)
	{
	}

	// ============================ Methods ============================


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