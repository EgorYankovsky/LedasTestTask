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
    ParametricFunction f1(s1);
    ParametricFunction f2(s2);

    auto find_infinite = [&f1, &f2](const double& t0, const double& t1, const double& alph, const double& beta) -> Result<Vector3D> {
        decltype(auto) a = (t1 - t0) / alph;
        decltype(auto) b = (t0 - t1) / beta;
        decltype(auto) c = (beta + t1 - t0) / alph;
        decltype(auto) d = (alph + t0 - t1) / alph;
            if (0.0 < a && a < 1.0) return Result<Vector3D>::success(f2.count(0.0), ResultStatus::Infinite);
            else if (0.0 < b && b < 1.0) return Result<Vector3D>::success(f1.count(0.0), ResultStatus::Infinite);
            else if (0.0 < c && c < 1.0) return Result<Vector3D>::success(f2.count(1.0), ResultStatus::Infinite);
            else if (0.0 < d && d < 1.0) return Result<Vector3D>::success(f1.count(1.0), ResultStatus::Infinite);
            return Result<Vector3D>::failure("no infinite", ResultStatus::NoIntersection);
        };

    decltype(auto) v1 = s1.get_segmented_vector();
    decltype(auto) v2 = s2.get_segmented_vector();

    decltype(auto) c = s2.start() - s1.start();
    decltype(auto) cr = cross(c, v1);
    if (cr.is_zero()) {
        // Векторы лежат на одной прямой.


        // Проверяем на множество решений и при реобходимости возвращаем значение.
        {
            if (abs(v1.x()) >= _eps && abs(v2.x()) >= _eps) {
                Result<Vector3D> res = find_infinite(s1.start().x(), s2.start().x(), v1.x(), v2.x());
                if (res.status() == ResultStatus::Infinite) return Result<Vector3D>::success(res.value(), res.status());
            }
            else if (abs(v1.y()) >= _eps && abs(v2.y()) >= _eps) {
                Result<Vector3D> res = find_infinite(s1.start().y(), s2.start().y(), v1.y(), v2.y());
                if (res.status() == ResultStatus::Infinite) return Result<Vector3D>::success(res.value(), res.status());
            }
            else if (abs(v1.z()) >= _eps && abs(v2.z()) >= _eps) {
                Result<Vector3D> res = find_infinite(s1.start().z(), s2.start().z(), v1.z(), v2.z());
                if (res.status() == ResultStatus::Infinite) return Result<Vector3D>::success(res.value(), res.status());
            }
        }


        // Частные решения если начала и концы векторов касаются друг друга.
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