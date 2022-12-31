#pragma once

#include "shape.h"

#include <memory>

namespace RayTracer
{
	class Group : public Shape
	{
	public:

		// Variables
		std::vector<Shape*> objects;
		BoundingBox mBbox;
		std::vector<std::unique_ptr<Group>> subGroups;

		// Constructors
		Group();

		// Methods
		Tuple getLocalNormal(Tuple point) override;
		std::vector<ObjectHit> getIntersectTime(Ray& ray) override;
		BoundingBox getBoundingBox(void) override;

		void addChild(Shape* child);
		void removeChild(Shape* child);
		void calculateBoundingBox(void);

		std::vector<std::vector<Shape*>> partitionChildren(void);
		void makeSubGroup(const std::vector<Shape*>& children);
		void divide(int threshold);

		// Operators
		bool operator== (Shape const& s1) override;
	};
}