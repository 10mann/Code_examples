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

	double Tuple::getMagnitude()
	{
		return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}

	double Tuple::getMagnitudeSquared()
	{
		return (x * x) + (y * y) + (z * z) + (w * w);
	}

	Tuple Tuple::getNormalized()
	{
		return (*this) / (std::sqrt((x * x) + (y * y) + (z * z) + (w * w)));
	}

	void Tuple::normalize()
	{
		(*this) = (*this) / this->getMagnitude();
	}

	double Tuple::dotProduct(Tuple const& tuple)
	{
		return ((x * tuple.x) + (y * tuple.y) + (z * tuple.z) + (w * tuple.w));
	}

	double RayTracer::Tuple::dotProduct(Tuple const& tuple) const
	{
		return ((x * tuple.x) + (y * tuple.y) + (z * tuple.z) + (w * tuple.w));
	}

	Tuple Tuple::crossProduct(Tuple const& tuple)
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

	Tuple operator-(Tuple const& t1, Tuple const& t2)
	{
		return Tuple(t1.x - t2.x, t1.y - t2.y, t1.z - t2.z, t1.w - t2.w);
	}

	bool operator==(Tuple const t1, Tuple const t2)
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

	Tuple operator*(Tuple const& t1, double n)
	{
		return Tuple(t1.x * n, t1.y * n, t1.z * n, t1.w * n);
	}

	Tuple Tuple::operator/(double n)
	{
		return Tuple(x / n, y / n, z / n, w / n);
	}

	Tuple& Tuple::operator*(Matrix const& m)
	{
			double x =
				m.m[0][0] * this->x +
				m.m[0][1] * this->y +
				m.m[0][2] * this->z +
				m.m[0][3] * this->w;

			double y =
				m.m[1][0] * this->x +
				m.m[1][1] * this->y +
				m.m[1][2] * this->z +
				m.m[1][3] * this->w;

			double z =
				m.m[2][0] * this->x +
				m.m[2][1] * this->y +
				m.m[2][2] * this->z +
				m.m[2][3] * this->w;

			double w =
				m.m[3][0] * this->x +
				m.m[3][1] * this->y +
				m.m[3][2] * this->z +
				m.m[3][3] * this->w;

			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;

			return *this;
	}

	Tuple& Tuple::operator*=(Matrix const& m)
	{
		double x =
			m.m[0][0] * this->x +
			m.m[0][1] * this->y +
			m.m[0][2] * this->z +
			m.m[0][3] * this->w;

		double y =
			m.m[1][0] * this->x +
			m.m[1][1] * this->y +
			m.m[1][2] * this->z +
			m.m[1][3] * this->w;

		double z =
			m.m[2][0] * this->x +
			m.m[2][1] * this->y +
			m.m[2][2] * this->z +
			m.m[2][3] * this->w;

		double w =
			m.m[3][0] * this->x +
			m.m[3][1] * this->y +
			m.m[3][2] * this->z +
			m.m[3][3] * this->w;

		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;

		return *this;
	}

	Tuple point(double x, double y, double z)
	{
		return Tuple(x, y, z, 1.0);
	}

	Tuple vector(double x, double y, double z)
	{
		return Tuple(x, y, z, 0.0);
	}

	Matrix viewTransform(Tuple from, Tuple to, Tuple up)
	{
		Tuple forward = (to - from).getNormalized();
		Tuple left = forward.crossProduct(up.getNormalized());
		Tuple trueUp = forward.crossProduct(left);
		double values[] =
		{
			left.x, left.y, left.z, 0,
			trueUp.x, trueUp.y, trueUp.z, 0,
			-forward.x, -forward.y, -forward.z, 0,
			0, 0, 0, 1
		};

		return Matrix(4, 4, values) * translation(-from.x, -from.y, -from.z);
	}
}