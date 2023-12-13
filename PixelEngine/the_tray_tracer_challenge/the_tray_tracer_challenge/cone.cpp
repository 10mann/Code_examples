#include "cone.h"
#include "DoubleHelpers.h"

namespace RayTracer
{
	// ========================= Constructors ==========================
	Cone::Cone()
		: minY(-INFINITY), maxY(INFINITY), closed(false)
	{
	}

	// ============================ Methods ============================
	Tuple Cone::getLocalNormal(Tuple point)
	{
		double y = std::sqrt(point.x * point.x + point.z * point.z);
		if (point.y > DoubleHelpers::EPSILON)
		{
			y = -y;
		}

		Tuple normal = vector(point.x, y, point.z);
		double dist = (point.x * point.x) + (point.z * point.z);

		if (dist < (point.y * point.y))
		{
			if (point.y >= (maxY - DoubleHelpers::EPSILON))
			{
				normal = vector(0, 1, 0);
			}
			else if (point.y <= (minY + DoubleHelpers::EPSILON))
			{
				normal = vector(0, -1, 0);
			}
		}

		return normal;
	}

	std::vector<Shape::ObjectHit> Cone::getIntersectTime(Ray& ray) 
	{
		std::vector<ObjectHit> intersectTimes;
		Ray transformedRay = ray.transform(invTransform);

		double a = (transformedRay.direction.x * transformedRay.direction.x) -
			(transformedRay.direction.y * transformedRay.direction.y) +
			(transformedRay.direction.z * transformedRay.direction.z);

		double b = 2 * ((transformedRay.origin.x * transformedRay.direction.x) -
			(transformedRay.origin.y * transformedRay.direction.y) +
			(transformedRay.origin.z * transformedRay.direction.z));
			
			if ((std::abs(a) > DoubleHelpers::EPSILON) || (std::abs(b) > DoubleHelpers::EPSILON))
		{
			double c = (transformedRay.origin.x * transformedRay.origin.x) -
				(transformedRay.origin.y * transformedRay.origin.y) +
				(transformedRay.origin.z * transformedRay.origin.z);

			if ((std::abs(a) > DoubleHelpers::EPSILON))
			{
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
			else
			{
				ObjectHit objHit(-c / (2 * b), this);
				intersectTimes.push_back(objHit);
			}
		}

		if (closed && ((transformedRay.direction.y > DoubleHelpers::EPSILON_HALF) || (transformedRay.direction.y < (-DoubleHelpers::EPSILON_HALF))))
		{
			double t = (minY - transformedRay.origin.y) / transformedRay.direction.y;
			double x = transformedRay.origin.x + (t * transformedRay.direction.x);
			double z = transformedRay.origin.z + (t * transformedRay.direction.z);
			if ((x * x + z * z) <= (minY * minY))
			{
				ObjectHit objHit(t, this);
				intersectTimes.push_back(objHit);
			}

			t = (maxY - transformedRay.origin.y) / transformedRay.direction.y;
			x = transformedRay.origin.x + (t * transformedRay.direction.x);
			z = transformedRay.origin.z + (t * transformedRay.direction.z);
			if ((x * x + z * z) <= (maxY * maxY))
			{
				ObjectHit objHit(t, this);
				intersectTimes.push_back(objHit);
			}
		}

		return intersectTimes;
	}

	void Cone::getIntersectTime(Ray& ray, std::vector<Shape::ObjectHit>& intersectTimes)
	{
		Ray transformedRay = ray.transform(invTransform);

		double a = (transformedRay.direction.x * transformedRay.direction.x) -
			(transformedRay.direction.y * transformedRay.direction.y) +
			(transformedRay.direction.z * transformedRay.direction.z);

		double b = 2 * ((transformedRay.origin.x * transformedRay.direction.x) -
			(transformedRay.origin.y * transformedRay.direction.y) +
			(transformedRay.origin.z * transformedRay.direction.z));

		if ((std::abs(a) > DoubleHelpers::EPSILON) || (std::abs(b) > DoubleHelpers::EPSILON))
		{
			double c = (transformedRay.origin.x * transformedRay.origin.x) -
				(transformedRay.origin.y * transformedRay.origin.y) +
				(transformedRay.origin.z * transformedRay.origin.z);

			if ((std::abs(a) > DoubleHelpers::EPSILON))
			{
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
			else
			{
				ObjectHit objHit(-c / (2 * b), this);
				intersectTimes.push_back(objHit);
			}
		}

		if (closed && ((transformedRay.direction.y > DoubleHelpers::EPSILON_HALF) || (transformedRay.direction.y < (-DoubleHelpers::EPSILON_HALF))))
		{
			double t = (minY - transformedRay.origin.y) / transformedRay.direction.y;
			double x = transformedRay.origin.x + (t * transformedRay.direction.x);
			double z = transformedRay.origin.z + (t * transformedRay.direction.z);
			if ((x * x + z * z) <= (minY * minY))
			{
				ObjectHit objHit(t, this);
				intersectTimes.push_back(objHit);
			}

			t = (maxY - transformedRay.origin.y) / transformedRay.direction.y;
			x = transformedRay.origin.x + (t * transformedRay.direction.x);
			z = transformedRay.origin.z + (t * transformedRay.direction.z);
			if ((x * x + z * z) <= (maxY * maxY))
			{
				ObjectHit objHit(t, this);
				intersectTimes.push_back(objHit);
			}
		}
	}

	BoundingBox Cone::getBoundingBox(void)
	{
		BoundingBox mBbox;
		if (true == closed)
		{
			double absMaxY = std::abs(maxY);
			double absMinY = std::abs(minY);
			double maxWidth = (absMaxY > absMinY) ? absMaxY : absMinY;

			mBbox.max = point(maxWidth, maxY, maxWidth);
			mBbox.min = point(-maxWidth, minY, -maxWidth);
		}
		else
		{
			mBbox.max = point(INFINITY, INFINITY, INFINITY);
			mBbox.min = point(-INFINITY, -INFINITY, -INFINITY);
		}

		mBbox.setTransform(transform);
		
		return mBbox;
	}

	// =========================== Operators ===========================
	bool Cone::operator==(Shape const& s1)
	{
		return false;
	}

	// ============================ Helpers =============================
}