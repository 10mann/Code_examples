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

	IntersectionList Ray::getIntersection(Sphere sphere)
	{
		//Ray ray = transform((sphere.transform).getInverse());
		Ray ray = transform((sphere.invTransform));
		IntersectionList intersections;
		Tuple sphereVector = ray.origin - sphere.center;
		//double a = ray.direction.dotProduct(ray.direction);
		double a = 2 * ray.direction.dotProduct(ray.direction);
		double b = 2 * ray.direction.dotProduct(sphereVector);
		//double c = sphereVector.dotProduct(sphereVector) - 1.0;
		//double discriminant = (b * b) - (2 * a * c);
		double discriminant = (b * b) - (2 * a * (sphereVector.dotProduct(sphereVector) - 1.0));
		//double sqrtDisc = std::sqrt(discriminant);

		if (discriminant > (-DoubleHelpers::EPSILON))
		{
			intersections = IntersectionList(
				//Intersection((-b - std::sqrt(discriminant)) / (a), sphere),
				//Intersection((std::sqrt(discriminant) - b) / (a), sphere));
				Intersection((-1 * (b + std::sqrt(discriminant))) / (a), sphere),
				Intersection((std::sqrt(discriminant) - b) / (a), sphere));
		}

		return intersections;
	}

	double Ray::getDiscriminant(Sphere const& sphere)
	{
		Tuple sphereVector = origin - sphere.center;
		double a = direction.dotProduct(direction);
		double b = 2 * direction.dotProduct(sphereVector);
		double c = sphereVector.dotProduct(sphereVector) - 1;
		return (b * b) - (4 * a * c);
	}

	Ray Ray::transform(Matrix const& m)
	{
		return Ray(m * origin, m * direction);
	}
	
	ComputeValues Ray::getComputeValues(Intersection& intersect)
	{
		ComputeValues computeValues;
		computeValues.i = intersect.i;
		computeValues.object = intersect.object;
		computeValues.point = getPosition(computeValues.i);
		computeValues.eyeDir = -direction;
		computeValues.normal = computeValues.object.getNormal(computeValues.point);
		computeValues.inside = (computeValues.normal.dotProduct(computeValues.eyeDir) < 0);
		if (true == computeValues.inside)
		{
			computeValues.normal = -computeValues.normal;
		}
		computeValues.overPoint = computeValues.point + computeValues.normal * DoubleHelpers::EPSILON;
		return computeValues;
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

