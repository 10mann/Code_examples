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

#include <iostream>
#include <chrono>
#include <fstream>


void benchmarkMatrixMult(void);
long long benchmarkDrawSphere(int iterations);