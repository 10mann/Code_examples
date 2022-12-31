#include "bounding_box.h"

#include "DoubleHelpers.h"

namespace RayTracer
{
	// ========================= Constructors ==========================
	BoundingBox::BoundingBox()
		: max(point(-INFINITY, -INFINITY, -INFINITY)), min(point(INFINITY, INFINITY, INFINITY)),
		transform(Matrix::identityMatrix), invTransform(Matrix::identityMatrix), altered(false)
	{
	}

	BoundingBox::BoundingBox(Tuple p1, Tuple p2)
		: min(p1), max(p2), transform(Matrix::identityMatrix), invTransform(Matrix::identityMatrix), altered(true)
	{
	}

	// ============================ Methods ============================
	bool BoundingBox::intersects(Ray& ray)
	{
		bool success = false;
		Ray transformedRay = ray.transform(invTransform);

		double xMin, yMin, zMin, xMax, yMax, zMax, temp, tMin, tMax;

		xMin = (min.x - transformedRay.origin.x) / transformedRay.direction.x;
		xMax = (max.x - transformedRay.origin.x) / transformedRay.direction.x;

		if (xMin > xMax)
		{
			temp = xMin;
			xMin = xMax;
			xMax = temp;
		}

		yMin = (min.y - transformedRay.origin.y) / transformedRay.direction.y;
		yMax = (max.y - transformedRay.origin.y) / transformedRay.direction.y;

		if (yMin > yMax)
		{
			temp = yMin;
			yMin = yMax;
			yMax = temp;
		}

		zMin = (min.z - transformedRay.origin.z) / transformedRay.direction.z;
		zMax = (max.z - transformedRay.origin.z) / transformedRay.direction.z;

		if (zMin > zMax)
		{
			temp = zMin;
			zMin = zMax;
			zMax = temp;
		}

		temp = (xMin > yMin) ? xMin : yMin;
		tMin = (zMin > temp) ? zMin : temp;


		temp = (xMax < yMax) ? xMax : yMax;
		tMax = (zMax < temp) ? zMax : temp;
		if (tMax > tMin)
		{
			success = true;
		}

		return success;
	}

	std::vector<BoundingBox> BoundingBox::splitBounds(void)
	{
		std::vector<BoundingBox> boxes;
		boxes.reserve(2);

		double sizeX = max.x - min.x;
		double sizeY = max.y - min.y;
		double sizeZ = max.z - min.z;

		if ((sizeX >= (sizeY - DoubleHelpers::EPSILON)) && 
			(sizeX >= (sizeZ - DoubleHelpers::EPSILON)))
		{
			double midPoint = min.x + (sizeX / 2);
			boxes.emplace_back(BoundingBox(point(min.x, min.y, min.z),
				point(midPoint, max.y, max.z)));

			boxes.emplace_back(BoundingBox(point(midPoint, min.y, min.z),
				point(max.x, max.y, max.z)));
		}
		else if ((sizeY >= (sizeX - DoubleHelpers::EPSILON)) &&
			(sizeY >= (sizeZ - DoubleHelpers::EPSILON)))
		{
			double midPoint = min.y + (sizeY / 2);
			boxes.emplace_back(BoundingBox(point(min.x, min.y, min.z),
				point(max.x, midPoint, max.z)));

			boxes.emplace_back(BoundingBox(point(min.x, midPoint, min.z),
				point(max.x, max.y, max.z)));
		}
		else
		{
			double midPoint = min.z + (sizeZ / 2);
			boxes.emplace_back(BoundingBox(point(min.x, min.y, min.z),
				point(max.x, max.y, midPoint)));

			boxes.emplace_back(BoundingBox(point(min.x, min.y, midPoint),
				point(max.x, max.y, max.z)));

		}

		return boxes;
	}

	void BoundingBox::addPoint(Tuple p)
	{
		altered = true;
		if (p.x > max.x)
		{
			max.x = p.x;
		}
		if (p.x < min.x)
		{
			min.x = p.x;
		}

		if (p.y > max.y)
		{
			max.y = p.y;
		}
		if (p.y < min.y)
		{
			min.y = p.y;
		}

		if (p.z > max.z)
		{
			max.z = p.z;
		}
		if (p.z < min.z)
		{
			min.z = p.z;
		}
	}

	void BoundingBox::addBox(BoundingBox box)
	{
		altered = true;
		addPoint(box.min);
		addPoint(box.max);
	}

	bool BoundingBox::containsPoint(Tuple p)
	{
		return (((p.x + DoubleHelpers::EPSILON) > min.x) && 
			((p.x - DoubleHelpers::EPSILON) < max.x) && 
			((p.y + DoubleHelpers::EPSILON) > min.y) && 
			((p.y - DoubleHelpers::EPSILON) < max.y) && 
			((p.z + DoubleHelpers::EPSILON) > min.z) && 
			((p.z - DoubleHelpers::EPSILON) < max.z));
	}

	bool BoundingBox::containsBox(BoundingBox b)
	{
		return (containsPoint(b.min) && containsPoint(b.max));
	}

	void BoundingBox::setTransform(Matrix m)
	{
		Tuple p1 = min;
		Tuple p2 = point(min.x, min.y, max.z);
		Tuple p3 = point(min.x, max.y, min.z);
		Tuple p4 = point(min.x, max.y, max.z);
		Tuple p5 = point(max.x, min.y, max.z);
		Tuple p6 = point(max.x, min.y, min.z);
		Tuple p7 = point(max.x, max.y, min.z);
		Tuple p8 = max;

		min = point(INFINITY, INFINITY, INFINITY);
		max = point(-INFINITY, -INFINITY, -INFINITY);

		addPoint(m * p1);
		addPoint(m * p2);
		addPoint(m * p3);
		addPoint(m * p4);
		addPoint(m * p5);
		addPoint(m * p6);
		addPoint(m * p7);
		addPoint(m * p8);
	}

	bool BoundingBox::isAltered(void)
	{
		return altered;
	}

	// =========================== Operators ===========================


	// ============================ Helpers =============================

}