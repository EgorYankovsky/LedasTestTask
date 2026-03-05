#include "pch.h"
#include "Include/Solutions/IntersectingLinesSolution.h"

auto 
IntersectingLinesSolution::solve(const Segment3D& s1, const Segment3D& s2) const -> Result<Vector3D> {
    ParametricFunction f1(s1);
    ParametricFunction f2(s2);
    
    decltype(auto) v1 = s1.get_segmented_vector();
    decltype(auto) v2 = s2.get_segmented_vector();

    Vector3D delt(s2.start().x() - s1.start().x(),
        s2.start().y() - s1.start().y(),
        s2.start().z() - s1.start().z());

    matrix2x2 A = { {{-1.0 * (v1 * v1), v1 * v2}
                   , {-1.0 * (v1 * v2), v2 * v2}} };
    vector2 b = { -1.0 * (v1 * delt),
                  -1.0 * (v2 * delt) };

    double detA = A[0][0] * A[1][1] - A[0][1] * A[1][0];
    matrix2x2 A_1 = { {{ A[1][1] / detA,  -A[0][1] / detA}
                     , {-A[1][0] / detA,   A[0][0] / detA}} };

    decltype(auto) sln = A_1 * b;

    decltype(auto) p1 = f1.count(sln[0]);
    decltype(auto) p2 = f2.count(sln[1]);

    if (p1 == p2 &&
        0.0 - _eps <= sln[0] && sln[0] <= 1.0 + _eps &&
        0.0 - _eps <= sln[1] && sln[1] <= 1.0 + _eps) return Result<Vector3D>::success(p1, ResultStatus::Intersection);
    return Result<Vector3D>::failure(no_intersection_msg, ResultStatus::NoIntersection);
}
