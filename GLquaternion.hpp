#pragma once

// �l����
template<typename T>
struct GLquaternion {
	// ������
	T i, j, k;

	// ������
	T w;

	// �f�t�H���g�R���X�g���N�^
	GLquaternion()
	{
	}

	// �R���X�g���N�^
	template<typename U>
	GLquaternion(const U i, const U j, const U k, const U w)
		: i(static_cast<T>(i)), j(static_cast<T>(j)), k(static_cast<T>(k)), w(static_cast<T>(w))
	{
	}

	// �f�X�g���N�^
	virtual ~GLquaternion()
	{
	}

	// �����l����
	virtual GLquaternion conj() const
	{
		return GLquaternion(-i, -j, -k, w);
	}

	// ������
	template<typename U>
	U imag() const
	{
		return U(i, j, k);
	}

	// �����l����
	virtual GLquaternion operator~() const
	{
		return conj();
	}

	// ��Z
	template<typename U>
	GLquaternion operator*(const GLquaternion<U> &q) const
	{
		return GLquaternion(
			i * q.w + w * q.i + j * q.k - k * q.j,
			j * q.w + w * q.j + k * q.i - i * q.k,
			k * q.w + w * q.k + i * q.j - j * q.i,
			w * q.w - i * q.i - j * q.j - k * q.k
		);
	}

	// ��Z
	template<template<typename> typename C, typename U>
	GLquaternion operator*(const C<U> &v) const
	{
		return GLquaternion(
			w * v.x + j * v.z - k * v.y,
			w * v.y + k * v.x - i * v.z,
			w * v.z + i * v.y - j * v.x,
			-(i * v.x + j * v.y + k * v.z)
		);
	}

	// �^�ϊ�
	template<typename U>
	operator GLquaternion<U>() const
	{
		return GLquaternion<U>(static_cast<U>(i), static_cast<U>(j), static_cast<U>(k), static_cast<U>(w));
	}
};

// �C�ӂ̎��ɑ΂����]�̂��߂̎l����
template<typename T, template<typename> typename C, typename U>
static auto make_quaternion(const C<U> &v, double theta)
{
	_ASSERT(v.dot(v) == 1);
	const auto a = theta / 2;
	const auto c = std::cos(a);
	const auto s = std::sin(a);
	return GLquaternion<T>(v.x * s, v.y * s, v.z * s, c);
}
