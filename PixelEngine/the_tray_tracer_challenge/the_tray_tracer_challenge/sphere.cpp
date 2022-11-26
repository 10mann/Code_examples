#include "sphere.h"
namespace RayTracer
{
	// ========================= Constructors ==========================
	Sphere::Sphere()
		: center(point(0, 0, 0)), radius(0.0)
	{

	}


	// ============================ Methods ============================
	//void Sphere::setTransform(Matrix m)
	//{
	//	transform = m;
	//	invTransform = m.getInverse();
	//}

	Tuple Sphere::getNormal(Tuple point)
	{
		Tuple worldNorm = invTransform.getTranspose() * ((invTransform * (point)) - center);
		worldNorm.w = 0;

		return worldNorm.getNormalized();
	}

	// =========================== Operators ===========================
	bool operator==(Sphere const& s1, Sphere const& s2)
	{
		return ((s1.center == s2.center) && 
			(s1.radius == s2.radius) && 
			(s1.transform == s2.transform) &&
			(s1.material == s2.material));
	}
}