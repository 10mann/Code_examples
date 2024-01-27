#include "color.h"

#include "DoubleHelpers.h"

#include <iostream>

namespace RayTracer
{
	using DoubleHelpers::isEqualDouble;

	Color const Color::White(1, 1, 1);
	Color const Color::Black(0, 0, 0);

	// ============================ Constructors ============================
	Color::Color()
		:red(0.0), green(0.0), blue(0.0), alpha(0.0)
	{

	}

	Color::Color(double r, double g, double b, double a)
		:red(r), green(g), blue(b), alpha(a)
	{

	}


	// ============================ Methods ============================


	// ============================ Operators ============================
	Color Color::operator+(Color const& color)
	{
		return Color(red + color.red, green + color.green, blue + color.blue, alpha + color.alpha);
	}

	Color Color::operator-(Color const& color)
	{
		return Color(red - color.red, green - color.green, blue - color.blue, alpha - color.alpha);
	}

	Color& Color::operator+=(Color const& color)
	{
		red += color.red; 
		green += color.green;
		blue += color.blue;
		alpha += color.alpha;
		return *this;
	}

	bool operator==(Color const& c1, Color const& c2)
	{
		return ((isEqualDouble(c1.red, c2.red)) &&
			(isEqualDouble(c1.green, c2.green)) &&
			(isEqualDouble(c1.blue, c2.blue)));
	}

	Color& Color::operator*(double n)
	{
		red *= n;
		green *= n;
		blue *= n;
		return *this;
		//return Color(red * n, green * n, blue * n);
	}

	Color operator*(Color const& c1, double n)
	{
		return Color(c1.red * n, c1.green * n, c1.blue * n);
	}

	Color RayTracer::Color::operator*(Color color)
	{
		return Color(red * color.red, green * color.green, blue * color.blue);
	}

	Color RayTracer::operator*(Color const& c1, Color const& c2)
	{
		return Color(c1.red * c2.red, c1.green * c2.green, c1.blue * c2.blue);
	}

	void Color::print() const
	{
		std::cout << "(" << red << ", " << green << ", " << blue << ")";
	}
}