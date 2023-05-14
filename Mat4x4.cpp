#include "Mat4x4.h"
#include "Vector3D.h"
#include <cmath>
#include <algorithm>
#include <Windows.h>

#if _DEBUG
#include <chrono>
#endif // _DEBUG


Mat4x4::Mat4x4()
	:m({ 0.0f })
{}

Mat4x4::Mat4x4(const Mat4x4& mat) {
	*this = mat;
}

Mat4x4 Mat4x4::operator*(const Mat4x4& mat) const{
	Mat4x4 tmp;

	for (int y = 0; y < Mat4x4::HEIGHT; y++) {
		for (int x = 0; x < Mat4x4::WIDTH; x++) {
			for (int i = 0; i < Mat4x4::WIDTH; i++) {
				tmp.m[y][x] += this->m[y][i] * mat.m[i][x];
			}
		}
	}

	return tmp;
}

Mat4x4::Mat4x4(std::array<std::array<float, 4>, 4> num) {
	m = num;
}

const Mat4x4& Mat4x4::operator=(const Mat4x4& mat) {
	this->m = mat.m;

	return *this;
}

const Mat4x4& Mat4x4::operator*=(const Mat4x4& mat) {
	*this = *this * mat;

	return *this;
}

Mat4x4 Mat4x4::operator+(const Mat4x4& mat) const {
	Mat4x4 tmp;

	for (int y = 0; y < Mat4x4::HEIGHT; y++) {
		for (int x = 0; x < Mat4x4::WIDTH; x++) {
			tmp[y][x] = this->m[y][x] + mat.m[y][x];
		}
	}

	return tmp;
}
const Mat4x4& Mat4x4::operator+=(const Mat4x4& mat) {
	for (int y = 0; y < Mat4x4::HEIGHT; y++) {
		for (int x = 0; x < Mat4x4::WIDTH; x++) {
			this->m[y][x] += mat.m[y][x];
		}
	}

	return *this;
}
Mat4x4 Mat4x4::operator-(const Mat4x4& mat) const {
	Mat4x4 tmp;

	for (int y = 0; y < Mat4x4::HEIGHT; y++) {
		for (int x = 0; x < Mat4x4::WIDTH; x++) {
			tmp[y][x] = this->m[y][x] - mat.m[y][x];
		}
	}

	return tmp;
}
const Mat4x4& Mat4x4::operator-=(const Mat4x4& mat) {
	for (int y = 0; y < Mat4x4::HEIGHT; y++) {
		for (int x = 0; x < Mat4x4::WIDTH; x++) {
			this->m[y][x] -= mat.m[y][x];
		}
	}

	return *this;
}

std::array<float, 4>& Mat4x4::operator[](size_t index) {
	return m[index];
}

bool Mat4x4::operator==(const Mat4x4& mat) const {
	return m == mat.m;
}

bool Mat4x4::operator!=(const Mat4x4& mat) const {
	return m != mat.m;
}

void Mat4x4::Indentity() {
	m = { 0.0f };

	for (int i = 0; i < WIDTH; i++) {
		m[i][i] = 1.0f;
	}
}

void Mat4x4::Translate(const Vector3D& vec) {
	this->m = { 0.0f };

	this->m[0][0] = 1.0f;
	this->m[1][1] = 1.0f;
	this->m[2][2] = 1.0f;
	this->m[3][3] = 1.0f;

	this->m[3][0] = vec.x;
	this->m[3][1] = vec.y;
	this->m[3][2] = vec.z;
}

void Mat4x4::Scalar(const Vector3D& vec) {
	this->m = { 0.0f };

	this->m[0][0] = vec.x;
	this->m[1][1] = vec.y;
	this->m[2][2] = vec.z;
	this->m[3][3] = 1.0f;
}

void Mat4x4::RotateX(float rad) {
	this->m = { 0.0f };
	this->m[0][0] = 1.0f;
	this->m[3][3] = 1.0f;

	this->m[1][1] = std::cos(rad);
	this->m[1][2] = std::sin(rad);
	this->m[2][1] = -std::sin(rad);
	this->m[2][2] = std::cos(rad);
}

