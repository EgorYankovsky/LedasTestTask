#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <locale.h>
#include <string.h>

#include "Include/Segment3D.h"
#include "Include/Result.h"

const std::string no_solution_msg = "No solution.";

auto Intersect(const Segment3D&, const Segment3D&) -> Vector3D;

auto intersection_checker(const Segment3D& s1, const Segment3D& s2) -> Result<Vector3D> {
    // Шаг 1. Проверить линейную зависимость между векторами, образуемыми в сегменте.
    decltype(auto) v1 = s1.get_segmented_vector();
    decltype(auto) v2 = s2.get_segmented_vector();
    decltype(auto) cross_result = cross(v1, v2);
    if (cross_result.is_zero()) {
        // Векторы зависимы.
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
    std::cout << "Kekus" << std::endl;
    return Result<Vector3D>::success(Vector3D(), ResultStatus::Intersection);
}