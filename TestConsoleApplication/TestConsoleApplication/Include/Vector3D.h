#pragma once

#include <cmath>

class Vector3D {
private:
	double X;
	double Y;
	double Z;
public:
	Vector3D() : X(0.0), Y(0.0), Z(0.0) {}
	Vector3D(const double& x, const double& y, const double& z) : X(x), Y(y), Z(z) {}
	~Vector3D() {}

	inline auto x() const noexcept -> double { return X; };
	inline auto y() const noexcept -> double { return Y; };
	inline auto z() const noexcept -> double { return Z; };

	inline auto is_zero() const noexcept -> bool { return X < 1e-16 && Y < 1e-16 && Z < 1e-16; }
	inline auto norma() const noexcept -> double { return sqrt(X*X + Y*Y + Z*Z); }

	/// <summary>
	/// Функция нахождения векторного произведения.
	/// </summary>
	inline friend auto cross(const Vector3D& a, const Vector3D& b) noexcept -> Vector3D {
		return Vector3D(a.y() * b.z() - a.z() * b.y(),
						a.z() * b.x() - a.x() * b.z(),
						a.x() * b.y() - a.y() * b.x());
	}

	inline friend auto operator-(const Vector3D& a, const Vector3D& b) noexcept -> Vector3D { return Vector3D(a.X-b.X, a.Y-b.Y, a.Z-b.Z); }
	inline friend auto operator==(const Vector3D& a, const Vector3D& b) noexcept -> bool { return abs(a.X - b.X) < 1e-16 
																							   && abs(a.Y - b.Y) < 1e-16 
																							   && abs(a.Z - b.Z) < 1e-16; }
};