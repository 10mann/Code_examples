#include "cylinder.h"
#include "DoubleHelpers.h"

#include <cmath>

namespace RayTracer
{
	// ========================= Constructors ==========================
	Cylinder::Cylinder()
		: minY(-INFINITY), maxY(INFINITY), closed(false)
	{
	}

	// ============================ Methods ============================
	Tuple Cylinder::getLocalNormal(Tuple point)
	{
		Tuple normal = vector(point.x, 0, point.z);

		double dist = (point.x * point.x) + (point.z * point.z);

		if (dist < 1)
		{
			if (point.y >= (maxY - DoubleHelpers::EPSILON))
			{
				normal = vector(0, 1, 0);
			}

			if (point.y <= (minY + DoubleHelpers::EPSILON))
			{
				normal = vector(0, -1, 0);
			}
		}

		return normal;
	}

	std::vector<Shape::ObjectHit> Cylinder::getIntersectTime(Ray& ray)
	{
		std::vector<ObjectHit> intersectTimes;
		Ray transformedRay = ray.transform(invTransform);

		double a = (transformedRay.direction.x * transformedRay.direction.x) + 
			(transformedRay.direction.z * transformedRay.direction.z);

		if (a > DoubleHelpers::EPSILON)
		{
			double b = 2 * (transformedRay.origin.x * transformedRay.direction.x +
				transformedRay.origin.z * transformedRay.direction.z);

			double c = (transformedRay.origin.x * transformedRay.origin.x) + 
				(transformedRay.origin.z * transformedRay.origin.z) - 1;

			double disc = ((b * b) - (4 * a * c));
			if (disc > -DoubleHelpers::EPSILON_HALF)
			{
				double discSqrt = std::sqrt(disc);
				double t0 = (-b - discSqrt) / (2 * a);
				double t1 = (discSqrt - b) / (2 * a);

				if (((transformedRay.origin.y + (t0 * transformedRay.direction.y) < maxY) &&
					((transformedRay.origin.y + (t0 * transformedRay.direction.y)) > minY)))
				{
					ObjectHit objHit(t0, this);
					intersectTimes.push_back(objHit);
				}
				
				if (((transformedRay.origin.y + (t1 * transformedRay.direction.y) < maxY) &&
					((transformedRay.origin.y + (t1 * transformedRay.direction.y)) > minY)))
				{
					ObjectHit objHit(t1, this);
					intersectTimes.push_back(objHit);
				}
			}
		}

		if ((intersectTimes.size() < 2) && closed && ((transformedRay.direction.y > DoubleHelpers::EPSILON_HALF) || (transformedRay.direction.y < (-DoubleHelpers::EPSILON_HALF))))
		{
			double t = (minY - transformedRay.origin.y) / transformedRay.direction.y;
			double x = transformedRay.origin.x + (t * transformedRay.direction.x);
			double z = transformedRay.origin.z + (t * transformedRay.direction.z);
			if ((x * x + z * z) <= 1)
			{
				ObjectHit objHit(t, this);
				intersectTimes.push_back(objHit);
			}

			t = (maxY - transformedRay.origin.y) / transformedRay.direction.y;
			x = transformedRay.origin.x + (t * transformedRay.direction.x);
			z = transformedRay.origin.z + (t * transformedRay.direction.z);
			if ((x * x + z * z) <= 1)
			{
				ObjectHit objHit(t, this);
				intersectTimes.push_back(objHit);
			}
		}

		return intersectTimes;
	}

