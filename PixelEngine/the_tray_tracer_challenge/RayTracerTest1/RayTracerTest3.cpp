#include "pch.h"
#include "CppUnitTest.h"
#include "../the_tray_tracer_challenge/matrix.h"
#include "../the_tray_tracer_challenge/tuple.h"
#include "../the_tray_tracer_challenge/DoubleHelpers.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using RayTracer::Matrix;
using RayTracer::Tuple;
using DoubleHelpers::isEqualDouble;

namespace RayTracerTest2
{
	TEST_CLASS(RayTracerTest2)
	{
	public:

		TEST_METHOD(TestMatrixCreate)
		{
			Logger::WriteMessage("Testing matrixCreate");
			Matrix matrix;
			matrix[0][0] = 1;
			matrix[0][1] = 2;
			matrix[0][2] = 3;
			matrix[0][3] = 4;
			matrix[1][0] = 5.5;
			matrix[1][1] = 6.5;
			matrix[1][2] = 7.5;
			matrix[1][3] = 8.5;
			matrix[2][0] = 9;
			matrix[2][1] = 10;
			matrix[2][2] = 11;
			matrix[2][3] = 12;
			matrix[3][0] = 13.5;
			matrix[3][1] = 14.5;
			matrix[3][2] = 15.5;
			matrix[3][3] = 16.6;

			Assert::IsTrue(isEqualDouble(1, matrix[0][0]));
			Assert::IsTrue(isEqualDouble(4, matrix[0][3]));
			Assert::IsTrue(isEqualDouble(5.5, matrix[1][0]));
			Assert::IsTrue(isEqualDouble(7.5, matrix[1][2]));
			Assert::IsTrue(isEqualDouble(11, matrix[2][2]));
			Assert::IsTrue(isEqualDouble(13.5, matrix[3][0]));
			Assert::IsTrue(isEqualDouble(15.5, matrix[3][2]));
		}

		TEST_METHOD(TestMatrixCreate2x2)
		{
			Logger::WriteMessage("Testing matrixCreate2x2");
			Matrix matrix(2, 2);
			matrix[0][0] = -3;
			matrix[0][1] = 5;
			matrix[1][0] = 1;
			matrix[1][1] = -2;

			Assert::IsTrue(isEqualDouble(-3, matrix[0][0]));
			Assert::IsTrue(isEqualDouble(5, matrix[0][1]));
			Assert::IsTrue(isEqualDouble(1, matrix[1][0]));
			Assert::IsTrue(isEqualDouble(-2, matrix[1][1]));
		}

		TEST_METHOD(TestMatrixCreate3x3)
		{
			Logger::WriteMessage("Testing matrixCreate3x3");
			Matrix matrix(3, 3);
			matrix[0][0] = -3;
			matrix[0][1] = 5;
			matrix[0][2] = 0;
			matrix[1][0] = 1;
			matrix[1][1] = -2;
			matrix[1][2] = -7;
			matrix[2][0] = 0;
			matrix[2][1] = 1;
			matrix[2][2] = 1;

			Assert::IsTrue(isEqualDouble(-3, matrix[0][0]));
			Assert::IsTrue(isEqualDouble(-2, matrix[1][1]));
			Assert::IsTrue(isEqualDouble(1, matrix[2][2]));
		}

		TEST_METHOD(TestEqualMatrix)
		{
			Logger::WriteMessage("Testing equalMatrix");
			Matrix matrix1;
			matrix1[0][0] = 1;
			matrix1[0][1] = 2;
			matrix1[0][2] = 3;
			matrix1[0][3] = 4;
			matrix1[1][0] = 5;
			matrix1[1][1] = 6;
			matrix1[1][2] = 7;
			matrix1[1][3] = 8;
			matrix1[2][0] = 9;
			matrix1[2][1] = 8;
			matrix1[2][2] = 7;
			matrix1[2][3] = 6;
			matrix1[3][0] = 5;
			matrix1[3][1] = 4;
			matrix1[3][2] = 3;
			matrix1[3][3] = 2;

			Matrix matrix2;
			matrix2[0][0] = 1;
			matrix2[0][1] = 2;
			matrix2[0][2] = 3;
			matrix2[0][3] = 4;
			matrix2[1][0] = 5;
			matrix2[1][1] = 6;
			matrix2[1][2] = 7;
			matrix2[1][3] = 8;
			matrix2[2][0] = 9;
			matrix2[2][1] = 8;
			matrix2[2][2] = 7;
			matrix2[2][3] = 6;
			matrix2[3][0] = 5;
			matrix2[3][1] = 4;
			matrix2[3][2] = 3;
			matrix2[3][3] = 2;

			Assert::IsTrue(matrix1 == matrix2);
		}

		TEST_METHOD(TestNotEqualMatrix)
		{
			Logger::WriteMessage("Testing notEqualMatrix");
			Matrix matrix1;
			matrix1[0][0] = 1;
			matrix1[0][1] = 2;
			matrix1[0][2] = 3;
			matrix1[0][3] = 4;
			matrix1[1][0] = 5;
			matrix1[1][1] = 6;
			matrix1[1][2] = 7;
			matrix1[1][3] = 8;
			matrix1[2][0] = 9;
			matrix1[2][1] = 8;
			matrix1[2][2] = 7;
			matrix1[2][3] = 6;
			matrix1[3][0] = 5;
			matrix1[3][1] = 4;
			matrix1[3][2] = 3;
			matrix1[3][3] = 2;

			Matrix matrix2;
			matrix2[0][0] = 2;
			matrix2[0][1] = 3;
			matrix2[0][2] = 4;
			matrix2[0][3] = 5;
			matrix2[1][0] = 6;
			matrix2[1][1] = 7;
			matrix2[1][2] = 8;
			matrix2[1][3] = 9;
			matrix2[2][0] = 8;
			matrix2[2][1] = 7;
			matrix2[2][2] = 6;
			matrix2[2][3] = 5;
			matrix2[3][0] = 4;
			matrix2[3][1] = 3;
			matrix2[3][2] = 2;
			matrix2[3][3] = 1;

			Assert::IsFalse(matrix1 == matrix2);
		}

		TEST_METHOD(TestMultiplyMatrix)
		{
			Logger::WriteMessage("Testing mulitplyMatrix");
			Matrix matrix1;
			matrix1[0][0] = 1;
			matrix1[0][1] = 2;
			matrix1[0][2] = 3;
			matrix1[0][3] = 4;
			matrix1[1][0] = 5;
			matrix1[1][1] = 6;
			matrix1[1][2] = 7;
			matrix1[1][3] = 8;
			matrix1[2][0] = 9;
			matrix1[2][1] = 8;
			matrix1[2][2] = 7;
			matrix1[2][3] = 6;
			matrix1[3][0] = 5;
			matrix1[3][1] = 4;
			matrix1[3][2] = 3;
			matrix1[3][3] = 2;

			Matrix matrix2;
			matrix2[0][0] = -2;
			matrix2[0][1] = 1;
			matrix2[0][2] = 2;
			matrix2[0][3] = 3;
			matrix2[1][0] = 3;
			matrix2[1][1] = 2;
			matrix2[1][2] = 1;
			matrix2[1][3] = -1;
			matrix2[2][0] = 4;
			matrix2[2][1] = 3;
			matrix2[2][2] = 6;
			matrix2[2][3] = 5;
			matrix2[3][0] = 1;
			matrix2[3][1] = 2;
			matrix2[3][2] = 7;
			matrix2[3][3] = 8;

			Matrix matrix3;
			matrix3[0][0] = 20;
			matrix3[0][1] = 20;
			matrix3[0][2] = 50;
			matrix3[0][3] = 48;
			matrix3[1][0] = 44;
			matrix3[1][1] = 54;
			matrix3[1][2] = 114;
			matrix3[1][3] = 108;
			matrix3[2][0] = 40;
			matrix3[2][1] = 58;
			matrix3[2][2] = 110;
			matrix3[2][3] = 102;
			matrix3[3][0] = 16;
			matrix3[3][1] = 26;
			matrix3[3][2] = 46;
			matrix3[3][3] = 42;

			Matrix prodMatrix = matrix1 * matrix2;
			Assert::IsTrue(prodMatrix == matrix3);
		}

		TEST_METHOD(TestMultiplyTuple)
		{
			Logger::WriteMessage("Testing mulitplyTuple");
			Matrix matrix;
			matrix[0][0] = 1;
			matrix[0][1] = 2;
			matrix[0][2] = 3;
			matrix[0][3] = 4;
			matrix[1][0] = 2;
			matrix[1][1] = 4;
			matrix[1][2] = 4;
			matrix[1][3] = 2;
			matrix[2][0] = 8;
			matrix[2][1] = 6;
			matrix[2][2] = 4;
			matrix[2][3] = 1;
			matrix[3][0] = 0;
			matrix[3][1] = 0;
			matrix[3][2] = 0;
			matrix[3][3] = 1;

			Tuple tuple(1, 2, 3, 1);

			Tuple prodTuple= matrix * tuple;
			Assert::IsTrue(prodTuple == Tuple(18, 24, 33, 1));
		}

		TEST_METHOD(TestMultiplyIdentityMatrix)
		{
			Logger::WriteMessage("Testing mulitplyIdentityMatrix");
			Matrix matrix;
			matrix[0][0] = 1;
			matrix[0][1] = 2;
			matrix[0][2] = 3;
			matrix[0][3] = 4;
			matrix[1][0] = 2;
			matrix[1][1] = 4;
			matrix[1][2] = 4;
			matrix[1][3] = 2;
			matrix[2][0] = 8;
			matrix[2][1] = 6;
			matrix[2][2] = 4;
			matrix[2][3] = 1;
			matrix[3][0] = 0;
			matrix[3][1] = 0;
			matrix[3][2] = 0;
			matrix[3][3] = 1;

			Matrix prodMatrix = matrix * Matrix::identityMatrix;

			Assert::IsTrue(prodMatrix == matrix);
		}

		TEST_METHOD(TestTranspose)
		{
			Logger::WriteMessage("Testing transpose");
			Matrix matrix;
			matrix[0][0] = 0;
			matrix[0][1] = 9;
			matrix[0][2] = 3;
			matrix[0][3] = 0;
			matrix[1][0] = 9;
			matrix[1][1] = 8;
			matrix[1][2] = 0;
			matrix[1][3] = 8;
			matrix[2][0] = 1;
			matrix[2][1] = 8;
			matrix[2][2] = 5;
			matrix[2][3] = 3;
			matrix[3][0] = 0;
			matrix[3][1] = 0;
			matrix[3][2] = 5;
			matrix[3][3] = 8;

			matrix.transpose();

			Matrix transposedMatrix;
			transposedMatrix[0][0] = 0;
			transposedMatrix[1][0] = 9;
			transposedMatrix[2][0] = 3;
			transposedMatrix[3][0] = 0;
			transposedMatrix[0][1] = 9;
			transposedMatrix[1][1] = 8;
			transposedMatrix[2][1] = 0;
			transposedMatrix[3][1] = 8;
			transposedMatrix[0][2] = 1;
			transposedMatrix[1][2] = 8;
			transposedMatrix[2][2] = 5;
			transposedMatrix[3][2] = 3;
			transposedMatrix[0][3] = 0;
			transposedMatrix[1][3] = 0;
			transposedMatrix[2][3] = 5;
			transposedMatrix[3][3] = 8;

			Assert::IsTrue(transposedMatrix == matrix);
		}

		TEST_METHOD(TestTransposeIdentityMatrix)
		{
			Logger::WriteMessage("Testing transposeIdentityMatrix");
			Matrix matrix = Matrix::identityMatrix;
			Matrix idMatrix = Matrix::identityMatrix;

			matrix.transpose();

			Assert::IsTrue(idMatrix == matrix);
		}

		TEST_METHOD(TestGetDeterminant2x2)
		{
			Logger::WriteMessage("Testing getDeterminant2x2");
			double values[] = { 1, 5, -3, 2 };
			Matrix matrix = Matrix(2, 2, values);

		
			Assert::IsTrue(isEqualDouble(17, matrix.getDeterminant()));
		}

		TEST_METHOD(TestGetSubMatrix3x3)
		{
			Logger::WriteMessage("Testing getSubMatrix3x3");
			double values[] = 
			{ 
				1, 5, 0,
				-3, 2, 7,
				0, 6, -3
			};
			Matrix matrix = Matrix(3, 3, values);

			double subValues[] =
			{
				-3, 2,
				0, 6
			};
			Matrix subMatrix = Matrix(2, 2, subValues);

			Assert::IsTrue(matrix.getSubMatrix(0, 2) == subMatrix);
		}

		TEST_METHOD(TestGetSubMatrix4x4)
		{
			Logger::WriteMessage("Testing getSubMatrix4x4");
			double values[] =
			{
				-6, 1, 1, 6,
				-8, 5, 8, 6,
				-1, 0, 8, 2,
				-7, 1, -1, 1
			};
			Matrix matrix = Matrix(4, 4, values);

			double subValues[] =
			{
				-6, 1, 6,
				-8, 8, 6,
				-7, -1, 1
			};
			Matrix subMatrix = Matrix(3,3, subValues);

			Assert::IsTrue(matrix.getSubMatrix(2, 1) == subMatrix);
		}

		TEST_METHOD(TestGetMinor3x3)
		{
			Logger::WriteMessage("Testing getMinor3x3");
			double values[] =
			{
				3, 5, 0,
				2, -1, -7,
				6, -1, 5
			};
			Matrix matrix = Matrix(3, 3, values);

			Matrix subMatrix = matrix.getSubMatrix(1, 0);

			Assert::IsTrue(isEqualDouble(subMatrix.getDeterminant(), 25));
			Assert::IsTrue(isEqualDouble(matrix.getMinor(1, 0), 25));
		}

		TEST_METHOD(TestGetCofactor3x3)
		{
			Logger::WriteMessage("Testing getCofactor3x3");
			double values[] =
			{
				3, 5, 0,
				2, -1, -7,
				6, -1, 5
			};
			Matrix matrix = Matrix(3, 3, values);

			Assert::IsTrue(isEqualDouble(matrix.getMinor(0, 0), -12));
			Assert::IsTrue(isEqualDouble(matrix.getCofactor(0, 0), -12));
			Assert::IsTrue(isEqualDouble(matrix.getMinor(1, 0), 25));
			Assert::IsTrue(isEqualDouble(matrix.getCofactor(1, 0), -25));
		}

		TEST_METHOD(TestGetDeterminant3x3)
		{
			Logger::WriteMessage("Testing getDeterminant3x3");
			double values[] =
			{
				1, 2, 6,
				-5, 8, -4,
				2, 6, 4
			};
			Matrix matrix = Matrix(3, 3, values);

			Assert::IsTrue(isEqualDouble(matrix.getCofactor(0, 0), 56));
			Assert::IsTrue(isEqualDouble(matrix.getCofactor(0, 1), 12));
			Assert::IsTrue(isEqualDouble(matrix.getCofactor(0, 2), -46));
			Assert::IsTrue(isEqualDouble(matrix.getDeterminant(), -196));
		}

		TEST_METHOD(TestGetDeterminant4x4)
		{
			Logger::WriteMessage("Testing getDeterminant4x4");
			double values[] =
			{
				-2, -8, 3, 5,
				-3, 1, 7, 3,
				1, 2, -9, 6,
				-6, 7, 7, -9
			};
			Matrix matrix = Matrix(4, 4, values);

			Assert::IsTrue(isEqualDouble(matrix.getCofactor(0, 0), 690));
			Assert::IsTrue(isEqualDouble(matrix.getCofactor(0, 1), 447));
			Assert::IsTrue(isEqualDouble(matrix.getCofactor(0, 2), 210));
			Assert::IsTrue(isEqualDouble(matrix.getCofactor(0, 3), 51));
			Assert::IsTrue(isEqualDouble(matrix.getDeterminant(), -4071));
		}

		TEST_METHOD(TestIsInvertable)
		{
			Logger::WriteMessage("Testing isInvertable");
			double values1[] =
			{
				6, 4, 4, 4,
				5, 5, 7, 6,
				4, -9, 3, -7,
				9, 1, 7, -6
			};
			Matrix matrix1 = Matrix(4, 4, values1);

			double values2[] =
			{
				-4, 2, -2, -3,
				9, 6, 2, 6,
				0, -5, 1, -5, 
				0, 0, 0, 0
			};
			Matrix matrix2 = Matrix(4, 4, values2);

			Assert::IsTrue(isEqualDouble(matrix1.getDeterminant(), -2120));
			Assert::IsTrue(matrix1.isInvertable());

			Assert::IsTrue(isEqualDouble(matrix2.getDeterminant(), 0));
			Assert::IsFalse(matrix2.isInvertable());
		}

		TEST_METHOD(TestgetInverse)
		{
			Logger::WriteMessage("Testing getInverse");
			double values1[] =
			{
				-5, 2, 6, -8,
				1, -5, 1, 8,
				7, 7, -6, -7,
				1, -3, 7, 4
			};
			Matrix matrix1 = Matrix(4, 4, values1);

			Matrix matrix2 = matrix1.getInverse();

			double inverseValues[] =
			{
				0.21805, 0.45113, 0.24060, -0.04511,
				-0.80827, -1.45677, -0.44361, 0.52068,
				-0.07895, -0.22368, -0.05263, 0.19737,
				-0.52256, -0.81391, -0.30075, 0.30639
			};
			Matrix inverseMatrixTest = Matrix(4, 4, inverseValues);

			Assert::IsTrue(isEqualDouble(matrix1.getDeterminant(), 532));
			Assert::IsTrue(isEqualDouble(matrix1.getCofactor(2, 3), -160));
			Assert::IsTrue(isEqualDouble(matrix2[3][2], (-160.0 / 532.0)));
			Assert::IsTrue(isEqualDouble(matrix1.getCofactor(3, 2), 105));
			Assert::IsTrue(isEqualDouble(matrix2[2][3], (105.0 / 532.0)));
			Assert::IsTrue(matrix2 == inverseMatrixTest);
		}

		TEST_METHOD(TestgetInverse2)
		{
			Logger::WriteMessage("Testing getInverse2");
			double values1[] =
			{
				8, -5, 9, 2,
				7, 5, 6, 1,
				-6, 0, 9, 6,
				-3, 0, -9, -4
			};
			Matrix matrix1 = Matrix(4, 4, values1);

			Matrix matrix2 = matrix1.getInverse();

			double inverseValues[] =
			{
				-0.15385, -0.15385, -0.28205, -0.53846,
				-0.07692, 0.12308, 0.02564, 0.03077,
				0.35897, 0.35897, 0.43590, 0.92308,
				-0.69231, -0.69231, -0.76923, -1.92308
			};
			Matrix inverseMatrixTest = Matrix(4, 4, inverseValues);
			Assert::IsTrue(matrix2 == inverseMatrixTest);
		}

		TEST_METHOD(TestgetInverse3)
		{
			Logger::WriteMessage("Testing getInverse3");
			double values1[] =
			{
				9, 3, 0, 9,
				-5, -2, -6, -3, 
				-4, 9, 6, 4, 
				-7, 6, 6, 2
			};
			Matrix matrix1 = Matrix(4, 4, values1);

			Matrix matrix2 = matrix1.getInverse();

			double inverseValues[] =
			{
				-0.04074, -0.07778, 0.14444, -0.22222,
				-0.07778, 0.03333, 0.36667, -0.33333,
				-0.02901, -0.14630, -0.10926, 0.12963,
				0.17778, 0.06667, -0.26667, 0.33333
			};
			Matrix inverseMatrixTest = Matrix(4, 4, inverseValues);
			Assert::IsTrue(matrix2 == inverseMatrixTest);
		}

		TEST_METHOD(TestReverseTransform)
		{
			Logger::WriteMessage("Testing reverseTransform");
			double values1[] =
			{
				3, -9, 7, 3,
				3, -8, 2, -9,
				-4, 4, 4, 1,
				-6, 5, -1, 1
			};
			Matrix matrix1 = Matrix(4, 4, values1);

			double values2[] =
			{
				3, -9, 7, 3,
				3, -8, 2, -9,
				-4, 4, 4, 1, 
				-6, 5, -1, 1
			};
			Matrix matrix2 = Matrix(4, 4, values2);

			Matrix matrix3 = matrix1 * matrix2;

			Assert::IsTrue(matrix1 == (matrix3 * matrix2.getInverse()));
		}
	};
}