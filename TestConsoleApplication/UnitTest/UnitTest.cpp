#include "pch.h"

#include <memory>

#include "CppUnitTest.h"

#include "../TestConsoleApplication/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(TestVector)
	{
	public:
		
		TEST_METHOD(CreationTest)
		{
			double expected_x = 1.0,
				   expected_y = 2.0,
				   expected_z = 3.0;

			Vector3D actual(1.0, 2.0, 3.0);
			Assert::IsTrue(actual.x() == expected_x &&
						   actual.y() == expected_y &&
						   actual.z() == expected_z);
		}
		
		TEST_METHOD(NormaTest)
		{
			double expected_norma = sqrt(14);
			double actual = Vector3D(1.0, 2.0, 3.0).norma();
			Assert::IsTrue(abs(actual - expected_norma) < 1e-16);
		}
		
		TEST_METHOD(EqualityTest)
		{
			Vector3D expected(-11.0, 10.0, -3.0);
			Vector3D actual(-11.0, 10.0, -3.0);
			bool status = expected == actual;
			Assert::IsTrue(status);
		}
		
		TEST_METHOD(DifferenceTest)
		{
			Vector3D expected(-2.0, 2.0, 4.0);

			Vector3D v1(4.0, 1.0, 3.0);
			Vector3D v2(2.0, 3.0, 7.0);

			Vector3D actual = v2 - v1;
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(CrossTest)
		{
			Vector3D expected(-11.0, 10.0, -3.0);
			
			Vector3D v1(1.0, 2.0, 3.0);
			Vector3D v2(4.0, 5.0, 2.0);

			Vector3D actual = cross(v1, v2);
			Assert::IsTrue(expected == actual);
		}
		
		TEST_METHOD(IsZeroTrue)
		{
			Vector3D v(0.0, 0.0, 0.0);
			Assert::IsTrue(v.is_zero());
		}
		
		TEST_METHOD(IsZeroFalse)
		{
			Vector3D v(1e-10, 1e-14, 1e-20);
			Assert::IsFalse(v.is_zero());
		}
	};


	TEST_CLASS(TestSegment)
	{

		TEST_METHOD(SegmentedVectorTest)
		{
			Vector3D expected(-2.0, 2.0, 4.0);

			Vector3D actual = Segment3D(Vector3D(4.0, 1.0, 3.0),
										Vector3D(2.0, 3.0, 7.0))
										.get_segmented_vector();

			Assert::IsTrue(expected == actual);
		}
	};

	TEST_CLASS(IntersectTests)
	{
		TEST_METHOD(TestDependentParallelVectors)
		{
			ResultStatus expected = ResultStatus::Parallel;

			Segment3D s1(Vector3D(1.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0))
					, s2(Vector3D(1.5, 1.0, 2.0), Vector3D(2.5, 1.0, 2.0));

			decltype(auto) actual = intersection_checker(s1, s2);
			Assert::IsTrue(expected == actual.status());
		}

		TEST_METHOD(TestDependentOnLineVectorsNoIntersection)
		{
			ResultStatus expected = ResultStatus::NoIntersection;

			Segment3D s1(Vector3D(1.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0))
					, s2(Vector3D(3.0, 0.0, 0.0), Vector3D(4.0, 0.0, 0.0));

			decltype(auto) actual = intersection_checker(s1, s2);
			Assert::IsTrue(expected == actual.status());
		}

		TEST_METHOD(TestDependentOnLineVectorsIntersectionCase1)
		{
			Vector3D expected(2.0, 0.0, 0.0);

			Segment3D s1(Vector3D(1.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0))
					, s2(Vector3D(2.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0));

			decltype(auto) actual = intersection_checker(s1, s2);
			Assert::IsTrue(expected == actual.value());
		}

		TEST_METHOD(TestDependentOnLineVectorsIntersectionCase2)
		{
			Vector3D expected(2.0, 0.0, 0.0);

			Segment3D s1(Vector3D(1.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0))
					, s2(Vector3D(3.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0));

			decltype(auto) actual = intersection_checker(s1, s2);
			Assert::IsTrue(expected == actual.value());
		}

		TEST_METHOD(TestDependentOnLineVectorsIntersectionCase3)
		{
			Vector3D expected(2.0, 0.0, 0.0);

			Segment3D s1(Vector3D(2.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s2(Vector3D(3.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0));

			decltype(auto) actual = intersection_checker(s1, s2);
			Assert::IsTrue(expected == actual.value());
		}

		TEST_METHOD(TestDependentOnLineVectorsIntersectionCase4)
		{
			Vector3D expected(2.0, 0.0, 0.0);

			Segment3D s1(Vector3D(2.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s2(Vector3D(2.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0));

			decltype(auto) actual = intersection_checker(s1, s2);
			Assert::IsTrue(expected == actual.value());
		}
	};
}
