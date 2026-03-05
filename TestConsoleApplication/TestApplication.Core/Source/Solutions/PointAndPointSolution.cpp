#include "pch.h"
#include "Include/Solutions/PointAndPointSolution.h"

auto 
operator*(const matrix2x2& m, const vector2& v) -> vector2 {
	return vector2{ m[0][0] * v[0] + m[0][1] * v[1],
					m[1][0] * v[0] + m[1][1] * v[1] };
}

auto 
PointAndPointSolution::solve(const Segment3D& s1, const Segment3D& s2) const -> Result<Vector3D> {
	// Проверяем равенство двух точек.
	decltype(auto) p1 = s1.start();
	decltype(auto) p2 = s2.start();
	if (p1 == p2) return Result<Vector3D>::success(s1.start(), ResultStatus::Intersection);
	return Result<Vector3D>::failure(no_intersection_msg, ResultStatus::NoIntersection);
}
