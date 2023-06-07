#pragma once
#include <string>

class Mat4x4;

class Vector3D {
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& vec) = default;

public:
	float x;
	float y;
	float z;

public:
	Vector3D& operator=(const Vector3D& vec) = default;
	Vector3D operator+(const Vector3D& vec) const;
	Vector3D operator-(const Vector3D& vec) const;
	Vector3D operator+=(const Vector3D& vec);
	Vector3D operator-=(const Vector3D& vec);
	Vector3D operator*(float scalar) const;
	Vector3D operator*=(float scalar);
	Vector3D Normalize();
	Vector3D operator*(const Mat4x4& mat) const;
	Vector3D& operator*=(const Mat4x4& mat);

	float Dot(const Vector3D& vec) const;
	Vector3D Cross(const Vector3D& vec) const;
	float Length();
};