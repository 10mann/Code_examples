#include "world.h"
#include "DoubleHelpers.h"
#include "raytracer_config.h"

#include <cmath>
#include <iostream>

namespace RayTracer
{
	// ========================= Constructors ==========================
	RayTracer::World::World()
	{
	}

	// ============================ Methods ============================
	bool World::containsObject(const Shape* s)
	{
		bool result = false;
		for (const auto& shape : objects)
		{
			if ((*shape) == *s)
			{
				result = true;
				break;
			}
		}
		return result;
	}

	bool World::containsLight(const PointLight& l)
	{
		bool result = false;
		for (const auto& light : lights)
		{
			if (light == l)
			{
				result = true;
				break;
			}
		}
		return result;
	}

	IntersectionList World::getIntersections(Ray& ray)
	{
		IntersectionList list;
		for (auto& s : objects)
		{
			list.addIntersections(ray, s);
		}
		
		list.sort();
		return list;
	}

	Color World::getHitColor(ComputeValues computeValues, int bounces)
	{
		Color color;
		for (auto& light : lights)
		{
			color = color + getLighting(computeValues.object, light, computeValues.point, computeValues.eyeDir, computeValues.normal, isInShadow(computeValues.overPoint, light));
		}

		color = color + getReflectedColor(computeValues, bounces);

		color = color + getRefractedColor(computeValues, bounces);

		return color;
	}

	Color RayTracer::World::getColor(Ray& ray, int bounces)
	{
		// ================== Check later ==============================
		Color color;
		IntersectionList list;

		for (auto& obj : objects)
		{
			list.addIntersections(ray, obj);
		}

		Intersection hit = list.hit();
		if (hit.i > 0)
		{
			color = getHitColor(list.getComputeValues(hit, ray), bounces);
		}
		
		return color;
	}

	bool World::isInShadow(Tuple point, PointLight light)
	{
		Tuple vec = (lights[0].position - point);
		double distSquared = vec.getMagnitudeSquared();
		Ray ray(point, vec.getNormalized());
		Intersection hit = getIntersections(ray).hit();
		return ((hit != Intersection::empty) && ((hit.i * hit.i) < distSquared));
	}

	void World::calculateInverseTransforms(void)
	{
		for (auto& obj : objects)
		{
			obj->invTransform = obj->transform.getInverse();
		}
	}

	Color World::getReflectedColor(ComputeValues comp, int bounces)
	{
		Color c(0, 0, 0);
		if ((bounces > 0) &&  (comp.object->material.reflective > DoubleHelpers::EPSILON))
		{
			Ray ray(comp.overPoint, comp.reflectVector);
			c = getColor(ray, --bounces) * comp.object->material.reflective;
		}

		return c;
	}

	Color World::getRefractedColor(ComputeValues comp, int bounces)
	{
		Color color(0, 0, 0);

		double cos_i = comp.eyeDir.dotProduct(comp.normal);
		double nRatio = comp.n1 / comp.n2;
		double sin2t = (nRatio * nRatio) * (1 - (cos_i * cos_i));

		if ((sin2t < 1) && 
			(comp.object->material.transparency > DoubleHelpers::EPSILON_HALF) && 
			(bounces > 0))
		{
			//color = Color(1, 1, 1);
			double cos_t = std::sqrt(1 - sin2t);
			Tuple dir = (comp.normal * (nRatio * cos_i - cos_t)) - (comp.eyeDir * nRatio);

			Ray refractRay(comp.underPoint, dir);
			color = getColor(refractRay, --bounces) * comp.object->material.transparency;
		}

		return color;
	}

	// =========================== Operators ===========================


	// ============================ Helpers =============================
	World RayTracer::createDfaultWorld()
	{
		World world;
		world.lights.push_back(PointLight(Color(1, 1, 1), point(-10, 10, -10)));
		static Sphere s1;
		Material m;
		m.color = Color(0.8, 1, 0.6);
		m.diffuse = 0.7;
		m.specular = 0.2;
		s1.material = m;
		
		static Sphere s2;
		s2.transform = scaling(0.5, 0.5, 0.5);
		world.objects.push_back(&s1);
		world.objects.push_back(&s2);
		return world;
	}

	Color getLighting(Shape* s, PointLight light, Tuple position, Tuple eyeDirection, Tuple normal, bool inShadow)
	{
		Color effectiveColor = s->material.getColor(position) * light.intensity;
		Color diffuse(0, 0, 0);
		Color specular(0, 0, 0);
		if (false == inShadow)
		{
			Tuple lightDir = (light.position - position).getNormalized();
			double lightDotNormal = lightDir.dotProduct(normal);
			if (lightDotNormal > (DoubleHelpers::EPSILON_HALF))
			{
				diffuse = effectiveColor * s->material.diffuse * lightDotNormal;
				Tuple reflectDir = getReflection(-lightDir, normal);
				double reflectDotEye = reflectDir.dotProduct(eyeDirection);

				if (reflectDotEye > (DoubleHelpers::EPSILON_HALF))
				{
					double factor = std::pow(reflectDotEye, s->material.shininess);
					specular = light.intensity * s->material.specular * factor;
				}
			}
		}

		return (effectiveColor * s->material.ambient) + specular + diffuse;
	}
}