#pragma once

namespace RayTracer
{
	class Tuple
	{
		// Variables
	public:
		double x;
		double y;
		double z;
		double w;

		// Constructors
		Tuple();
		Tuple(double x, double y, double z, double w);

		// Methods
		void print(void);
		bool isPoint(void);
		bool isVector(void);
		bool isEqual(Tuple const& tuple);
		double getMagnitude();
		Tuple getNormalized();
		void normalize();
		double dotProduct(Tuple const& tuple);
		Tuple crossProduct(Tuple const& tuple);

		// Operators
		Tuple operator+(Tuple const& tuple);
		Tuple operator-(Tuple const& tuple);
		friend bool operator== (Tuple const& t1, Tuple const& t2);
		Tuple operator-();
		Tuple operator*(double n);
		Tuple operator/(double n);
	};

	Tuple point(double x, double y, double z);
	Tuple vector(double x, double y, double z);
}