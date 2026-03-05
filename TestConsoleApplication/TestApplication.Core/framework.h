#pragma once

#include "Include/Segment3D.h"
#include "Include/Solutions.h"

#define WIN32_LEAN_AND_MEAN

const Vector3D empty_vector = Vector3D(NAN, NAN, NAN);

auto Intersect(const Segment3D&, const Segment3D&) -> Vector3D;