#include "Vector2D.h"
#include <assert.h>
#include <cmath>

Vector2D::Vector2D() {
	this->x = 0.0f;
	this->y = 0.0f;
}
Vector2D::Vector2D(const Vector2D& num) {
	this->x = num.x;
	this->y = num.y;
}
Vector2D::Vector2D(const float& X, const float& Y) {
	this->x = X;
	this->y = Y;
}


Vector2D Vector2D::operator+(const Vector2D& num) const {
	Vector2D tmp;

	tmp.x = this->x + num.x;
	tmp.y = this->y + num.y;

	return tmp;
};
Vector2D Vector2D::operator-(const Vector2D& num) const {
	Vector2D tmp;

	tmp.x = this->x - num.x;
	tmp.y = this->y - num.y;

	return tmp;
}
Vector2D Vector2D::operator*(const Vector2D& num) const {
	Vector2D tmp;

	tmp.x = this->x * num.x;
	tmp.y = this->y * num.y;

	return tmp;
}
Vector2D Vector2D::operator/(const Vector2D& num) const {
	Vector2D tmp;

	tmp.x = this->x / num.x;
	tmp.y = this->y / num.y;

	return tmp;
}


Vector2D Vector2D::operator*(const float& num) const {
	Vector2D tmp;

	tmp.x = this->x * num;
	tmp.y = this->y * num;

	return tmp;
}
Vector2D Vector2D::operator/(const float& num) const {
	Vector2D tmp;

	tmp.x = this->x / num;
	tmp.y = this->y / num;

	return tmp;
}

Vector2D operator+(const float& num, const Vector2D& vec) {
	Vector2D tmp;

	tmp.x = num + vec.x;
	tmp.y = num + vec.y;

	return tmp;
}
Vector2D operator-(const float& num, const Vector2D& vec) {
	Vector2D tmp;

	tmp.x = num - vec.x;
	tmp.y = num - vec.y;

	return tmp;
}
Vector2D operator*(const float& num, const Vector2D& vec) {
	Vector2D tmp;

	tmp.x = num * vec.x;
	tmp.y = num * vec.y;

	return tmp;
}
Vector2D operator/(const float& num, const Vector2D& vec) {
	Vector2D tmp;

	tmp.x = num / vec.x;
	tmp.y = num / vec.y;

	return tmp;
}

const Vector2D& Vector2D::operator=(const Vector2D& num) {
	this->x = num.x;
	this->y = num.y;

	return *this;
}


const Vector2D& Vector2D::operator+=(const Vector2D& num) {
	this->x += num.x;
	this->y += num.y;

	return *this;
}
const Vector2D& Vector2D::operator-=(const Vector2D& num) {
	this->x -= num.x;
	this->y -= num.y;

	return *this;
}

const Vector2D& Vector2D::operator*=(const float& num) {
	this->x *= num;
	this->y *= num;

	return *this;
}
const Vector2D& Vector2D::operator/=(const float& num) {
	this->x /= num;
	this->y /= num;

	return *this;
}

bool Vector2D::operator==(const Vector2D& num) const {
	return this->x == num.x && this->y == num.y;
}
bool Vector2D::operator!=(const Vector2D& num) const {
	return this->x != num.x && this->y != num.y;
}


bool operator==(const float& num, const Vector2D& vec) {
	return num == vec.x && num == vec.y;
}
bool operator!=(const float& num, const Vector2D& vec) {
	return num != vec.x && num != vec.y;
}
bool operator<(const float& num, const Vector2D& vec) {
	return num < vec.x || num < vec.y;
}
bool operator>(const float& num, const Vector2D& vec) {
	return num > vec.x || num > vec.y;
}
bool operator<=(const float& num, const Vector2D& vec) {
	return num <= vec.x || num <= vec.y;
}
bool operator>=(const float& num, const Vector2D& vec) {
	return num >= vec.x || num >= vec.y;
}

void Vector2D::Rotate(float rad) {
	x *= cosf(rad);
	y *= sinf(rad);
}

float Vector2D::Cross(const Vector2D& vec) const {
	return x * vec.y - y * vec.x;
}
float Vector2D::Dot(const Vector2D& vec) const {
	return x * vec.x + y * vec.y;
}

float Vector2D::GetLength() const {
	return std::hypot(x, y);
}

Vector2D Vector2D::Normalize() const {
	return Vector2D(x/ GetLength(), y / GetLength());
}