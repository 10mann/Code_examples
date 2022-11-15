#pragma once

#include "tuple.h"

namespace RayTracer
{
	class Matrix
	{
	public:

		// Variables
		int rows = 4;
		int cols = 4;
		double m[4][4];

		static Matrix const identityMatrix;


		// Constructors
		Matrix();
		Matrix(int rows, int cols);
		Matrix(int r, int c, double p[16]);
		Matrix(double a, double b, double c, double d);

		// Methods
		void print(void);
		void transpose(void);
		double getDeterminant(void);
		Matrix getSubMatrix(int row, int col);
		double getMinor(int row, int col);
		double getCofactor(int row, int col);
		bool isInvertable(void);
		Matrix getInverse(void);

		// Operators
		double* operator[](int index);
		bool operator==(Matrix const& matrix);
		Matrix operator*(Matrix const& matrix);
		Tuple operator*(Tuple const& tuple);
	};
}