#pragma once
#include "Vector3D.h"

class Segment3D {
private:
	Vector3D _start;
	Vector3D _end;
public:
	Segment3D() {}
	Segment3D(const Vector3D& v0, const Vector3D& v1) : _start(v0), _end(v1) {}
	~Segment3D() {}

	inline auto start() const noexcept -> const Vector3D& { return _start; };
	inline auto end() const noexcept -> const Vector3D& { return _end; };
	
	/// <summary>
	/// Метод, возвращающий вектор, заключенный в сегменте. Иначе говоря, разница _end и _start.
	/// </summary>
	inline auto get_segmented_vector() const noexcept -> Vector3D { return _end - _start; }
};