#pragma once

#include <memory>
#include <array>

#include "../Segment3D.h"
#include "../Result.h"
#include "../ParametricFunction.h"

using matrix2x2 = std::array<std::array<double, 2>, 2>;
using vector2 = std::array<double, 2>;

auto operator* (const matrix2x2& m, const vector2& v) -> vector2;

const std::string no_intersection_msg = "No intersection.";
const std::string parallel_msg = "Parallel.";

class ISolution {
public:
	~ISolution() = default;
	virtual auto solve(const Segment3D&, const Segment3D&) const -> Result<Vector3D> = 0;
};