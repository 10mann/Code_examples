#include "world.h"

namespace RayTracer
{
	// ========================= Constructors ==========================
	RayTracer::World::World()
	{
	}

	// ============================ Methods ============================
	bool World::containsObject(const Sphere& s)
	{
		bool result = false;
		for (const auto& sphere : objects)
		{
			if (sphere == s)
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

	IntersectionList RayTracer::World::getIntersections(Ray& ray)
	{
		IntersectionList list;
		for (auto& s : objects)
		{
			IntersectionList hits = ray.getIntersection(s);
			list.addList(hits);
		}
		
		list.sort();
		return list;
	}

	// =========================== Operators ===========================


	// ============================ Helpers =============================
	World RayTracer::createDfaultWorld()
	{
		World world;
		world.lights.push_back(PointLight(Color(1, 1, 1), point(-10, 10, -10)));
		Sphere s1;
		Material m;
		m.color = Color(0.8, 1, 0.6);
		m.diffuse = 0.7;
		m.specular = 0.2;
		s1.material = m;
		
		Sphere s2;
		s2.transform = scaling(0.5, 0.5, 0.5);
		world.objects.push_back(s1);
		world.objects.push_back(s2);
		return world;
	}
}