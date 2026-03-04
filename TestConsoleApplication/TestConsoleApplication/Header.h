#pragma once

#include <iostream>
#include <iomanip>

#include "Include/Segment3D.h"
#include "Include/Result.h"
#include "Include/ParametricFunction.h"

using matrix2x2 = std::array<std::array<double, 2>, 2>;
using vector2 = std::array<double, 2>;

const std::string no_solution_msg = "No solution.";
const Vector3D empty_vector = Vector3D(NAN, NAN, NAN);

auto Intersect(const Segment3D&, const Segment3D&) -> Vector3D;


auto find_partial_solution(const Segment3D& s1, const Segment3D& s2) -> Result<Vector3D> {
    decltype(auto) v1 = s1.get_segmented_vector();
    decltype(auto) c = s2.start() - s1.start();
    decltype(auto) cr = cross(c, v1);
    if (cr.is_zero()) {
        // Векторы лежат на одной прямой.
        if (s1.end() == s2.start())        return Result<Vector3D>::success(s2.start(), ResultStatus::Intersection);
        else if (s2.end() == s1.start())   return Result<Vector3D>::success(s1.start(), ResultStatus::Intersection);
        else if (s1.end() == s2.end())     return Result<Vector3D>::success(s2.end(), ResultStatus::Intersection);
        else if (s1.start() == s2.start()) return Result<Vector3D>::success(s2.start(), ResultStatus::Intersection);
        return Result<Vector3D>::failure(no_solution_msg, ResultStatus::NoIntersection);
    }
    else {
        // Векторы не лежат на одной прямой.
        return Result<Vector3D>::failure(no_solution_msg, ResultStatus::Parallel);
    }
}

auto operator* (const matrix2x2& m, const vector2& v) -> vector2 {
    return vector2{ m[0][0]*v[0] + m[0][1]*v[1],
                    m[1][0]*v[0] + m[1][1]*v[1]};
}

auto intersection_checker(const Segment3D& s1, const Segment3D& s2) -> Result<Vector3D> {
    ParametricFunction f1(s1);
    ParametricFunction f2(s2);

    // Шаг 1. Проверить линейную зависимость между векторами, образуемыми в сегментах.
    decltype(auto) v1 = s1.get_segmented_vector();
    decltype(auto) v2 = s2.get_segmented_vector();
    decltype(auto) cross_result = cross(v1, v2);
    if (cross_result.is_zero()) // Векторы зависимы.
        return find_partial_solution(s1, s2);

    // Шаг 2. Находим минимальное расстояние.
    Vector3D delt(s2.start().x() - s1.start().x(),
                  s2.start().y() - s1.start().y(),
                  s2.start().z() - s1.start().z());

    matrix2x2 A = { {{-1.0 * (v1 * v1), v1 * v2}
                   , {-1.0 * (v1 * v2), v2 * v2}}};    
    vector2 b = { -1.0 * (v1 * delt),
                  -1.0 * (v2 * delt) };

    double detA = A[0][0] * A[1][1] - A[0][1] * A[1][0];
    matrix2x2 A_1 = { {{ A[1][1] / detA,  -A[0][1] / detA}
                     , {-A[1][0] / detA,   A[0][0] / detA}}};
    
    decltype(auto) sln = A_1 * b;

    decltype(auto) p1 = f1.count(sln[0]);
    decltype(auto) p2 = f2.count(sln[1]);

    if (p1 == p2 && 
        0.0 - _eps <= sln[0] && sln[0] <= 1.0 + _eps && 
        0.0 - _eps <= sln[1] && sln[1] <= 1.0 + _eps) return Result<Vector3D>::success(p1, ResultStatus::Intersection);
    return Result<Vector3D>::failure(no_solution_msg, ResultStatus::NoIntersection);
}