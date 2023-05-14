#pragma once

#include <array>
#include <string>

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

class Vector3D;

class Mat4x4 {
public:
	/// <summary>
	/// 規定コンストラクタ
	/// </summary>
	Mat4x4();

	/// <summary>
	/// コピーコンストラクタ
	/// </summary>
	Mat4x4(const Mat4x4& mat);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="num"></param>
	Mat4x4(std::array<std::array<float, 4>, 4> num);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Mat4x4() = default;

private:
	static const int HEIGHT = 4;
	static const int WIDTH = 4;

private:
	std::array<std::array<float, 4>, 4> m;

public:
	Mat4x4 operator*(const Mat4x4& mat) const;
	const Mat4x4& operator=(const Mat4x4& mat);
	const Mat4x4& operator*=(const Mat4x4& mat);

	Mat4x4 operator+(const Mat4x4& mat) const;
	const Mat4x4& operator+=(const Mat4x4& mat);
	Mat4x4 operator-(const Mat4x4& mat) const;
	const Mat4x4& operator-=(const Mat4x4& mat);

	std::array<float, 4>& operator[](size_t index);

	bool operator==(const Mat4x4& mat) const;
	bool operator!=(const Mat4x4& mat) const;

	inline std::array<std::array<float, 4>, 4> get() const {
		return m;
	}

public:
	/// <summary>
	/// 単位行列化
	/// </summary>
	void Indentity();

	/// <summary>
	/// 平行移動行列化
	/// </summary>
	/// <param name="vec">移動ベクトル</param>
	void Translate(const Vector3D& vec);

	/// <summary>
	/// スカラー倍行列化
	/// </summary>
	/// <param name="vec">大きさベクトル</param>
	void Scalar(const Vector3D& vec);

	/// <summary>
	/// x軸回転
	/// </summary>
	/// <param name="rad">ラジアン</param>
	void RotateX(float rad);

	/// <summary>
	/// y軸回転
	/// </summary>
	/// <param name="rad">ラジアン</param>
	void RotateY(float rad);

	/// <summary>
	/// z軸回転
	/// </summary>
	/// <param name="rad">ラジアン</param>
	void RotateZ(float rad);

	/// <summary>
	/// アフィン
	/// </summary>
	/// <param name="scale">スケール</param>
	/// <param name="rad">ラジアン</param>
	/// <param name="translate">平行移動</param>
	void Affin(const Vector3D& scale, const Vector3D& rad, const Vector3D& translate);

	/// <summary>
	/// 逆行列化
	/// </summary>
	void Inverse();

	/// <summary>
	/// 転置行列化
	/// </summary>
	void Transepose();

	/// <summary>
	/// 投資投影
	/// </summary>
	/// <param name="fov"></param>
	/// <param name="aspectRatio"></param>
	/// <param name="nearClip"></param>
	/// <param name="farClip"></param>
	void PerspectiveFov(float fovY, float aspectRatio, float nearClip, float farClip);

	/// <summary>
	/// 正射影
	/// </summary>
	/// <param name="left"></param>
	/// <param name="right"></param>
	/// <param name="top"></param>
	/// <param name="bottom"></param>
	/// <param name="nearClip"></param>
	/// <param name="farClip"></param>
	void Orthographic(float left, float right, float top, float bottom, float nearClip, float farClip);

	/// <summary>
	/// ビューポート
	/// </summary>
	/// <param name="left"></param>
	/// <param name="right"></param>
	/// <param name="top"></param>
	/// <param name="bottom"></param>
	/// <param name="minDepth"></param>
	/// <param name="maxDepth"></param>
	void ViewPort(float left, float top, float width, float height, float minDepth, float maxDepth);
};


/// <summary>
/// 単位行列
/// </summary>
/// <returns>単位行列を返す</returns>
Mat4x4 MakeMatrixIndentity();

/// <summary>
/// 平行移動行列
/// </summary>
/// <param name="vec">移動ベクトル</param>
/// <returns>平行移動行列を返す</returns>
Mat4x4 MakeMatrixTranslate(Vector3D vec);

/// <summary>
/// スカラー倍行列
/// </summary>
/// <param name="vec">大きさベクトル</param>
/// <returns>スカラー倍行列を返す</returns>
Mat4x4 MakeMatrixScalar(Vector3D vec);

/// <summary>
/// x軸回転
/// </summary>
/// <param name="rad">ラジアン</param>
/// <returns>x軸回転した行列</returns>
Mat4x4 MakeMatrixRotateX(float rad);

/// <summary>
/// y軸回転
/// </summary>
/// <param name="rad">ラジアン</param>
/// <returns>y軸回転した行列</returns>
Mat4x4 MakeMatrixRotateY(float rad);

/// <summary>
/// z軸回転
/// </summary>
/// <param name="rad">ラジアン</param>
/// <returns>z軸回転した行列</returns>
Mat4x4 MakeMatrixRotateZ(float rad);

/// <summary>
/// アフィン
/// </summary>
/// <param name="scale">スケール</param>
/// <param name="rad">ラジアン</param>
/// <param name="translate">平行移動</param>
Mat4x4 MakeMatrixAffin(const Vector3D& scale, const Vector3D& rad, const Vector3D& translate);


/// <summary>
/// 逆行列
/// <para>失敗したら引数の行列を返す</para>
/// </summary>
/// <param name="mat">逆行列にしたい行列</param>
/// <returns>引数の逆行列</returns>
Mat4x4 MakeMatrixInverse(Mat4x4 mat);

/// <summary>
/// 転置行列
/// </summary>
/// <param name="mat">転置行列にしたい行列</param>
/// <returns>引数の転置行列</returns>
Mat4x4 MakeMatrixTransepose(Mat4x4 mat);

/// <summary>
	/// 投資投影
	/// </summary>
	/// <param name="fov"></param>
	/// <param name="aspectRatio"></param>
	/// <param name="nearClip"></param>
	/// <param name="farClip"></param>
Mat4x4 MakeMatrixPerspectiveFov(float fovY, float aspectRatio, float nearClip, float farClip);

/// <summary>
/// 正射影
/// </summary>
/// <param name="left"></param>
/// <param name="right"></param>
/// <param name="top"></param>
/// <param name="bottom"></param>
/// <param name="nearClip"></param>
/// <param name="farClip"></param>
Mat4x4 MakeMatrixOrthographic(float left, float top, float right, float bottom, float nearClip, float farClip);

/// <summary>
/// ビューポート
/// </summary>
/// <param name="left"></param>
/// <param name="right"></param>
/// <param name="top"></param>
/// <param name="bottom"></param>
/// <param name="minDepth"></param>
/// <param name="maxDepth"></param>
Mat4x4 MakeMatrixViewPort(float left, float top, float width, float height, float minDepth, float maxDepth);