void Mat4x4::RotateY(float rad) {
	this->m = { 0.0f };
	this->m[1][1] = 1.0f;
	this->m[3][3] = 1.0f;

	this->m[0][0] = std::cos(rad);
	this->m[0][2] = -std::sin(rad);
	this->m[2][0] = std::sin(rad);
	this->m[2][2] = std::cos(rad);
}

void Mat4x4::RotateZ(float rad) {
	this->m = { 0.0f };
	this->m[2][2] = 1.0f;
	this->m[3][3] = 1.0f;
	
	this->m[0][0] = std::cos(rad);
	this->m[0][1] = std::sin(rad);
	this->m[1][0] = -std::sin(rad);
	this->m[1][1] = std::cos(rad);
}


void Mat4x4::Affin(const Vector3D& scale, const Vector3D& rad, const Vector3D& translate) {
	Mat4x4 rotate = MakeMatrixRotateX(rad.x) * MakeMatrixRotateY(rad.y) * MakeMatrixRotateZ(rad.z);

	*this = Mat4x4({
		scale.x * rotate.m[0][0], scale.x * rotate.m[0][1],scale.x * rotate.m[0][2], 0.0f,
		scale.y * rotate.m[1][0], scale.y * rotate.m[1][1],scale.y * rotate.m[1][2], 0.0f,
		scale.z * rotate.m[2][0], scale.z * rotate.m[2][1],scale.z * rotate.m[2][2], 0.0f,
		translate.x, translate.y, translate.z, 1.0f
		});
}


void Mat4x4::Inverse() {
#ifdef _DEBUG
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
#endif

	//一時保存用
	Mat4x4 tmp = *this;

	//単位行列
	Mat4x4 identity = MakeMatrixIndentity();

	// pibotを1にするためのバッファ
	float toOne = *(tmp.m.begin()->begin());

	// 見ている行の一部の値を0.0fにするためのバッファ(0除算が発生しないように初期化は1.0fで行う)
	float tmpNum = 0.0f;

	// 掃き出し法
	for (int i = 0; i < Mat4x4::HEIGHT; i++) {
		// ピボット選択
		if (tmp.m[i][i] == 0.0f && i < Mat4x4::HEIGHT) {
			// 行要素番号バッファ
			int pibIndex = i;
			// ピボットバッファ
			float pibot = fabsf(tmp.m[i][i]);

			// ピボット設定
			for (int y = i + 1; y < Mat4x4::HEIGHT; y++) {
				if (tmp.m[y][i] != 0.0f && pibot < fabsf(tmp.m[y][i])) {
					pibot = fabsf(tmp.m[y][i]);
					pibIndex = y;
				}
			}

			//ピボットが0だった場合逆行列は存在しないので処理終了
			if (pibot == 0.0f) {
				return;
			}

			// 見てる値が0だったらその行を見ている値の列で絶対値の一番高い行と交換
			tmp.m[i].swap(tmp.m[pibIndex]);
			identity.m[i].swap(identity.m[pibIndex]);
		}

		// tmpを単位行列に近づけるために見ている要素の行を見ている要素で割る
		toOne = tmp.m[i][i];
		for (int x = 0; x < Mat4x4::HEIGHT; x++) {
			tmp.m[i][x] /= toOne;
			identity.m[i][x] /= toOne;
		}

		// tmpの見ている列を単位行列に近づけるための処理
		for (int y = 0; y < Mat4x4::HEIGHT; ++y) {
			if (i == y) {
				continue;
			}

			tmpNum = -tmp.m[y][i];
			for (int x = 0; x < Mat4x4::WIDTH; x++) {
				tmp.m[y][x] += tmpNum * tmp.m[i][x];
				identity.m[y][x] += tmpNum * identity.m[i][x];
			}
		}
	}

	// tmpが単位行列になっていない場合失敗なので処理終了
	if (tmp != MakeMatrixIndentity()) {
		return;
	}

	// 逆行列にした行列を代入
	*this = identity;

#ifdef _DEBUG
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::string msg = "Inverse Matrix Process Time : " + std::to_string(static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count())) + " microseconds\n";
	OutputDebugStringA(msg.c_str());
