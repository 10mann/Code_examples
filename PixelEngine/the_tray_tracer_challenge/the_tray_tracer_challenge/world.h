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
		std::vector<Shape*> objects;
		std::vector<PointLight> lights;

		// Constructors
		World();

		// Methods
		bool containsObject(const Shape* s);
		bool containsLight(const PointLight& s);
		IntersectionList getIntersections(Ray& ray);
		Color getHitColor(ComputeValues computeValues, int bounces);
		Color getColor(Ray& ray, int bounces);
		bool isInShadow(Tuple point, PointLight light);
		void calculateInverseTransforms(void);
		Color getReflectedColor(ComputeValues comp, int bounces);
		Color getRefractedColor(ComputeValues comp, int bounces);

		// Operators
		
	};

	Color getLighting(Shape* s, PointLight light, Tuple position, Tuple eyeDirection, Tuple normal, bool inShadow);
	World createDfaultWorld();
}