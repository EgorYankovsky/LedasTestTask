#pragma once

#include <array>

#include "Segment3D.h"

class ParametricFunction {
private:
	std::array<double, 3> a;
	std::array<double, 3> t0;
public:
	ParametricFunction(const Segment3D& s) {
		t0[0] = s.start().x();
		t0[1] = s.start().y();
		t0[2] = s.start().z();
		a[0] = s.end().x() - s.start().x();
		a[1] = s.end().y() - s.start().y();
		a[2] = s.end().z() - s.start().z();
	};
	~ParametricFunction() {};

	inline auto count(const double& t) -> Vector3D { return Vector3D(a[0] * t + t0[0],
																	 a[1] * t + t0[1],
																	 a[2] * t + t0[2]); }
};