	void Cylinder::getIntersectTime(Ray& ray, std::vector<Shape::ObjectHit>& intersectTimes)
	{
		Ray transformedRay = ray.transform(invTransform);

		double a = (transformedRay.direction.x * transformedRay.direction.x) +
			(transformedRay.direction.z * transformedRay.direction.z);

		if (a > DoubleHelpers::EPSILON)
		{
			double b = 2 * (transformedRay.origin.x * transformedRay.direction.x +
				transformedRay.origin.z * transformedRay.direction.z);

			double c = (transformedRay.origin.x * transformedRay.origin.x) +
				(transformedRay.origin.z * transformedRay.origin.z) - 1;

			double disc = ((b * b) - (4 * a * c));
			if (disc > -DoubleHelpers::EPSILON_HALF)
			{
				double discSqrt = std::sqrt(disc);
				double t0 = (-b - discSqrt) / (2 * a);
				double t1 = (discSqrt - b) / (2 * a);

				if (((transformedRay.origin.y + (t0 * transformedRay.direction.y) < maxY) &&
					((transformedRay.origin.y + (t0 * transformedRay.direction.y)) > minY)))
				{
					ObjectHit objHit(t0, this);
					intersectTimes.push_back(objHit);
				}

				if (((transformedRay.origin.y + (t1 * transformedRay.direction.y) < maxY) &&
					((transformedRay.origin.y + (t1 * transformedRay.direction.y)) > minY)))
				{
					ObjectHit objHit(t1, this);
					intersectTimes.push_back(objHit);
				}
			}
		}

		if ((intersectTimes.size() < 2) && closed && ((transformedRay.direction.y > DoubleHelpers::EPSILON_HALF) || (transformedRay.direction.y < (-DoubleHelpers::EPSILON_HALF))))
		{
			double t = (minY - transformedRay.origin.y) / transformedRay.direction.y;
			double x = transformedRay.origin.x + (t * transformedRay.direction.x);
			double z = transformedRay.origin.z + (t * transformedRay.direction.z);
			if ((x * x + z * z) <= 1)
			{
				ObjectHit objHit(t, this);
				intersectTimes.push_back(objHit);
			}

			t = (maxY - transformedRay.origin.y) / transformedRay.direction.y;
			x = transformedRay.origin.x + (t * transformedRay.direction.x);
			z = transformedRay.origin.z + (t * transformedRay.direction.z);
			if ((x * x + z * z) <= 1)
			{
				ObjectHit objHit(t, this);
				intersectTimes.push_back(objHit);
			}
		}
	}

	void Cylinder::getIntersections(Ray ray, std::vector<Shape::ObjectHit>& intersectTimes)
	{
		ray.transformed(invTransform);

		double a = (ray.direction.x * ray.direction.x) +
			(ray.direction.z * ray.direction.z);

		if (a > DoubleHelpers::EPSILON)
		{
			double b = 2 * (ray.origin.x * ray.direction.x +
				ray.origin.z * ray.direction.z);

			double c = (ray.origin.x * ray.origin.x) +
				(ray.origin.z * ray.origin.z) - 1;

			double disc = ((b * b) - (4 * a * c));
			if (disc > -DoubleHelpers::EPSILON_HALF)
			{
				double discSqrt = std::sqrt(disc);
				double t0 = (-b - discSqrt) / (2 * a);
				double t1 = (discSqrt - b) / (2 * a);

				if (((ray.origin.y + (t0 * ray.direction.y) < maxY) &&
					((ray.origin.y + (t0 * ray.direction.y)) > minY)))
				{
					ObjectHit objHit(t0, this);
					intersectTimes.push_back(objHit);
				}

				if (((ray.origin.y + (t1 * ray.direction.y) < maxY) &&
					((ray.origin.y + (t1 * ray.direction.y)) > minY)))
				{
					ObjectHit objHit(t1, this);
					intersectTimes.push_back(objHit);
				}
			}
		}

		if ((intersectTimes.size() < 2) && closed && ((ray.direction.y > DoubleHelpers::EPSILON_HALF) || (ray.direction.y < (-DoubleHelpers::EPSILON_HALF))))
		{
			double t = (minY - ray.origin.y) / ray.direction.y;
			double x = ray.origin.x + (t * ray.direction.x);
			double z = ray.origin.z + (t * ray.direction.z);
			if ((x * x + z * z) <= 1)
			{
				ObjectHit objHit(t, this);
				intersectTimes.push_back(objHit);
			}

			t = (maxY - ray.origin.y) / ray.direction.y;
			x = ray.origin.x + (t * ray.direction.x);
			z = ray.origin.z + (t * ray.direction.z);
			if ((x * x + z * z) <= 1)
			{
				ObjectHit objHit(t, this);
				intersectTimes.push_back(objHit);
			}
		}
	}

	BoundingBox Cylinder::getBoundingBox(void)
	{
		BoundingBox mBbox;
		if (true == closed)
		{
			mBbox.max = point(1, maxY, 1);
			mBbox.min = point(-1, minY, -1);
		}
		else
		{
			mBbox.max = point(1, INFINITY, 1);
			mBbox.min = point(-1, -INFINITY, -1);
		}

		mBbox.setTransform(transform);
		
		return mBbox;
	}

	// =========================== Operators ===========================
	bool Cylinder::operator==(Shape const& s1)
	{
		return false;
	}

	// ============================ Helpers =============================
}