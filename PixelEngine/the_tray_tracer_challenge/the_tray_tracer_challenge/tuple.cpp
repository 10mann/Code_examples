#include "tuple.h"

#include "DoubleHelpers.h"

#include <iostream>
#include <cmath>

namespace RayTracer
{
	using DoubleHelpers::isEqualDouble;

	// ============================ Constructors ============================
	Tuple::Tuple()
		: x(0.0), y(0.0), z(0.0), w(1.0)
	{

	}

	Tuple::Tuple(double x, double y, double z, double w)
	:	 x(x), y(y), z(z), w(w)
	{

	}


	// ============================ Methods ============================
	void Tuple::print(void)
	{
		std::cout << "(" << x << ", " << y << ", " << z << ", " << w << ")" << std::endl;
	}

	bool Tuple::isPoint(void)
	{
		return isEqualDouble(w, 1.0);;
	}

	bool Tuple::isVector(void)
	{
		return isEqualDouble(w, 0.0);
	}

	bool Tuple::isEqual(Tuple const& tuple)
	{
		return ((isEqualDouble(x, tuple.x)) && 
			(isEqualDouble(y, tuple.y)) && 
			(isEqualDouble(z, tuple.z)) && 
			isEqualDouble(w, tuple.w));
	}

	double RayTracer::Tuple::getMagnitude()
	{
		return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}

	Tuple RayTracer::Tuple::getNormalized()
	{
		return (*this) / this->getMagnitude();
	}

	void RayTracer::Tuple::normalize()
	{
		(*this) = (*this) / this->getMagnitude();
	}

	double RayTracer::Tuple::dotProduct(Tuple const& tuple)
	{
		return ((x * tuple.x) + (y * tuple.y) + (z * tuple.z) + (w * tuple.w));
	}

	Tuple RayTracer::Tuple::crossProduct(Tuple const& tuple)
	{
		return Tuple(
			(y * tuple.z) - (tuple.y * z), 
			(z * tuple.x) - (tuple.z * x), 
			(x * tuple.y) - (tuple.x * y), 
			0.0);
	}


	// ============================ Operators ============================
	Tuple Tuple::operator+(Tuple const& tuple)
	{
		return Tuple(x + tuple.x, y + tuple.y, z + tuple.z, w + tuple.w);
	}

	Tuple Tuple::operator-(Tuple const& tuple)
	{
		return Tuple(x - tuple.x, y - tuple.y, z - tuple.z, w - tuple.w);
	}

	bool RayTracer::operator==(Tuple const& t1, Tuple const& t2)
	{
		return ((isEqualDouble(t1.x, t2.x)) &&
			(isEqualDouble(t1.y, t2.y)) &&
			(isEqualDouble(t1.z, t2.z)) &&
			isEqualDouble(t1.w, t2.w));
	}

	Tuple Tuple::operator-()
	{
		return Tuple(-x, -y, -z, -w);
	}

	Tuple Tuple::operator*(double n)
	{
		return Tuple(x * n, y * n, z * n, w * n);
	}

	Tuple RayTracer::Tuple::operator/(double n)
	{
		return Tuple(x / n, y / n, z / n, w / n);
	}

	Tuple point(double x, double y, double z)
	{
		return Tuple(x, y, z, 1.0);
	}

	Tuple vector(double x, double y, double z)
	{
		return Tuple(x, y, z, 0.0);
	}
}