#pragma once

#include "canvas.h"

namespace RayTracer
{
	//void drawSpherebByRay(Canvas& canvas);
	void drawDefaultScene(Canvas& image);
	void drawDefaultScene2(Canvas& image);
	void drawDefaultScene3(Canvas& image);
	void drawDefaultScene4(Canvas& image);

	void drawMarbleMadness(Canvas& image);

	void drawDefaultRefractionScene1(Canvas& image);

	void drawSphereGrid(Canvas& image);

	void drawCubeScene1(Canvas& image);
	void drawCubeScene2(Canvas& image);
	void drawCubeScene3(Canvas& image);
	void drawCubeScene4(Canvas& image);

	void drawCylinderScene1(Canvas& image);
	void drawCylinderScene2(Canvas& image);

	void drawConeScene1(Canvas& image);
	void drawConeScene2(Canvas& image);

	void drawGroupScene1(Canvas& image);
}
