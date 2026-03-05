#include <memory>

#include "CppUnitTest.h"

#include "Include/Segment3D.h"
#include "Include/Solutions.h"
#include "framework.h"

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

	TEST_CLASS(TestPointAndPointSolution)
	{
		std::unique_ptr<ISolution> solver;

		TEST_METHOD_INITIALIZE(TestPointAndPointSolutionInit)
		{
			solver = std::make_unique<PointAndPointSolution>();
		}

		TEST_METHOD(TestPointsIntersection)
		{
			Vector3D expected(3.0, 2.0, 1.0);

			Segment3D s1(Vector3D(3.0, 2.0, 1.0), Vector3D(3.0, 2.0, 1.0))
					, s2(Vector3D(3.0, 2.0, 1.0), Vector3D(3.0, 2.0, 1.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			if (solution_result.status() != ResultStatus::Intersection) Assert::Fail();
			decltype(auto) actual = solution_result.value();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestPointsNoIntersection)
		{
			ResultStatus expected = ResultStatus::NoIntersection;

			Segment3D s1(Vector3D(3.0, 2.0, 1.0), Vector3D(3.0, 2.0, 1.0))
					, s2(Vector3D(3.0, 3.0, 3.0), Vector3D(3.0, 3.0, 3.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}
	};

	TEST_CLASS(TestPointAndLineSolution)
	{
		std::unique_ptr<ISolution> solver;

		TEST_METHOD_INITIALIZE(TestPointAndLineSolutionInit)
		{
			solver = std::make_unique<PointAndLineSolution>();
		}

		TEST_METHOD(TestPointAndLineIntersection)
		{
			Vector3D expected(3.0, 2.0, 1.0);

			Segment3D s1(Vector3D(3.0, 2.0, 1.0), Vector3D(3.0, 2.0, 1.0))
					, s2(Vector3D(2.0, 4.0, 0.0), Vector3D(4.0, 0.0, 2.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			if (solution_result.status() != ResultStatus::Intersection) Assert::Fail();
			decltype(auto) actual = solution_result.value();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestPointAndLineOutOfRangeIntersection)
		{
			ResultStatus expected = ResultStatus::NoIntersection;

			Segment3D s1(Vector3D(5.0, -2.0, 3.0), Vector3D(5.0, -2.0, 3.0))
					, s2(Vector3D(2.0, 4.0, 0.0), Vector3D(4.0, 0.0, 2.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestPointAndLineIntersectionAtStart)
		{
			Vector3D expected(2.0, 4.0, 0.0);

			Segment3D s1(Vector3D(2.0, 4.0, 0.0), Vector3D(2.0, 4.0, 0.0))
					, s2(Vector3D(2.0, 4.0, 0.0), Vector3D(4.0, 0.0, 2.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			if (solution_result.status() != ResultStatus::Intersection) Assert::Fail();
			decltype(auto) actual = solution_result.value();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestPointAndLineIntersectionAtEnd)
		{
			Vector3D expected(4.0, 0.0, 2.0);

			Segment3D s1(Vector3D(4.0, 0.0, 2.0), Vector3D(4.0, 0.0, 2.0))
					, s2(Vector3D(2.0, 4.0, 0.0), Vector3D(4.0, 0.0, 2.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			if (solution_result.status() != ResultStatus::Intersection) Assert::Fail();
			decltype(auto) actual = solution_result.value();
			Assert::IsTrue(expected == actual);
		}
		TEST_METHOD(TestPointAndLineNoIntersection)
		{
			ResultStatus expected = ResultStatus::NoIntersection;

			Segment3D s1(Vector3D(3.0, 2.0, 1.0), Vector3D(3.0, 2.0, 1.0))
					, s2(Vector3D(3.0, 3.0, 3.0), Vector3D(4.0, 4.0, 4.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}
	};
	
	TEST_CLASS(TestCollinearityLinesSolution)
	{
		std::unique_ptr<ISolution> solver;

		TEST_METHOD_INITIALIZE(TestPointAndLineSolutionInit)
		{
			solver = std::make_unique<CollinearityLinesSolution>();
		}

		TEST_METHOD(TestParallelLinesCase1)
		{
			ResultStatus expected = ResultStatus::Parallel;

			Segment3D s1(Vector3D(0.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s2(Vector3D(0.0, 1.0, 0.0), Vector3D(1.0, 1.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestParallelLinesCase2)
		{
			ResultStatus expected = ResultStatus::Parallel;

			Segment3D s1(Vector3D(0.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s2(Vector3D(1.0, 1.0, 0.0), Vector3D(0.0, 1.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestParallelLinesCase3)
		{
			ResultStatus expected = ResultStatus::Parallel;

			Segment3D s1(Vector3D(1.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0))
					, s2(Vector3D(0.0, 1.0, 0.0), Vector3D(1.0, 1.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestParallelLinesCase4)
		{
			ResultStatus expected = ResultStatus::Parallel;

			Segment3D s1(Vector3D(1.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0))
					, s2(Vector3D(1.0, 1.0, 0.0), Vector3D(0.0, 1.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionCase1)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s1(Vector3D(0.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0))
					, s2(Vector3D(1.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionCase2)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s1(Vector3D(0.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0))
					, s2(Vector3D(3.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionCase3)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s1(Vector3D(2.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s2(Vector3D(1.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionCase4)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s1(Vector3D(2.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s2(Vector3D(3.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionCase5)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s2(Vector3D(0.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0))
					, s1(Vector3D(1.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionCase6)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s2(Vector3D(0.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0))
					, s1(Vector3D(3.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionCase7)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s2(Vector3D(2.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s1(Vector3D(1.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionCase8)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s2(Vector3D(2.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s1(Vector3D(3.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}
	
		TEST_METHOD(TestNoIntersectionCase1)
		{
			ResultStatus expected = ResultStatus::NoIntersection;

			Segment3D s1(Vector3D(1.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0))
					, s2(Vector3D(3.0, 0.0, 0.0), Vector3D(4.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}
		
		TEST_METHOD(TestNoIntersectionCase2)
		{
			ResultStatus expected = ResultStatus::NoIntersection;

			Segment3D s1(Vector3D(1.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0))
					, s2(Vector3D(4.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}
		
		TEST_METHOD(TestNoIntersectionCase3)
		{
			ResultStatus expected = ResultStatus::NoIntersection;

			Segment3D s1(Vector3D(2.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s2(Vector3D(3.0, 0.0, 0.0), Vector3D(4.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}
		
		TEST_METHOD(TestNoIntersectionCase4)
		{
			ResultStatus expected = ResultStatus::NoIntersection;

			Segment3D s1(Vector3D(2.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s2(Vector3D(4.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestNoIntersectionCase5)
		{
			ResultStatus expected = ResultStatus::NoIntersection;

			Segment3D s2(Vector3D(1.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0))
					, s1(Vector3D(3.0, 0.0, 0.0), Vector3D(4.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}
		
		TEST_METHOD(TestNoIntersectionCase6)
		{
			ResultStatus expected = ResultStatus::NoIntersection;

			Segment3D s2(Vector3D(1.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0))
					, s1(Vector3D(4.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}
		
		TEST_METHOD(TestNoIntersectionCase7)
		{
			ResultStatus expected = ResultStatus::NoIntersection;

			Segment3D s2(Vector3D(2.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s1(Vector3D(3.0, 0.0, 0.0), Vector3D(4.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}
		
		TEST_METHOD(TestNoIntersectionCase8)
		{
			ResultStatus expected = ResultStatus::NoIntersection;

			Segment3D s2(Vector3D(2.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s1(Vector3D(4.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestOnlySolutionIntersectionCase1)
		{
			Vector3D expected(1.0, 0.0, 0.0);

			Segment3D s1(Vector3D(0.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s2(Vector3D(1.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			if (solution_result.status() != ResultStatus::Intersection) Assert::Fail();
			decltype(auto) actual = solution_result.value();
			Assert::IsTrue(expected == actual);
		}
		
		TEST_METHOD(TestOnlySolutionIntersectionCase2)
		{
			Vector3D expected(1.0, 0.0, 0.0);

			Segment3D s1(Vector3D(0.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s2(Vector3D(2.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			if (solution_result.status() != ResultStatus::Intersection) Assert::Fail();
			decltype(auto) actual = solution_result.value();
			Assert::IsTrue(expected == actual);
		}
		
		TEST_METHOD(TestOnlySolutionIntersectionCase3)
		{
			Vector3D expected(1.0, 0.0, 0.0);

			Segment3D s1(Vector3D(1.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0))
					, s2(Vector3D(1.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			if (solution_result.status() != ResultStatus::Intersection) Assert::Fail();
			decltype(auto) actual = solution_result.value();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestOnlySolutionIntersectionCase4)
		{
			Vector3D expected(1.0, 0.0, 0.0);

			Segment3D s1(Vector3D(1.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0))
					, s2(Vector3D(2.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			if (solution_result.status() != ResultStatus::Intersection) Assert::Fail();
			decltype(auto) actual = solution_result.value();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestOnlySolutionIntersectionCase5)
		{
			Vector3D expected(1.0, 0.0, 0.0);

			Segment3D s2(Vector3D(0.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s1(Vector3D(1.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			if (solution_result.status() != ResultStatus::Intersection) Assert::Fail();
			decltype(auto) actual = solution_result.value();
			Assert::IsTrue(expected == actual);
		}
		
		TEST_METHOD(TestOnlySolutionIntersectionCase6)
		{
			Vector3D expected(1.0, 0.0, 0.0);

			Segment3D s2(Vector3D(0.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s1(Vector3D(2.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			if (solution_result.status() != ResultStatus::Intersection) Assert::Fail();
			decltype(auto) actual = solution_result.value();
			Assert::IsTrue(expected == actual);
		}
		
		TEST_METHOD(TestOnlySolutionIntersectionCase7)
		{
			Vector3D expected(1.0, 0.0, 0.0);

			Segment3D s2(Vector3D(1.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0))
					, s1(Vector3D(1.0, 0.0, 0.0), Vector3D(2.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			if (solution_result.status() != ResultStatus::Intersection) Assert::Fail();
			decltype(auto) actual = solution_result.value();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestOnlySolutionIntersectionCase8)
		{
			Vector3D expected(1.0, 0.0, 0.0);

			Segment3D s2(Vector3D(1.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0))
					, s1(Vector3D(2.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			if (solution_result.status() != ResultStatus::Intersection) Assert::Fail();
			decltype(auto) actual = solution_result.value();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionSameLineCase1)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s1(Vector3D(1.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0))
					, s2(Vector3D(1.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionSameLineCase2)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s1(Vector3D(3.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s2(Vector3D(1.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionSameLineCase3)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s1(Vector3D(1.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0))
					, s2(Vector3D(3.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionSameLineCase4)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s1(Vector3D(3.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s2(Vector3D(3.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionSameLineCase5)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s2(Vector3D(1.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0))
					, s1(Vector3D(1.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionSameLineCase6)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s2(Vector3D(3.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s1(Vector3D(1.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionSameLineCase7)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s2(Vector3D(1.0, 0.0, 0.0), Vector3D(3.0, 0.0, 0.0))
					, s1(Vector3D(3.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestInfiniteIntersectionSameLineCase8)
		{
			ResultStatus expected = ResultStatus::Infinite;

			Segment3D s2(Vector3D(3.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0))
					, s1(Vector3D(3.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}
	
	};

	TEST_CLASS(TestIntersectingLinesSolution)
	{
		std::unique_ptr<ISolution> solver;

		TEST_METHOD_INITIALIZE(TestPointAndLineSolutionInit)
		{
			solver = std::make_unique<IntersectingLinesSolution>();
		}

		TEST_METHOD(TestIntersection)
		{
			Vector3D expected(3.0, 2.0, 5.0);

			Segment3D s1(Vector3D(4.0, 1.0, 3.0), Vector3D(2.0, 3.0, 7.0))
					, s2(Vector3D(3.0, 0.0, 0.0), Vector3D(3.0, 4.0, 10.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			if (solution_result.status() != ResultStatus::Intersection) Assert::Fail();
			decltype(auto) actual = solution_result.value();
			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(TestNoIntersection)
		{
			ResultStatus expected = ResultStatus::NoIntersection;

			Segment3D s1(Vector3D(4.0, 1.0, 3.0), Vector3D(2.0, 3.0, 7.0))
					, s2(Vector3D(3.0, 0.0, 0.0), Vector3D(3.0, 8.0, 10.0));

			decltype(auto) solution_result = solver->solve(s1, s2);
			decltype(auto) actual = solution_result.status();
			Assert::IsTrue(expected == actual);
		}
	};

}
