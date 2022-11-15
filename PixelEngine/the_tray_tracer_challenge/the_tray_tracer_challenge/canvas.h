#pragma once

#include "color.h"

#include <vector>
#include <string>

namespace RayTracer
{
	constexpr int MAX_LINE_LENGTH = 70;
	class Canvas
	{
	public:
		// Variables
		int width;
		int height;

		std::vector<Color> pixels;

		// Constructors
		Canvas();
		Canvas(int width, int height, Color color = Color(0, 0, 0));

		// Methods
		void writePixel(int x, int y, Color color);
		Color getPixel(int x, int y);
		std::string getPPM();
		
		void print();
	};
}