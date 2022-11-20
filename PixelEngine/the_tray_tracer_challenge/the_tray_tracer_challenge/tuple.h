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
		double getMagnitudeSquared();
		Tuple getNormalized();
		void normalize();
		double dotProduct(Tuple const& tuple);
		//double dotProduct(Tuple tuple);
		double dotProduct(Tuple const& tuple) const;
		//double dotProduct(Tuple tuple) const;
		Tuple crossProduct(Tuple const& tuple);

		// Operators
		Tuple operator+(Tuple const& tuple);
		Tuple operator-(Tuple const& tuple);
		friend Tuple operator- (Tuple const& t1, Tuple const& t2);
		friend bool operator== (Tuple const& t1, Tuple const& t2);
		Tuple operator-();
		//Tuple operator*(double n);
		friend Tuple operator* (Tuple const& t1, double n);
		//friend Tuple operator* (Tuple t1, double n);
		Tuple operator/(double n);
	};

	Tuple point(double x, double y, double z);
	Tuple vector(double x, double y, double z);
}