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
	Tuple Sphere::getLocalNormal(Tuple point)
	{
		Tuple worldNorm = (((point)) - center).getNormalized();

		return worldNorm;
	}

	std::vector<Shape::ObjectHit> RayTracer::Sphere::getIntersectTime(Ray& ray)
	{
		std::vector<ObjectHit> intersectTimes;
		//Ray transformedRay = ray.transform(invTransform);

		//Tuple sphereVector = transformedRay.origin - (point(0, 0, 0));
		ray.transformed(invTransform);
		//Tuple sphereVector = transformedRay.origin - (point(0, 0, 0));
		//double a = 2 * transformedRay.direction.dotProduct(transformedRay.direction);
		//double a = 2 * transformedRay.direction.dotProduct(transformedRay.direction);
		//double b = 2 * transformedRay.direction.dotProduct(sphereVector);
		//double discriminant = (b * b) - (2 * a * (sphereVector.dotProduct(sphereVector) - 1.0));

/*		Tuple sphereVector = ray.origin - (point(0, 0, 0));
		double a = 2 * ray.direction.dotProduct(ray.direction);
		double b = 2 * ray.direction.dotProduct(sphereVector);
		double discriminant = (b * b) - (2 * a * (sphereVector.dotProduct(sphereVector) - 1.0));	*/	
		
		double a = 2 * ray.direction.dotProduct(ray.direction);
		double b = 2 * ray.direction.dotProduct(ray.origin);
		double discriminant = (b * b) - (2 * a * (ray.origin.dotProduct(ray.origin) - 1.0));

		if (discriminant > (-DoubleHelpers::EPSILON))
		{
			ObjectHit objHit1((-1 * (b + std::sqrt(discriminant))) / (a), this);
			ObjectHit objHit2((std::sqrt(discriminant) - b) / (a), this);
			intersectTimes.push_back(objHit1);
			intersectTimes.push_back(objHit2);
		}
		return intersectTimes;
	}

	void RayTracer::Sphere::getIntersectTime(Ray& ray, std::vector<Shape::ObjectHit>& intersectTimes)
	{
		Ray transformedRay = ray.transform(invTransform);

		Tuple sphereVector = transformedRay.origin - (point(0, 0, 0));
		double a = 2 * transformedRay.direction.dotProduct(transformedRay.direction);
		double b = 2 * transformedRay.direction.dotProduct(sphereVector);
		double discriminant = (b * b) - (2 * a * (sphereVector.dotProduct(sphereVector) - 1.0));

		//ray.transformed(invTransform);
		//double a = 2 * ray.direction.dotProduct(ray.direction);
		//double b = 2 * ray.direction.dotProduct(ray.origin);
		//double discriminant = (b * b) - (2 * a * (ray.origin.dotProduct(ray.origin) - 1.0));

		//Tuple sphereVector = ray.origin - (point(0, 0, 0));
		//double a = 2 * ray.direction.dotProduct(ray.direction);
		//double b = 2 * ray.direction.dotProduct(sphereVector);
		//double discriminant = (b * b) - (2 * a * (sphereVector.dotProduct(sphereVector) - 1.0));

		if (discriminant > (-DoubleHelpers::EPSILON))
		{
			ObjectHit objHit1((-1 * (b + std::sqrt(discriminant))) / (a), this);
			ObjectHit objHit2((std::sqrt(discriminant) - b) / (a), this);
			intersectTimes.push_back(objHit1);
			intersectTimes.push_back(objHit2);
		}
	}

	void Sphere::getIntersections(Ray ray, std::vector<Shape::ObjectHit>& intersectTimes)
	{
		ray.transformed(invTransform);
		ray.origin.w = 0;
		double a = 2 * ray.direction.dotProduct(ray.direction);
		double b = 2 * ray.direction.dotProduct(ray.origin);
		double discriminant = (b * b) - (2 * a * (ray.origin.dotProduct(ray.origin) - 1.0));

		if (discriminant > 0)
		{
			double sqr = std::sqrt(discriminant);
			intersectTimes.emplace_back(ObjectHit((-1 * (b + sqr)) / (a), this));
			intersectTimes.emplace_back(ObjectHit((sqr - b) / (a), this));
		}
	}

	BoundingBox Sphere::getBoundingBox(void)
	{
		BoundingBox mBbox(point(-1, -1, -1), point(1, 1, 1));
		mBbox.setTransform(transform);

		return mBbox;
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