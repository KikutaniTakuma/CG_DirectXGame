#include "Vector3D.h"
#include <cmath>
#include "Math/Mat4x4/Mat4x4.h"
#include <cassert>

Vector3D::Vector3D():
	x(0.0f),
	y(0.0f),
	z(0.0f)
{}

Vector3D::Vector3D(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D Vector3D::operator+(const Vector3D& vec) const {
	Vector3D tmp(x + vec.x, y + vec.y, z + vec.z);

	return tmp;
}
Vector3D Vector3D::operator-(const Vector3D& vec) const {
	Vector3D tmp(x - vec.x, y - vec.y, z - vec.z);

	return tmp;
}
Vector3D Vector3D::operator+=(const Vector3D& vec) {
	*this = *this + vec;

	return *this;
}
Vector3D Vector3D::operator-=(const Vector3D& vec) {
	*this = *this - vec;

	return *this;
}

Vector3D Vector3D::operator*(float scalar) const {
	Vector3D tmp(x * scalar, y * scalar, z * scalar);

	return tmp;
}
Vector3D Vector3D::operator*=(float scalar) {
	*this = *this * scalar;

	return *this;
}

Vector3D Vector3D::Normalize() {
	float nor = this->Length();

	return Vector3D(x / nor, y / nor, z / nor);
}

Vector3D Vector3D::operator*(const Mat4x4& mat) const {
	Vector3D result;

	result.x = x * mat.get()[0][0] + y * mat.get()[1][0] + z * mat.get()[2][0] + 1.0f * mat.get()[3][0];
	result.y = x * mat.get()[0][1] + y * mat.get()[1][1] + z * mat.get()[2][1] + 1.0f * mat.get()[3][1];
	result.z = x * mat.get()[0][2] + y * mat.get()[1][2] + z * mat.get()[2][2] + 1.0f * mat.get()[3][2];
	const float&& w = x * mat.get()[0][3] + y * mat.get()[1][3] + z * mat.get()[2][3] + 1.0f * mat.get()[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

Vector3D& Vector3D::operator*=(const Mat4x4& mat) {
	*this = *this * mat;

	return *this;
}

float Vector3D::Length() {
	return sqrtf(powf(x,2.0f)+ powf(y, 2.0f)+ powf(z, 2.0f));
}

float Vector3D::Dot(const Vector3D& vec) const {
	return x * vec.x + y * vec.y + z * vec.z;
}

Vector3D Vector3D::Cross(const Vector3D& vec) const {
	Vector3D result;

	result.x = y * vec.z - z * vec.y;
	result.y = z * vec.x - x * vec.z;
	result.z = x * vec.y - y * vec.x;

	return result;
}