#endif


	/// 苦労した割にはすっきりしないプログラムでつらい
}


void Mat4x4::Transepose() {
	std::swap(m[1][0], m[0][1]);
	std::swap(m[2][0], m[0][2]);
	std::swap(m[3][0], m[0][3]);
	std::swap(m[2][1], m[1][2]);
	std::swap(m[2][3], m[3][2]);
	std::swap(m[3][1], m[1][3]);
}

void Mat4x4::PerspectiveFov(float fovY, float aspectRatio, float nearClip, float farClip) {
	m = { 0.0f };

	m[0][0] = (1.0f / aspectRatio) * (1.0f / std::tan(fovY / 2.0f));
	m[1][1] = 1.0f / std::tan(fovY / 2.0f);
	m[2][2] = farClip / (farClip - nearClip);
	m[2][3] = 1.0f;
	m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
}

void Mat4x4::Orthographic(float left, float top, float right, float bottom, float nearClip, float farClip) {
	m = { 0.0f };

	m[0][0] = 2.0f / (right - left);
	m[1][1] = 2.0f / (top - bottom);
	m[2][2] = 1.0f / (farClip - nearClip);
	m[3][3] = 1.0f;

	m[3][0] = (left + right) / (left - right);
	m[3][1] = (top + bottom) / (bottom - top);
	m[3][2] = nearClip / (nearClip - farClip);
}

void Mat4x4::ViewPort(float left, float top, float width, float height, float minDepth, float maxDepth) {
	m = { 0.0f };

	m[0][0] = width / 2.0f;
	m[1][1] = height/ -2.0f;
	m[2][2] = maxDepth - minDepth;
	m[3][3] = 1.0f;

	m[3][0] = left + (width / 2.0f);
	m[3][1] = top + (height / 2.0f);
	m[3][2] = minDepth;
}


Mat4x4 MakeMatrixIndentity() {
	Mat4x4 tmp;
	tmp.Indentity();
	return tmp;
}

Mat4x4 MakeMatrixInverse(Mat4x4 mat) {
	Mat4x4 tmp = mat;
	tmp.Inverse();
	return tmp;
}

Mat4x4 MakeMatrixTransepose(Mat4x4 mat) {
	Mat4x4 tmp = mat;
	tmp.Transepose();
	return tmp;
}

Mat4x4 MakeMatrixTranslate(Vector3D vec) {
	Mat4x4 mat;

	mat.Translate(vec);

	return mat;
}

Mat4x4 MakeMatrixScalar(Vector3D vec) {
	Mat4x4 mat;

	mat.Scalar(vec);

	return mat;
}

Mat4x4 MakeMatrixRotateX(float rad) {
	Mat4x4 tmp;

	tmp.RotateX(rad);

	return tmp;
}

Mat4x4 MakeMatrixRotateY(float rad) {
	Mat4x4 tmp;

	tmp.RotateY(rad);

	return tmp;
}

Mat4x4 MakeMatrixRotateZ(float rad) {
	Mat4x4 tmp;

	tmp.RotateZ(rad);

	return tmp;
}

Mat4x4 MakeMatrixAffin(const Vector3D& scale, const Vector3D& rad, const Vector3D& translate) {
	Mat4x4 tmp;

	tmp.Affin(scale, rad, translate);

	return tmp;
}

Mat4x4 MakeMatrixPerspectiveFov(float fovY, float aspectRatio, float nearClip, float farClip) {
	Mat4x4 tmp;

	tmp.PerspectiveFov(fovY, aspectRatio, nearClip, farClip);

	return tmp;
}

Mat4x4 MakeMatrixOrthographic(float left, float right, float top, float bottom, float nearClip, float farClip) {
	Mat4x4 tmp;

	tmp.Orthographic(left, right, top, bottom, nearClip, farClip);

	return tmp;
}

Mat4x4 MakeMatrixViewPort(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Mat4x4 tmp;

	tmp.ViewPort(left, top, width, height, minDepth, maxDepth);

	return tmp;
}