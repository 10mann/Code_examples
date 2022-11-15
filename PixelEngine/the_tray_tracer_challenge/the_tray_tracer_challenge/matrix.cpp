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

	double Matrix::getDeterminant(void)
	{
		double det = 0;

		if (rows > 2)
		{
			for (int i = 0; i < rows; i++)
			{
				det += m[0][i] * this->getCofactor(0, i);
			}
		}
		else
		{
			det = (m[0][0] * m[1][1]) - (m[1][0] * m[0][1]);
		}

		return det;
	}

	Matrix Matrix::getSubMatrix(int row, int col)
	{
		Matrix matrix;
		matrix.rows = rows - 1;
		matrix.cols = cols - 1;
		int rowIndex = 0;
		int colIndex = 0;

		for (int y = 0; y < rows; y++)
		{
			if (y != row)
			{
				colIndex = 0;
				for (int x = 0; x < cols; x++)
				{
					if ((x != col))
					{
						matrix[rowIndex][colIndex] = m[y][x];
						colIndex++;
					}
				}
				rowIndex++;
			}
		}

		return matrix;
	}

	double Matrix::getMinor(int row, int col)
	{
		return this->getSubMatrix(row, col).getDeterminant();
	}

	double Matrix::getCofactor(int row, int col)
	{
		double minor = this->getMinor(row, col);
		if (((row + col) % 2) != 0)
		{
			minor *= -1;
		}

		return minor;
	}

	bool Matrix::isInvertable(void)
	{
		return !isEqualDouble(0, this->getDeterminant());
	}

	Matrix RayTracer::Matrix::getInverse(void)
	{
		Matrix coMatrix;

		if (this->isInvertable())
		{
			double determinant = this->getDeterminant();

			for (int row = 0; row < rows; row++)
			{
				for (int col = 0; col < cols; col++)
				{
					coMatrix[col][row] = this->getCofactor(row, col) / determinant;
				}
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

	bool Matrix::operator==(Matrix const& matrix)
	{
		bool ret = true;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				ret = isEqualDouble(m[i][j], matrix.m[i][j]);
				if (false == ret)
				{
					break;
				}
			}
		}
		return ret;
	}

	Matrix Matrix::operator*(Matrix const& matrix)
	{
		Matrix prodMatrix;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				prodMatrix[i][j] =
					m[i][0] * matrix.m[0][j] +
					m[i][1] * matrix.m[1][j] +
					m[i][2] * matrix.m[2][j] +
					m[i][3] * matrix.m[3][j];
			}
		}

		return prodMatrix;
	}

	Tuple Matrix::operator*(Tuple const& tuple)
	{
		double x =
			m[0][0] * tuple.x +
			m[0][1] * tuple.y +
			m[0][2] * tuple.z +
			m[0][3] * tuple.w;

		double y =
			m[1][0] * tuple.x +
			m[1][1] * tuple.y +
			m[1][2] * tuple.z +
			m[1][3] * tuple.w;

		double z =
			m[2][0] * tuple.x +
			m[2][1] * tuple.y +
			m[2][2] * tuple.z +
			m[2][3] * tuple.w;

		double w =
			m[3][0] * tuple.x +
			m[3][1] * tuple.y +
			m[3][2] * tuple.z +
			m[3][3] * tuple.w;

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
}