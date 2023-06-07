#pragma once

class Vector2D {
public:
	Vector2D();
	Vector2D(const float& X, const float& Y);

	Vector2D(const Vector2D& num);

	inline ~Vector2D(){}

public:
	float x;
	float y;

public:

	Vector2D operator+(const Vector2D& num) const;
	Vector2D operator-(const Vector2D& num) const;
	Vector2D operator*(const Vector2D& num) const;
	Vector2D operator/(const Vector2D& num) const;
	Vector2D operator*(const float& num) const;
	Vector2D operator/(const float& num) const;
	const Vector2D& operator=(const Vector2D& num);
	const Vector2D& operator+=(const Vector2D& num);
	const Vector2D& operator-=(const Vector2D& num);
	const Vector2D& operator*=(const float& num);
	const Vector2D& operator/=(const float& num);
	bool operator==(const Vector2D& num) const;
	bool operator!=(const Vector2D& num) const;

	// =================================================================================

	void Rotate(float rad);

	float Cross(const Vector2D& vec) const;
	float Dot(const Vector2D& vec) const;
	float GetLength() const;

	Vector2D Normalize() const;
};