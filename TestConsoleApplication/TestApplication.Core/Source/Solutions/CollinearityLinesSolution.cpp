#include "pch.h"
#include "Include/Solutions/CollinearityLinesSolution.h"

auto
CollinearityLinesSolution::solve(const Segment3D& s1, const Segment3D& s2) const -> Result<Vector3D> {
    ParametricFunction f1(s1);
    ParametricFunction f2(s2);

    auto find_infinite = [&f1, &f2](const double& t0, const double& t1, const double& alph, const double& beta) -> Result<Vector3D> {
        decltype(auto) a = (t1 - t0) / alph;
        decltype(auto) b = (t0 - t1) / beta;
        decltype(auto) c = (beta + t1 - t0) / alph;
        decltype(auto) d = (alph + t0 - t1) / beta;

        int arr[4] = {
            0.0 <= a && a < 1.0 ? 1 : 0,
            0.0 < b && b <= 1.0 ? 1 : 0,
            0.0 < c && c <= 1.0 ? 1 : 0,
            0.0 <= d && d < 1.0 ? 1 : 0
        };
        int sum_arr = arr[0] + arr[1] + arr[2] + arr[3];

        if (sum_arr > 1) {
            if (arr[0] == 1) return Result<Vector3D>::success(f2.count(0.0), ResultStatus::Infinite);
            if (arr[1] == 1) return Result<Vector3D>::success(f1.count(0.0), ResultStatus::Infinite);
            if (arr[2] == 1) return Result<Vector3D>::success(f2.count(1.0), ResultStatus::Infinite);
            if (arr[3] == 1) return Result<Vector3D>::success(f1.count(1.0), ResultStatus::Infinite);
        }
        return Result<Vector3D>::failure("", ResultStatus::NoIntersection);
        };

    decltype(auto) v1 = s1.get_segmented_vector();
    decltype(auto) v2 = s2.get_segmented_vector();

    decltype(auto) c = s2.start() - s1.start();
    decltype(auto) cr = cross(c, v1);
    if (cr.is_zero()) { // Векторы лежат на одной прямой.

        // Проверяем на множество решений и при необходимости возвращаем значение.
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

        return Result<Vector3D>::failure(no_intersection_msg, ResultStatus::NoIntersection);
    }
    else { // Векторы не лежат на одной прямой.
        return Result<Vector3D>::failure(parallel_msg, ResultStatus::Parallel);
    }
}