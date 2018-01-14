#include "stdafx.h"
#include "CppUnitTest.h"

#include "../SDLFramework/Linal/matrix.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Matrixtest
{		

	TEST_CLASS(Matrixes)
	{
	public:

		TEST_METHOD(CorrectSizeInitialization)
		{
			auto matrix = Linal::Matrix<double>{ 2, 3 };

			Assert::AreEqual(3, matrix.GetWidth());
			Assert::AreEqual(2, matrix.GetHeight());
		}

		TEST_METHOD(ValuesCorresponds)
		{
			auto matrix = Linal::Matrix<double>{ 3, 3 };

			matrix.Set(1, 1, 1).Set(2, 1, 2).Set(3, 1, 3);
			matrix.Set(1, 2, 4).Set(2, 2, 5).Set(3, 2, 6);
			matrix.Set(1, 3, 7).Set(2, 3, 8).Set(3, 3, 9);

			Assert::AreEqual((double) 1, matrix.Get(1, 1));
			Assert::AreEqual((double) 2, matrix.Get(2, 1));
			Assert::AreEqual((double) 3, matrix.Get(3, 1));
			Assert::AreEqual((double) 4, matrix.Get(1, 2));
			Assert::AreEqual((double) 5, matrix.Get(2, 2));
			Assert::AreEqual((double) 6, matrix.Get(3, 2));
			Assert::AreEqual((double) 7, matrix.Get(1, 3));
			Assert::AreEqual((double) 8, matrix.Get(2, 3));
			Assert::AreEqual((double) 9, matrix.Get(3, 3));
		}

		TEST_METHOD(CanAddHelpLine)
		{
			auto matrix = Linal::Matrix<double>{ 3, 3 };

			matrix = Linal::Matrix<double>::AddHelpLine(matrix);

			Assert::AreEqual(3, matrix.GetWidth());
			Assert::AreEqual(4, matrix.GetHeight());
		}

		TEST_METHOD(Multiple)
		{
			auto lhs = Linal::Matrix<double>{ 2, 2 };
			auto rhs = Linal::Matrix<double>{ 2, 2 };

			lhs.Set(1, 1, 4).Set(1, 2, 1);
			lhs.Set(2, 1, 2).Set(2, 2, 3);

			rhs.Set(1, 1, 3).Set(1, 2, 0);
			rhs.Set(2, 1, 2).Set(2, 2, 5);

			auto multiplied = lhs * rhs;

			Assert::AreEqual(2, multiplied.GetWidth());
			Assert::AreEqual(2, multiplied.GetHeight());

			Assert::AreEqual((double) 14, multiplied.Get(1, 1));
			Assert::AreEqual((double)  5, multiplied.Get(1, 2));
			Assert::AreEqual((double) 12, multiplied.Get(2, 1));
			Assert::AreEqual((double) 15, multiplied.Get(2, 2));
		}
	};
}