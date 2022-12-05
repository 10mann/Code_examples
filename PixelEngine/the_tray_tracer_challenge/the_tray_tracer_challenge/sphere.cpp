#include "sphere.h"
#include "DoubleHelpers.h"

#include <cmath>

namespace RayTracer
{
	// ========================= Constructors ==========================
	Sphere::Sphere()
		: center(point(0, 0, 0)), radius(0.0)
	{
		transform = Matrix::identityMatrix;
		invTransform = Matrix::identityMatrix;
		material = Material();
	}


	// ============================ Methods ============================

	Tuple Sphere::getNormal(Tuple point)
	{
		Tuple worldNorm = invTransform.getTranspose() * ((invTransform * (point)) - center);
		worldNorm.w = 0;

		return worldNorm.getNormalized();
	}

	std::vector<double> RayTracer::Sphere::getIntersectTime(Ray& ray)
	{
		std::vector<double> intersectTimes;
		Tuple sphereVector = ray.origin - (point(0, 0, 0));
		double a = 2 * ray.direction.dotProduct(ray.direction);
		double b = 2 * ray.direction.dotProduct(sphereVector);
		double discriminant = (b * b) - (2 * a * (sphereVector.dotProduct(sphereVector) - 1.0));

		if (discriminant > (-DoubleHelpers::EPSILON))
		{
			intersectTimes.push_back((-1 * (b + std::sqrt(discriminant))) / (a));
			intersectTimes.push_back((std::sqrt(discriminant) - b) / (a));
		}
		return intersectTimes;
	}

	const Color& Sphere::colorAt(Tuple point)
	{
		return (material.pattern == nullptr) ? material.color : 
			material.pattern->colorAt(invTransform * point);
	}

	// =========================== Operators ===========================

	bool Sphere::operator==(Shape const& s1)
	{
		Sphere* s2 = (Sphere*)(&s1);

		return ((center == s2->center) &&
			(DoubleHelpers::isEqualDouble(radius, s2->radius))
			&& (transform == s2->transform));
	}

	Sphere glassSphere()
	{
		Sphere sphere;
		sphere.material.refractiveIndex = REFRACT_GLASS;
		sphere.material.transparency = 1;
		return sphere;
	}
}