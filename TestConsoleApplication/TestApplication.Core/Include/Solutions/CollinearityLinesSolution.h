#pragma once

#include "ISolution.h"

class CollinearityLinesSolution final : public ISolution {
public:
	CollinearityLinesSolution() {}
	~CollinearityLinesSolution() {}

	auto solve(const Segment3D&, const Segment3D&) const -> Result<Vector3D> override;
};