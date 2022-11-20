#include "sphere.h"
namespace RayTracer
{
	// ========================= Constructors ==========================
	Sphere::Sphere()
		: center(point(0, 0, 0)), radius(0.0), transform(Matrix::identityMatrix)
	{
	}


	// ============================ Methods ============================
	void Sphere::setTransform(Matrix m)
	{
		transform = m;
	}

	//Tuple Sphere::getNormal(Tuple point)
	//{
	//	Tuple worldPoint = transform.getInverse() * point;
	//	Tuple objNorm = worldPoint - center;
	//	Tuple worldNorm = transform.getInverse().getTranspose() * objNorm;
	//	worldNorm.w = 0;
	//	worldNorm.normalize();

	//	return worldNorm;
	//}

	Tuple Sphere::getNormal(Tuple point)
	{
		Tuple worldPoint = transform.getInverse() * (point);
		//Tuple objNorm = ;
		Tuple worldNorm = transform.getInverse().getTranspose() * (worldPoint - center);
		worldNorm.w = 0;
		worldNorm.normalize();

		return worldNorm;
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