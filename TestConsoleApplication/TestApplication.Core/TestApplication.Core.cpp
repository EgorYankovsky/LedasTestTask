#include "pch.h"

auto
Intersect(const Segment3D& s1, const Segment3D& s2) -> Vector3D {
    Vector3D solution;
    try {

        decltype(auto) v1 = s1.get_segmented_vector();
        decltype(auto) v2 = s2.get_segmented_vector();

        std::unique_ptr<ISolution> solver = nullptr;

        // На вход попались точки (вектор, порожденный сегментом, чья норма пренебрежительно мала).
        if (v1.norma() <= _eps && v2.norma() <= _eps)
            solver = std::make_unique<PointAndPointSolution>();
        // На вход попалась одна точка.
        else if (v1.norma() <= _eps || v2.norma() <= _eps)
            solver = std::make_unique<PointAndLineSolution>();

        decltype(auto) cross_result = cross(v1, v2);
        if (cross_result.is_zero() && solver == nullptr) // Векторы колинеарны.
            solver = std::make_unique<CollinearityLinesSolution>();
        else // Векторы как минимум скрещиваются.
            solver = std::make_unique<IntersectingLinesSolution>();

        if (solver == nullptr) throw std::exception("Solver wasn't selected.");
        decltype(auto) solution_result = solver->solve(s1, s2);

        if (solution_result.status() == ResultStatus::Intersection ||
            solution_result.status() == ResultStatus::Infinite) {
            solution = solution_result.value();
        }
        else {
            std::cout << solution_result.message() << std::endl;
            solution = empty_vector;
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Unexpected error: " << ex.what() << std::endl;
        solution = empty_vector;
    }
    return solution;
}