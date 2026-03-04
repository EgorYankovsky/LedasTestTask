#pragma once

#include <cmath>

const double _eps = 1E-13;

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

	inline auto is_zero() const noexcept -> bool { return abs(X) < _eps && 
														  abs(Y) < _eps && 
														  abs(Z) < _eps; }
	inline auto norma() const noexcept -> double { return sqrt(X*X + Y*Y + Z*Z); }

	/// <summary>
	/// Функция нахождения векторного произведения.
	/// </summary>
	inline friend auto cross(const Vector3D& a, const Vector3D& b) noexcept -> Vector3D {
		return Vector3D(a.y() * b.z() - a.z() * b.y(),
						a.z() * b.x() - a.x() * b.z(),
						a.x() * b.y() - a.y() * b.x());
	}

	inline friend auto operator*(const Vector3D& a, const Vector3D& b) noexcept -> double { return a.x()*b.x() + a.y()*b.y() + a.z()*b.z(); }
	inline friend auto operator-(const Vector3D& a, const Vector3D& b) noexcept -> Vector3D { return Vector3D(a.X-b.X, a.Y-b.Y, a.Z-b.Z); }
	inline friend auto operator==(const Vector3D& a, const Vector3D& b) noexcept -> bool { return abs(a.X - b.X) < _eps
																							   && abs(a.Y - b.Y) < _eps
																							   && abs(a.Z - b.Z) < _eps; }
};