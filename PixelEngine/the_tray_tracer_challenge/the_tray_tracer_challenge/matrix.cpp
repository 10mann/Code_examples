#include "matrix.h"
#include "DoubleHelpers.h"

#include <iostream>
#include <cmath>

namespace RayTracer
{
	using DoubleHelpers::isEqualDouble;
	static double identityValues[] = 
	{
		1, 0, 0, 0, 
		0, 1, 0, 0, 
		0, 0, 1, 0, 
		0, 0, 0, 1
	};

	Matrix const Matrix::identityMatrix = Matrix(4, 4, identityValues);

	// ============================ Constructors ============================
	Matrix::Matrix()
		:rows(4), cols(4)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				m[i][j] = 0;
			}
		}
	}

	Matrix::Matrix(int rows, int cols)
		:rows(rows), cols(cols)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				m[i][j] = 0;
			}
		}
	}

	Matrix::Matrix(int r, int c, double p[16])
	{
		rows = r;
		cols = c;

		for (int y = 0; y < rows; y++)
		{
			for (int x = 0; x < cols; x++)
			{
				m[y][x] = p[x + cols * y];
			}
		}
	}

	Matrix::Matrix(double a, double b, double c, double d)
	{
		rows = 2;
		cols = 2;

		m[0][0] = a;
		m[0][1] = b;
		m[1][0] = c;
		m[1][1] = d;
	}

	// ============================ Methods ============================
	void Matrix::print(void)
	{
		for (int i = 0; i < rows; i++)
		{
			std::cout << "|";
			for (int j = 0; j < cols; j++)
			{
				std::cout << "\t" << m[i][j] << "\t|";
			}
			std::cout << std::endl;
		}
	}

	void Matrix::transpose(void)
	{
		for (int y = 0; y < rows; y++)
		{
			for (int x = y; x < cols; x++)
			{
				double temp = m[y][x];
				m[y][x] = m[x][y];
				m[x][y] = temp;
			}
		}
	}

	Matrix Matrix::getTranspose(void)
	{
		Matrix m = *this;
		m.transpose();
		return m;
	}

	double Matrix::getDeterminant(void)
	{
		double det = 0;

		switch (rows)
		{
		case 2:
		{
			det = (m[0][0] * m[1][1]) - (m[1][0] * m[0][1]);
			break;
		}

		case 3:
		{
			det = (m[0][0] * ((m[1][1] * m[2][2]) - (m[2][1] * m[1][2]))) -
				(m[0][1] * ((m[1][0] * m[2][2]) - (m[2][0] * m[1][2]))) + 
				(m[0][2] * ((m[1][0] * m[2][1]) - (m[2][0] * m[1][1])));
			break;
		}

		case 4:
		{
			det = (m[0][0] * getSubMatrix(0, 0).getDeterminant()) -
				(m[0][1] * getSubMatrix(0, 1).getDeterminant()) +
				(m[0][2] * getSubMatrix(0, 2).getDeterminant()) -
				(m[0][3] * getSubMatrix(0, 3).getDeterminant());
			break;
		}

		default:
		{
			for (int i = 0; i < rows; i++)
			{
				det += m[0][i] * this->getCofactor(0, i);
			}
			break;
		}
		}

		return det;
	}

	Matrix Matrix::getSubMatrix(int row, int col)
	{
		Matrix matrix = *this;
		matrix.rows = rows - 1;
		matrix.cols = cols - 1;

		for (int i = row; i < matrix.rows; i++)
		{
			matrix.m[i][0] = matrix.m[i + 1][0];
			matrix.m[i][1] = matrix.m[i + 1][1];
			matrix.m[i][2] = matrix.m[i + 1][2];
			matrix.m[i][3] = matrix.m[i + 1][3];
		}

		for (int i = col; i < matrix.cols; i++)
		{
			matrix.m[0][i] = matrix.m[0][i + 1];
			matrix.m[1][i] = matrix.m[1][i + 1];
			matrix.m[2][i] = matrix.m[2][i + 1];
			matrix.m[3][i] = matrix.m[3][i + 1];
		}

		return matrix;
	}

	double Matrix::getMinor(int row, int col)
	{
		return this->getSubMatrix(row, col).getDeterminant();
	}

	double Matrix::getCofactor(int row, int col)
	{
		return this->getMinor(row, col) * (((row + col) % 2) ? -1 : 1);
	}

	bool Matrix::isInvertable(void)
	{
		return !isEqualDouble(0, this->getDeterminant());
	}

	Matrix Matrix::getInverse(void)
	{
		Matrix coMatrix;

		double determinant = this->getDeterminant();

		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < cols; col++)
			{
				coMatrix[col][row] = this->getCofactor(row, col) / determinant;
			}
		}

		return coMatrix;
	}

	// ============================ Operators ============================
	double* Matrix::operator[](int index)
	{
		double* ret = nullptr;
		if (index < rows)
		{
			ret = m[index];
		}

		return ret;
	}

	bool operator==(Matrix const m1, Matrix const m2)
	{
		bool ret = true;
		for (int i = 0; i < m1.rows; i++)
		{
			for (int j = 0; j < m1.cols; j++)
			{
				ret = isEqualDouble(m1.m[i][j], m2.m[i][j]);
				if (false == ret)
				{
					break;
				}
			}
		}
		return ret;
	}

	Matrix operator*(Matrix m1, Matrix m2)
	{
		Matrix prodMatrix;
		for (int i = 0; i < m1.rows; i++)
		{
			prodMatrix[i][0] =
				m1.m[i][0] * m2.m[0][0] +
				m1.m[i][1] * m2.m[1][0] +
				m1.m[i][2] * m2.m[2][0] +
				m1.m[i][3] * m2.m[3][0];

			prodMatrix[i][1] =
				m1.m[i][0] * m2.m[0][1] +
				m1.m[i][1] * m2.m[1][1] +
				m1.m[i][2] * m2.m[2][1] +
				m1.m[i][3] * m2.m[3][1];

			prodMatrix[i][2] =
				m1.m[i][0] * m2.m[0][2] +
				m1.m[i][1] * m2.m[1][2] +
				m1.m[i][2] * m2.m[2][2] +
				m1.m[i][3] * m2.m[3][2];

			prodMatrix[i][3] =
				m1.m[i][0] * m2.m[0][3] +
				m1.m[i][1] * m2.m[1][3] +
				m1.m[i][2] * m2.m[2][3] +
				m1.m[i][3] * m2.m[3][3];
		}

		return prodMatrix;
	}

	Tuple operator*(Matrix const& m, Tuple const& tuple)
	{
		double x =
			m.m[0][0] * tuple.x +
			m.m[0][1] * tuple.y +
			m.m[0][2] * tuple.z +
			m.m[0][3] * tuple.w;

		double y =
			m.m[1][0] * tuple.x +
			m.m[1][1] * tuple.y +
			m.m[1][2] * tuple.z +
			m.m[1][3] * tuple.w;

		double z =
			m.m[2][0] * tuple.x +
			m.m[2][1] * tuple.y +
			m.m[2][2] * tuple.z +
			m.m[2][3] * tuple.w;

		double w =
			m.m[3][0] * tuple.x +
			m.m[3][1] * tuple.y +
			m.m[3][2] * tuple.z +
			m.m[3][3] * tuple.w;

		return Tuple(x, y, z, w);
	}

	Tuple operator*(Matrix m, Tuple& tuple)
	{
		double x =
			m.m[0][0] * tuple.x +
			m.m[0][1] * tuple.y +
			m.m[0][2] * tuple.z +
			m.m[0][3] * tuple.w;

		double y =
			m.m[1][0] * tuple.x +
			m.m[1][1] * tuple.y +
			m.m[1][2] * tuple.z +
			m.m[1][3] * tuple.w;

		double z =
			m.m[2][0] * tuple.x +
			m.m[2][1] * tuple.y +
			m.m[2][2] * tuple.z +
			m.m[2][3] * tuple.w;

		double w =
			m.m[3][0] * tuple.x +
			m.m[3][1] * tuple.y +
			m.m[3][2] * tuple.z +
			m.m[3][3] * tuple.w;

		return Tuple(x, y, z, w);
	}



	Matrix translation(double x, double y, double z)
	{
		Matrix transformMatrix = Matrix::identityMatrix;
		transformMatrix[0][3] = x;
		transformMatrix[1][3] = y;
		transformMatrix[2][3] = z;

		return transformMatrix;
	}

	Matrix scaling(double x, double y, double z)
	{
		Matrix transformMatrix = Matrix::identityMatrix;
		transformMatrix[0][0] = x;
		transformMatrix[1][1] = y;
		transformMatrix[2][2] = z;

		return transformMatrix;
	}

	Matrix rotationX(double rotation)
	{
		Matrix rotationMatrix = Matrix::identityMatrix;
		rotationMatrix[1][1] = cos(rotation);
		rotationMatrix[2][2] = cos(rotation);
		rotationMatrix[2][1] = sin(rotation);
		rotationMatrix[1][2] = -sin(rotation);
		return rotationMatrix;
	}

	Matrix rotationY(double rotation)
	{
		Matrix rotationMatrix = Matrix::identityMatrix;
		rotationMatrix[0][0] = cos(rotation);
		rotationMatrix[2][2] = cos(rotation);
		rotationMatrix[0][2] = sin(rotation);
		rotationMatrix[2][0] = -sin(rotation);
		return rotationMatrix;
	}

	Matrix rotationZ(double rotation)
	{
		Matrix rotationMatrix = Matrix::identityMatrix;
		rotationMatrix[0][0] = cos(rotation);
		rotationMatrix[1][1] = cos(rotation);
		rotationMatrix[1][0] = sin(rotation);
		rotationMatrix[0][1] = -sin(rotation);
		return rotationMatrix;
	}

	Matrix shearing(double xY, double xZ, double yX, double yZ, double zX, double zY)
	{
		Matrix shearingMatrix = Matrix::identityMatrix;
		shearingMatrix[0][1] = xY;
		shearingMatrix[0][2] = xZ;
		shearingMatrix[1][0] = yX;
		shearingMatrix[1][2] = yZ;
		shearingMatrix[2][0] = zX;
		shearingMatrix[2][1] = zY;
		return shearingMatrix;
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

		Matrix viewMatrix = Matrix(4, 4, values) * translation(-from.x, -from.y, -from.z);

		return viewMatrix;
	}
}