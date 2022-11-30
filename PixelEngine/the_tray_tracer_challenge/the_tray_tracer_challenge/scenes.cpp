#include "scenes.h"

#include "tuple.h"
#include "canvas.h"
#include "color.h"
#include "matrix.h"
#include "DoubleHelpers.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "intersection.h"
#include "intersection_list.h"
#include "material.h"
#include "point_light.h"
#include "world.h"
#include "camera.h"
#include "stripe_pattern.h"
#include "gradient_pattern.h"
#include "ring_pattern.h"

using RayTracer::Matrix;
using RayTracer::Tuple;
using RayTracer::Ray;
using RayTracer::Sphere;
using RayTracer::World;
using RayTracer::Material;
using RayTracer::Color;
using RayTracer::Canvas;
using RayTracer::Camera;
using RayTracer::PointLight;
using RayTracer::Plane;
using RayTracer::StripePattern;
using RayTracer::GradientPattern;
using RayTracer::RingPattern;

using RayTracer::rotationX;
using RayTracer::rotationY;
using RayTracer::rotationZ;
using RayTracer::translation;
using RayTracer::scaling;
using RayTracer::getLighting;
using RayTracer::createDfaultWorld;
using RayTracer::viewTransform;
using RayTracer::point;
using RayTracer::vector;

using DoubleHelpers::MATH_PI;

namespace RayTracer
{

	//void drawClock(olc::PixelGameEngine* engine)
	//{
	//	// Draw clock using rotation matrix
	//	Tuple clockP = RayTracer::point(0, 1, 0);
	//
	//	for (double rads = 0.0; rads < (2.0 * MATH_PI); rads += (MATH_PI / 6.0))
	//	{
	//		Tuple hourP = rotationZ(rads) * clockP;
	//		hourP = scaling(150, 150, 150) * hourP;
	//		hourP = translation(engine->ScreenWidth() / 2.0, engine->ScreenHeight() / 2.0, 0) * hourP;
	//		engine->FillCircle({ (int)(hourP.x), (int)(hourP.y) }, 3);
	//	}
	//}

	//void drawCirclebByRay(olc::PixelGameEngine* engine)
	//{
	//	int width = engine->ScreenWidth();
	//	int height = engine->ScreenHeight();
	//	Sphere s;
	//	//Matrix m = RayTracer::rotationY(DoubleHelpers::MATH_PI / 4);
	//	//m = m * RayTracer::scaling(1, 1, 0.5);
	//	//s.setTransform(m);
	//	double wallZ = 10;
	//	Tuple origin = RayTracer::point(0, 0, -5);
	//	double wallSize = ((wallZ - origin.z) / std::abs(origin.z)) * 2 + 1;
	//	double pixelSizeY = wallSize / height;
	//	double pixelSizeX = wallSize / height;
	//
	//	for (int y = 0; y < height; y++)
	//	{
	//		double worldY = (wallSize / 2) - (pixelSizeY * y);
	//		for (int x = 0; x < width; x++)
	//		{
	//			double worldX = -(wallSize / 2) + (pixelSizeX * x);
	//			Tuple wallPoint = RayTracer::point(worldX, worldY, wallZ);
	//			Tuple dir = (wallPoint - origin);
	//			dir.normalize();
	//			Ray ray(origin, dir);
	//			if (ray.getIntersection(s).count() > 0)
	//			{
	//				engine->Draw({ x, y }, olc::Pixel(0, 255, 0));
	//			}
	//			else
	//			{
	//				engine->Draw({ x, y }, olc::Pixel(0, 0, 0));
	//			}
	//		}
	//	}
	//}

	//void drawSpherebByRay(Canvas& canvas)
	//{
	//	int width = canvas.width;
	//	int height = canvas.height;
	//	Sphere s;
	//	s.material = Material();
	//	s.material.color = Color(0.25, 0.74, 0.96);
	//	s.material.shininess = 200;
	//	PointLight light(Color(1, 1, 1), RayTracer::point(0, 0, -10));
	//
	//	double wallZ = 10;
	//	Tuple origin = RayTracer::point(0, 0, -5);
	//	//double wallSize = ((wallZ - origin.z) / std::abs(origin.z)) * 2 + 1;
	//	double wallSize = 10;
	//	double pixelSizeY = wallSize / height;
	//	double pixelSizeX = wallSize /height;
	//	
	//	for (int y = 0; y < height; y++)
	//	{
	//		double worldY = (wallSize / 2) - (pixelSizeY * y);
	//		for (int x = 0; x < width; x++)
	//		{
	//			double worldX = -(wallSize / 2) + (pixelSizeX * x);
	//			Tuple wallPoint = RayTracer::point(worldX, worldY, wallZ);
	//			Tuple dir = (wallPoint - origin);
	//			dir.normalize();
	//			Ray ray(origin, dir);
	//			IntersectionList hits = ray.getIntersection(s);
	//			if (hits.count() > 0)
	//			{
	//				Intersection hit = hits.hit();
	//				Tuple hitPos = ray.getPosition(hit.i);
	//				Tuple normal = s.getNormal(hitPos);
	//				Tuple eyeDir = -ray.direction;
	//				Color pixelColor = getLighting(hit.object.material, light, hitPos, eyeDir, normal);
	//				int16_t colorR = pixelColor.red * 255;
	//				if (colorR > 255)
	//				{
	//					colorR = 255;
	//				}
	//
	//				int16_t colorG = pixelColor.green * 255;
	//				if (colorG > 255)
	//				{
	//					colorG = 255;
	//				}
	//
	//				int16_t colorB = pixelColor.blue * 255;
	//				if (colorB > 255)
	//				{
	//					colorB = 255;
	//				}
	//				canvas.writePixel(x, y, pixelColor);
	//			}
	//			else
	//			{
	//
	//			}
	//		}
	//	}
	//
	//	//std::ofstream file("sphere.ppm");
	//	//file << canvas.getPPM();
	//	//file.close();
	//}

