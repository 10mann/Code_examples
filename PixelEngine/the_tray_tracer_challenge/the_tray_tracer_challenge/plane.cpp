#include "plane.h"
#include "DoubleHelpers.h"


namespace RayTracer
{
	// ========================= Constructors ==========================
	Plane::Plane()
	{
	}

	// ============================ Methods ============================
	Tuple Plane::getLocalNormal(Tuple point)
	{
		return vector(0, 1, 0);
	}

	std::vector<Shape::ObjectHit> Plane::getIntersectTime(Ray& ray)
	{
		std::vector<ObjectHit> intersectTimes;
		Ray transformedRay = ray.transform(invTransform);

		if (std::abs(ray.direction.y) > DoubleHelpers::EPSILON)
		{
			ObjectHit objHit(-transformedRay.origin.y / transformedRay.direction.y, this);
			intersectTimes.push_back(objHit);
		}

		return intersectTimes;
	}

	void Plane::getIntersectTime(Ray& ray, std::vector<Shape::ObjectHit>& intersectTimes)
	{
		Ray transformedRay = ray.transform(invTransform);

		if (std::abs(ray.direction.y) > DoubleHelpers::EPSILON)
		{
			ObjectHit objHit(-transformedRay.origin.y / transformedRay.direction.y, this);
			intersectTimes.push_back(objHit);
		}
	}

	BoundingBox Plane::getBoundingBox(void)
	{
		BoundingBox mBbox = BoundingBox(point(-INFINITY, 0, -INFINITY), point(INFINITY, 0, INFINITY));
		mBbox.setTransform(transform);
		
		return mBbox;
	}


	// =========================== Operators ===========================
	bool Plane::operator==(Shape const& s1)
	{
		return false;
	}


	// ============================ Helpers =============================
}