#pragma once

#include "ISolution.h"

class PointAndLineSolution final : public ISolution {
public:
	PointAndLineSolution() {}
	~PointAndLineSolution() {}

	auto solve(const Segment3D&, const Segment3D&) const -> Result<Vector3D> override;
};