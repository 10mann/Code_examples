#pragma once

#include "tuple.h"
#include "ray.h"

#include <vector>

namespace RayTracer
{
	class BoundingBox
	{
	public:

		// Variables
		Tuple min;
		Tuple max;

		Matrix transform;
		Matrix invTransform;

		bool altered;

		// Constructors
		BoundingBox();
		BoundingBox(Tuple p1, Tuple p2);

		// Methods
		bool intersects(Ray& ray);

		//std::vector<BoundingBox> splitBounds(void);
		void splitBounds(std::vector<BoundingBox>& boxes);

		void addPoint(Tuple p);
		void addBox(BoundingBox box);
		bool containsPoint(Tuple p);
		bool containsBox(BoundingBox b);
		bool containsBoxCenter(BoundingBox b);

		void setTransform(Matrix m);

		bool isAltered(void);

		// Operators
	};

}