#pragma once

#include "sphere.h"
#include "point_light.h"
#include "intersection_list.h"
#include "ray.h"

#include <vector>

namespace RayTracer
{
	class World
	{
	public:

		// Variables
		std::vector<Sphere> objects;
		//PointLight lighSource;
		std::vector<PointLight> lights;

		// Constructors
		World();

		// Methods
		bool containsObject(const Sphere& s);
		bool containsLight(const PointLight& s);
		IntersectionList getIntersections(Ray& ray);

		// Operators

	};

	World createDfaultWorld();
}