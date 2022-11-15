#pragma once

namespace RayTracer
{
	class Color
	{
	public:
		// Variables
		double red;
		double green;
		double blue;
		double alpha;

		// Constructors
		Color();
		Color(double r, double g, double b, double a=0.0);

		// Methods

		// Operators
		Color operator+(Color const& color);
		Color operator-(Color const& color);
		friend bool operator== (Color const& c1, Color const& c2);
		Color operator*(double n);
		Color operator*(Color color);
		void print();
	};
}