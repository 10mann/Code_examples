#include "group.h"

#include <algorithm>
#include <iostream>

namespace RayTracer
{
	// ========================= Constructors ==========================
	Group::Group()
	{
	}

	// ============================ Methods ============================
	Tuple Group::getLocalNormal(Tuple point)
	{
		std::cout << "Calling getNormal on group object\n";
		return Tuple();
	}

	std::vector<Shape::ObjectHit> Group::getIntersectTime(Ray& ray)
	{
		std::vector<ObjectHit> intersectTimes;
		Ray transformedRay = ray.transform(invTransform);
		if (true == mBbox.intersects(transformedRay))
		{
			for (const auto s : objects)
			{
				std::vector<ObjectHit> shapeIntersectTimes;
				s->getIntersectTime(transformedRay, shapeIntersectTimes);
				for (const auto t : shapeIntersectTimes)
				{
					intersectTimes.push_back(t);
				}
			}

			std::sort(intersectTimes.begin(), intersectTimes.end(), [](ObjectHit x, ObjectHit y) {return x.i < y.i; });
		}

		return intersectTimes;
	}

	void Group::getIntersectTime(Ray& ray, std::vector<Shape::ObjectHit>& intersectTimes)
	{
		Ray transformedRay = ray;

		if (parent == nullptr)
		{
			//ray.transformed(invTransform);
			transformedRay = ray.transform(invTransform);
		}

		//if (mBbox.intersects(ray))
		if (mBbox.intersects(transformedRay))
		{
			for (auto& s : objects)
			{
				std::vector<ObjectHit> shapeIntersectTimes;
				s->getIntersectTime(transformedRay, shapeIntersectTimes);
				//s->getIntersectTime(ray, shapeIntersectTimes);
				for (auto t : shapeIntersectTimes)
				{
					intersectTimes.push_back(t);
				}
			}

			std::sort(intersectTimes.begin(), intersectTimes.end(), [](ObjectHit x, ObjectHit y) { return x.i < y.i; });
		}
	}

	void Group::getIntersections(Ray ray, std::vector<Shape::ObjectHit>& intersectTimes)
	{
		if (parent == nullptr)
		{
			ray.transformed(invTransform);
			//transformedRay = ray.transform(invTransform);
		}

		//if (mBbox.intersects(transformedRay))
		if (mBbox.hits(ray))
		{
			for (auto& s : objects)
			{
				std::vector<ObjectHit> shapeIntersectTimes;
				//s->getIntersectTime(transformedRay, shapeIntersectTimes);
				s->getIntersections(ray, shapeIntersectTimes);
				for (auto const& t : shapeIntersectTimes)
				{
					intersectTimes.push_back(t);
				}
			}

			std::sort(intersectTimes.begin(), intersectTimes.end(), [](ObjectHit x, ObjectHit y) { return x.i < y.i; });
		}
	}

	BoundingBox Group::getBoundingBox(void)
	{
		return mBbox;
	}

	void Group::addChild(Shape* child)
	{
		objects.push_back(child);
		child->parent = this;
	}

	void Group::removeChild(Shape* child)
	{
		for(int i = 0; i < objects.size(); i++)
		{
			if (objects[i] == child)
			{
				objects.erase(objects.begin() + i);
				break;
			}
		}
	}

	void Group::calculateBoundingBox(void)
	{
		mBbox = BoundingBox();

		for (auto& o : objects)
		{
			mBbox.addBox(o->getBoundingBox());
		}

		mBbox.setTransform(transform);
	}

	void Group::partitionChildren(std::vector<std::vector<Shape*>>& partitions)
	{
		std::vector<Shape*> left;
		std::vector<Shape*> right;
		std::vector<Shape*> rest;
		std::vector<BoundingBox> boxes;
		boxes.reserve(2);
		mBbox.splitBounds(boxes);
		BoundingBox bbox;
		left.reserve(objects.size() / 2);
		right.reserve(objects.size() / 2);
		rest.reserve(objects.size() / 2);

		for (auto& obj : objects)
		{
			bbox = obj->getBoundingBox();
			if (boxes[0].containsBox(bbox))
			{
				left.emplace_back(obj);
			}
			else if (boxes[1].containsBox(bbox))
			{
				right.emplace_back(obj);
			}
			else
			{
				rest.emplace_back(obj);
			}
		}

		if ((left.size() > 0) || (right.size() > 0))
		{
			objects.clear();

			if (left.size() > 0)
			{
				partitions.emplace_back(left);
			}

			if (right.size() > 0)
			{
				partitions.emplace_back(right);
			}
		}

		//objects.clear();

		//partitions.push_back(left);
		//partitions.push_back(right);
		if (rest.size() > 0)
		{
			partitions.emplace_back(rest);
		}
	}

	void Group::makeSubGroup(const std::vector<Shape*>& children)
	{
		subGroups.emplace_back(std::make_unique<Group>());
		for (const auto& c : children)
		{
			subGroups[subGroups.size() - 1]->addChild(c);
		}

		addChild(subGroups[subGroups.size() - 1].get());
	}

	void Group::divide(int threshold)
	{
		if (objects.size() > threshold)
		{
			calculateBoundingBox();
			std::vector<std::vector<Shape*>> list;
			partitionChildren(list);

			for (auto& group : list)
			{
				if (group.size() > 0)
				{
					makeSubGroup(group);
				}
			}
		}

		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->divide(threshold);
		}
	}

	// =========================== Operators ===========================
	bool Group::operator==(Shape const& s1)
	{
		return false;
	}

	// ============================ Helpers =============================
}