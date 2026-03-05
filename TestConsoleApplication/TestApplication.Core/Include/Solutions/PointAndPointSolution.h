#pragma once

#include "ISolution.h"

class PointAndPointSolution final : public ISolution {
public:
	PointAndPointSolution() {}
	~PointAndPointSolution() {}

	auto solve(const Segment3D&, const Segment3D&) const -> Result<Vector3D> override;
};