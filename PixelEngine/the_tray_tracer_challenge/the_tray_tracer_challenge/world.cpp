#include "world.h"

namespace RayTracer
{
	// ========================= Constructors ==========================
	RayTracer::World::World()
	{
	}

	// ============================ Methods ============================
	bool World::containsObject(const Shape& s)
	{
		bool result = false;
		for (const auto& shape : objects)
		{
			if (*shape == s)
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
			//list.addList(ray.getIntersection(s));
			list.addIntersections(ray, s);
		}
		
		list.sort();
		return list;
	}

	Color World::getHitColor(ComputeValues computeValues)
	{
		Color color;
		for (auto& light : lights)
		{
			color = color + getLighting(computeValues.object->material, light, computeValues.point, computeValues.eyeDir, computeValues.normal, isInShadow(computeValues.overPoint, light));
		}

		return color;
	}

	Color RayTracer::World::getColor(Ray& ray)
	{
		Color color;
		IntersectionList list;

		for (auto& obj : objects)
		{
			//list.addList(ray.getIntersection(obj));
			list.addIntersections(ray, obj);
		}

		Intersection hit = list.hit();
		if (hit.i > 0)
		{
			//color = getHitColor(ray.getComputeValues(hit));
			color = getHitColor(hit.getComputeValues(ray));
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
}