	void drawDefaultScene(Canvas& image)
	{
		Sphere floor;
		floor.transform = scaling(20, 0.1, 20);
		floor.material.specular = 0;
		floor.material.diffuse = 0.67;
		floor.material.color = Color(1, 1, 1);

		Sphere leftWall;
		leftWall.transform = translation(0, 0, 8) *
			rotationY(-MATH_PI / 4.0) * rotationX(MATH_PI / 2.0) * scaling(20, 0.1, 20);
		leftWall.material = floor.material;

		Sphere rightWall;
		rightWall.transform = translation(0, 0, 8) *
			rotationY(MATH_PI / 4.0) * rotationX(MATH_PI / 2.0) * scaling(20, 0.1, 20);
		rightWall.material = floor.material;

		Sphere s1;
		s1.transform = translation(2, 1.6, 1) * scaling(1.5, 1.5, 1.5);
		s1.material.color = Color(0.25, 0.74, 0.96);

		Sphere s2;
		s2.transform = translation(-0.5, 2.9, -2) * scaling(0.35, 0.35, 0.35);
		s2.material.color = Color(0.34, 0.96, 0.26);

		Sphere s3;
		s3.transform = translation(-2.5, 1.15, 0) * scaling(1.1, 1.1, 1.1);
		s3.material.color = Color(0.96, 0.59, 0.26);

		World world;
		//world.lights.push_back(PointLight(Color(0.4, 0.4, 0.4), point(10, 10, -10)));
		world.lights.push_back(PointLight(Color(1, 1, 1), point(-7, 5, -10)));
		world.objects.push_back(&floor);
		world.objects.push_back(&leftWall);
		world.objects.push_back(&rightWall);
		world.objects.push_back(&s1);
		world.objects.push_back(&s2);
		world.objects.push_back(&s3);

		Camera camera(image.width, image.height, MATH_PI / 2);
		camera.transform = viewTransform(point(-0.5, 1.5, -5), point(0, 1.5, 5), vector(0, 1, 0));

		image = camera.render(world);
	}

	void drawDefaultScene2(Canvas& image)
	{
		Plane floor;
		floor.material.specular = 0;
		floor.material.diffuse = 1;
		floor.material.specular = 1;
		floor.material.color = Color(1, 1, 1);

		Sphere s1;
		s1.transform = translation(2, 1.6, 1) * scaling(1.5, 1.5, 1.5);
		s1.material.color = Color(0.25, 0.74, 0.96);


		Sphere s2;
		s2.transform = translation(-0.5, 2.9, -2) * scaling(0.35, 0.35, 0.35);
		s2.material.color = Color(0.34, 0.96, 0.26);

		Sphere s3;
		s3.transform = translation(-2.5, 1.15, 0) * scaling(1.1, 1.1, 1.1);
		s3.material.color = Color(0.96, 0.59, 0.26);

		World world;
		world.lights.push_back(PointLight(Color(1, 1, 1), point(-7, 5, -10)));
		world.objects.push_back(&floor);
		world.objects.push_back(&s1);
		world.objects.push_back(&s2);
		world.objects.push_back(&s3);

		Camera camera(image.width, image.height, MATH_PI / 2);
		camera.transform = viewTransform(point(-1, 2, -5), point(0, 1.5, 5), vector(0, 1, 0));

		image = camera.render(world);
	}

	void drawDefaultScene3(Canvas& image)
	{
		StripePattern pattern1(Color(0.25, 0.74, 0.96), Color(0.55, 0.84, 0.96));
		pattern1.setTransform(scaling(0.3, 0.3, 0.3) * rotationZ(DoubleHelpers::MATH_PI / 4));

		GradientPattern pattern2(Color(1.000, 0.600, 0.000), Color(1.000, 0.000, 0.000));
		pattern2.setTransform(scaling(0.4, 0.4, 0.4) * translation(1.5, 0, 0));

		RingPattern pattern3(Color(1.000, 0.600, 0.000), Color(1.000, 0.000, 0.000));
		pattern3.setTransform(rotationZ(DoubleHelpers::MATH_PI / 2.0) * scaling(0.2, 0.2, 0.2));


		Plane floor;
		floor.material.specular = 0;
		floor.material.diffuse = 1;
		floor.material.specular = 1;
		floor.material.color = Color(1, 1, 1);
		floor.material.pattern = &pattern3;

		Sphere s1;
		s1.transform = translation(2, 1.6, 1) * scaling(1.5, 1.5, 1.5);
		s1.material.color = Color(0.25, 0.74, 0.96);
		
		s1.material.pattern = &pattern1;

		Sphere s2;
		s2.transform = translation(-0.5, 2.9, -2) * scaling(0.35, 0.35, 0.35);
		s2.material.color = Color(0.34, 0.96, 0.26);
		s2.material.pattern = &pattern2;


		Sphere s3;
		s3.transform = translation(-2.5, 1.15, 0) * scaling(1.1, 1.1, 1.1);
		s3.material.color = Color(0.867, 0.000, 1.000);
		s3.material.pattern = &pattern3;


		World world;
		world.lights.push_back(PointLight(Color(1, 1, 1), point(-7, 5, -10)));
		world.objects.push_back(&floor);
		world.objects.push_back(&s1);
		world.objects.push_back(&s2);
		world.objects.push_back(&s3);

		Camera camera(image.width, image.height, MATH_PI / 3);
		camera.transform = viewTransform(point(-2, 2, -7), point(1, 1.5, 5), vector(0, 1, 0));

		image = camera.render(world);
	}

}