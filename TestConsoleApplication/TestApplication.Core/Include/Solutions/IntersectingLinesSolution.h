#pragma once

#include "ISolution.h"

class IntersectingLinesSolution final : public ISolution {
public:
	IntersectingLinesSolution() {}
	~IntersectingLinesSolution() {}

	auto solve(const Segment3D&, const Segment3D&) const -> Result<Vector3D> override;
};