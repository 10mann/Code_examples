#include "canvas.h"

#include <iostream>

namespace RayTracer
{
	Canvas::Canvas()
	{
		width = 0;
		height = 0;
	}

	Canvas::Canvas(int width, int height, Color color)
	{
		this->width = width;
		this->height = height;
		this->index = 0;
		this->segment_width = 1;

		this->pixels = std::vector<Color>(width * height, color);
	}


	void Canvas::writePixel(int x, int y, Color color)
	{
		int index = x + (y * width);
		if (index < pixels.size())
		{
			pixels[index] = color;
		}
	}

	Color Canvas::getPixel(int x, int y)
	{
		return pixels[x + (y * width)];
	}

	std::string Canvas::getPPM()
	{
		std::string ppmStr("P3\n");
		ppmStr.append(std::to_string(width));
		ppmStr.append(" ");
		ppmStr.append(std::to_string(height));
		ppmStr.append("\n");
		ppmStr.append(std::to_string(255));

		int lineLength = 0;
		for (int y = 0; y < height; y++)
		{
			ppmStr.append("\n");
			lineLength = 0;
			for (int x = 0; x < width; x++)
			{
				Color color = pixels[x + (y * width)];
				int red = (int)((color.red * 255) + 0.5);
				red = (red > 255) ? 255 : red;
				red = (red < 0) ? 0 : red;

				int green = (int)((color.green * 255) + 0.5);
				green = (green > 255) ? 255 : green;
				green = (green < 0) ? 0 : green;

				int blue = (int)((color.blue * 255) + 0.5);
				blue = (blue > 255) ? 255 : blue;
				blue = (blue < 0) ? 0 : blue;

				std::string redStr = std::to_string(red);
				if ((lineLength + redStr.size()) >= MAX_LINE_LENGTH)
				{
					lineLength = 0;
					ppmStr.append("\n");
				}
				ppmStr.append(redStr);
				lineLength += redStr.size();
				
				std::string greenStr = std::to_string(green);
				if ((lineLength + greenStr.size()) >= MAX_LINE_LENGTH)
				{
					lineLength = 0;
					ppmStr.append("\n");
				}
				else
				{
					ppmStr.append(" ");
					lineLength++;
				}
				ppmStr.append(greenStr);
				lineLength += greenStr.size();

				std::string blueStr = std::to_string(blue);
				if ((lineLength + blueStr.size()) >= MAX_LINE_LENGTH)
				{
					lineLength = 0;
					ppmStr.append("\n");
				}		
				else
				{
					ppmStr.append(" ");
					lineLength++;
				}
				ppmStr.append(blueStr);
				lineLength += blueStr.size();

				if (((lineLength + 1) < MAX_LINE_LENGTH) && (x < (width - 1)))
				{
					ppmStr.append(" ");
					lineLength++;
				}
			}
		}
		ppmStr.append("\n");

		return ppmStr;
	}

	int Canvas::getNextIndex()
	{
		int index = this->index;
		this->index += segment_width;
		return index;
	}

	void Canvas::print()
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				pixels[x + y * width].print();
				std::cout << ", ";
			}
			std::cout << std::endl;
		}
	}
}