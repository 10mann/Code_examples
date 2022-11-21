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
		Matrix getTranspose(void);
		double getDeterminant(void);
		Matrix getSubMatrix(int row, int col);
		double getMinor(int row, int col);
		double getCofactor(int row, int col);
		bool isInvertable(void);
		Matrix getInverse(void);

		// Operators
		double* operator[](int index);
		friend bool operator== (Matrix const& m1, Matrix const& m2);
		//bool operator==(Matrix& matrix);
		//Matrix operator*(Matrix const& matrix);
		//friend Matrix operator* (const Matrix& m1, const Matrix& m2);
		friend Matrix operator* (Matrix m1, Matrix m2);
		Tuple operator*(Tuple const& tuple);
		friend Tuple operator* (Matrix const& m, Tuple const& tuple);
	};

	Matrix translation(double x, double y, double z);
	Matrix scaling(double x, double y, double z);
	Matrix rotationX(double rotation);
	Matrix rotationY(double rotation);
	Matrix rotationZ(double rotation);
	Matrix shearing(double xY, double xZ, double yX, double yZ, double zX, double zY);
	Matrix viewTransform(Tuple from, Tuple to, Tuple up);
}