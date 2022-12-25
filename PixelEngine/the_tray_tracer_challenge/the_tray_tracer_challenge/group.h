#pragma once

#include "shape.h"

namespace RayTracer
{
	class Group : public Shape
	{
	public:

		// Variables
		std::vector<Shape*> objects;

		// Constructors
		Group();

		// Methods
		//Tuple getNormal(Tuple point) override;
		Tuple getLocalNormal(Tuple point) override;
		std::vector<ObjectHit> getIntersectTime(Ray& ray) override;
		//Color colorAt(Tuple point) override;

		void addChild(Shape* child);

		// Operators
		bool operator== (Shape const& s1) override;
	};
}