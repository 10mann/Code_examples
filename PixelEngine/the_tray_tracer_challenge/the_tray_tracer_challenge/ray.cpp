#include "ray.h"

#include "DoubleHelpers.h"

using DoubleHelpers::isEqualDouble;

namespace RayTracer
{
	// ========================= Constructors ==========================
	Ray::Ray()
		:origin(point(0, 0, 0)), direction(vector(0, 0, 0))
	{
	}

	Ray::Ray(Tuple origin, Tuple direction)
		:origin(origin), direction(direction)
	{
	}


	// ============================ Methods ============================
	Tuple Ray::getPosition(double time)
	{
		return origin + (direction * time);
	}

	Ray Ray::transform(Matrix const& m)
	{
		return Ray(m * origin, m * direction);
	}

	// =========================== Operators ===========================


	// =========================== Helpers ===========================
	Tuple RayTracer::getReflection(Tuple in, Tuple normal)
	{
		return in - normal * 2 * in.dotProduct(normal);
	}

	Color getLighting(Material m, PointLight light, Tuple position, Tuple eyeDirection, Tuple normal, bool inShadow)
	{
		Color effective_color = m.color * light.intensity;
		Color diffuse(0, 0, 0);
		Color specular(0, 0, 0);
		if (false == inShadow)
		{
			Tuple lightDir = (light.position - position).getNormalized();
			double lightDotNormal = lightDir.dotProduct(normal);
			if (lightDotNormal > 0)
			{
				diffuse = effective_color * m.diffuse * lightDotNormal;
				Tuple reflectDir = getReflection(-lightDir, normal);
				double reflectDotEye = reflectDir.dotProduct(eyeDirection);

				if (reflectDotEye > 0)
				{
					double factor = std::pow(reflectDotEye, m.shininess);
					specular = light.intensity * m.specular * factor;
				}
			}
		}

		return (effective_color * m.ambient) + specular + diffuse;
	}
}

