#pragma once

#include "tuple.h"
#include "canvas.h"
#include "color.h"
#include "matrix.h"
#include "DoubleHelpers.h"
#include "ray.h"
#include "sphere.h"
#include "intersection.h"
#include "intersection_list.h"
#include "material.h"
#include "point_light.h"
#include "world.h"
#include "camera.h"
#include "cube.h"

#include <iostream>
#include <chrono>
#include <fstream>


namespace RayTracer
{
	void benchmarkMatrixMult(void);
	long long benchmarkDrawSphere(int iterations);
	long long benchmarkMatrixMult(int iterations);
	long long benchmarkGetDistance(int iterations);
	long long benchmarkIsInShadow(int iterations);
	long long benchmarkGetInverse(int iterations);
	long long benchmarkGetSubMatrix(int iterations);
	long long benchmarkCompareCubeIntersect(int iterations);
}