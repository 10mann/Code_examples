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

	void World::getIntersections(Ray& ray, IntersectionList& list)
	{
		/*IntersectionList list;*/
		for (auto& s : objects)
		{
			list.addIntersections(ray, s);
		}
		
		list.sort();
		//return list;
	}

	Color World::getHitColor(ComputeValues computeValues, int bounces)
	{
		Color color;
		//for (const auto& light : lights)
		//{
		//	color = color + getLighting(computeValues.object, light, computeValues.point, computeValues.eyeDir, computeValues.normal, isInShadow(computeValues.overPoint, light));
		//}
		color = color + getLighting(computeValues, lights[0], isInShadow(computeValues.overPoint, lights[0]));

		if ((computeValues.object->material.reflective > DoubleHelpers::EPSILON_HALF) &&
			(computeValues.object->material.transparency > DoubleHelpers::EPSILON_HALF))
		{
			Color reflected = getReflectedColor(computeValues, bounces);
			Color refracted = getRefractedColor(computeValues, bounces);
			double reflectance = getSchlick(computeValues);
			color = color + (reflected * reflectance) + (refracted * (1 - reflectance));
		}

		return color;
	}

	Color RayTracer::World::getColor(Ray& ray, int bounces)
	{
		// ================== Check later ==============================
		Color color;
		IntersectionList list;

		for (const auto& obj : objects)
		{
			list.addIntersections(ray, obj);
		}

		Intersection hit = list.hit();
		if (hit.i > 0)
		{
			color += getHitColor(list.getComputeValues(hit, ray), bounces);
		}
		
		return color;
	}

	bool World::isInShadow(Tuple point, PointLight light)
	{
		Tuple vec = (lights[0].position - point);
		double distSquared = vec.getMagnitudeSquared();
		Ray ray(point, vec.getNormalized());
		IntersectionList list;
		getIntersections(ray, list);
		Intersection hit = list.hit();
		return ((hit != Intersection::empty) && ((hit.i * hit.i) < distSquared));
	}

	void World::calculateInverseTransforms(void)
	{
		for (auto& obj : objects)
		{
			obj->invTransform = obj->transform.getInverse();
		}
	}

	Color World::getReflectedColor(ComputeValues& comp, int bounces)
	{
		Color c(0, 0, 0);
		if ((bounces > 0) &&  (comp.object->material.reflective > DoubleHelpers::EPSILON))
		{
			Ray ray(comp.overPoint, comp.reflectVector);
			c += getColor(ray, --bounces) * comp.object->material.reflective;
		}

		return c;
	}

	Color World::getRefractedColor(ComputeValues& comp, int bounces)
	{
		Color color(0, 0, 0);

		if ((comp.sin2t < 1) && 
			(comp.object->material.transparency > DoubleHelpers::EPSILON) &&
			(bounces > 0))
		{
			Tuple dir = (comp.normal * (comp.nRatio * comp.cos_i - comp.cos_t)) - (comp.eyeDir * comp.nRatio);

			Ray refractRay(comp.underPoint, dir);
			color += getColor(refractRay, --bounces) * comp.object->material.transparency;
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
		Color effectiveColor = s->colorAt(position) * light.intensity;
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

	Color getLighting(ComputeValues& c, PointLight light, bool inShadow)
	{
		Color effectiveColor = c.object->colorAt(c.point) * light.intensity;
		Color diffuse(0, 0, 0);
		Color specular(0, 0, 0);
		if (false == inShadow)
		{
			Tuple lightDir = (light.position - c.point).getNormalized();
			double lightDotNormal = lightDir.dotProduct(c.normal);
			if (lightDotNormal > (DoubleHelpers::EPSILON_HALF))
			{
				diffuse = effectiveColor * c.object->material.diffuse * lightDotNormal;
				Tuple reflectDir = getReflection(-lightDir, c.normal);
				double reflectDotEye = reflectDir.dotProduct(c.eyeDir);

				if (reflectDotEye > (DoubleHelpers::EPSILON_HALF))
				{
					double factor = std::pow(reflectDotEye, c.object->material.shininess);
					specular = light.intensity * c.object->material.specular * factor;
				}
			}
		}

		return (effectiveColor * c.object->material.ambient) + specular + diffuse;
	}

	double getSchlick(ComputeValues comp)
	{
		double reflectance = 0;

		if ((comp.sin2t > 1) && (comp.n1 > comp.n2))
		{
			reflectance = 1;
		}
		else
		{
			if (comp.n1 > comp.n2)
			{
				reflectance = ((comp.n1 - comp.n2) / (comp.n1 + comp.n2)) * ((comp.n1 - comp.n2) / (comp.n1 + comp.n2));
				reflectance = reflectance + ((1 - reflectance) * std::pow((1 - comp.cos_t), 5));
			}
			else
			{
				reflectance = ((comp.n1 - comp.n2) / (comp.n1 + comp.n2)) * ((comp.n1 - comp.n2) / (comp.n1 + comp.n2));
				reflectance = reflectance + ((1 - reflectance) * std::pow((1 - comp.cos_i), 5));
			}
		}

		return reflectance;
	}
}