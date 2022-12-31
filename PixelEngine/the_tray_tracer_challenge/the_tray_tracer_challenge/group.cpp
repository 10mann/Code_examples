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
		if (true == mBbox.intersects(ray))
		{
			for (const auto s : objects)
			{
				std::vector<ObjectHit> shapeIntersectTimes = s->getIntersectTime(transformedRay);
				for (const auto t : shapeIntersectTimes)
				{
					intersectTimes.push_back(t);
				}
			}

			std::sort(intersectTimes.begin(), intersectTimes.end(), [](ObjectHit x, ObjectHit y) {return x.i < y.i; });
		}

		return intersectTimes;
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

	std::vector<std::vector<Shape*>> Group::partitionChildren(void)
	{
		std::vector<Shape*> left;
		std::vector<Shape*> right;
		std::vector<std::vector<Shape*>> partitions;
		std::vector<BoundingBox> boxes = mBbox.splitBounds();

		for (int i = 0; i < objects.size(); i++)
		{
			if (true == boxes[0].containsBox(objects[i]->getBoundingBox()))
			{
				left.push_back(objects[i]);
			}
			else if (true == boxes[1].containsBox(objects[i]->getBoundingBox()))
			{
				right.push_back(objects[i]);
			}
		}

		for (const auto& o : left)
		{
			removeChild(o);
		}

		for (const auto& o : right)
		{
			removeChild(o);
		}

		partitions.push_back(left);
		partitions.push_back(right);

		return partitions;
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
		if (objects.size() >= threshold)
		{
			calculateBoundingBox();
			std::vector<std::vector<Shape*>> list = partitionChildren();
			if (list[0].size() > 0)
			{
				makeSubGroup(list[0]);
			}

			if (list[1].size() > 0)
			{
				makeSubGroup(list[1]);
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