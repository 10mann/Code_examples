#include "point_light.h"


namespace RayTracer
{
	// ========================= Constructors ==========================
	PointLight::PointLight()
		: intensity(Color(1, 1, 1)), position(point(0, 0, 0))
	{
	}

	PointLight::PointLight(Color intensity, Tuple position)
		: intensity(intensity), position(position)
	{
	}

	// ============================ Methods ============================


	// =========================== Operators ===========================
	bool RayTracer::operator==(PointLight const& l1, PointLight const& l2)
	{
		return ((l1.intensity == l2.intensity) && (l1.position == l2.position));
	}

}