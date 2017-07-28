#pragma once

template<typename T, size_t N>
struct GLpoint
{
	T val[N];

	// �f�t�H���g�R���X�g���N�^
	GLpoint()
	{
	}

	// �R���X�g���N�^
	GLpoint(T v1, T v2, T v3, T v4)
		: val{ v1, v2, v3, v4 }
	{
	}

	// �R���X�g���N�^
	GLpoint(T v1, T v2, T v3)
		: val{ v1, v2, v3 }
	{
	}

	// �R���X�g���N�^
	GLpoint(T v1, T v2)
		: val{ v1, v2 }
	{
	}

	// �R�s�[�R���X�g���N�^
	GLpoint(const GLpoint<T, N> &point)
	{
		for (auto i = size_t(); i < N; i++) {
			new(val + i)T(point[i]);
		}
	}

	// ���[�u�R���X�g���N�^
	GLpoint(GLpoint<T, N> &&point)
	{
		for (auto i = size_t(); i < N; i++) {
			new(val + i)T(point[i]);
		}
	}

	// �f�X�g���N�^
	virtual ~GLpoint()
	{
	}

	// �v���~�e�B�u�|�C���^�ւ̕ϊ�
	operator const T*() const
	{
		return val;
	}

	// �v���~�e�B�u�|�C���^�ւ̕ϊ�
	operator T*()
	{
		return val;
	}

	// �C���f�b�N�X
	const T &operator[](size_t index) const
	{
		return val[index];
	}

	// �C���f�b�N�X
	T &operator[](size_t index)
	{
		return val[index];
	}

	// ���Z
	virtual GLpoint<T, N> &operator +=(const GLpoint<T, N> &point)
	{
		for (auto i = size_t(); i < N; i++) {
			val[i] += point[i];
		}
		return *this;
	}

	// ��Z
	virtual GLpoint<T, N> operator +(const GLpoint<T, N> &point) const
	{
		auto v = GLpoint<T, N>();
		for (auto i = size_t(); i < N; i++) {
			new(v.val + i)T(val[i] + point[i]);
		}
		return v;
	}

	// ��Z
	virtual GLpoint<T, N> &operator *=(const T arg)
	{
		for (auto i = size_t(); i < N; i++) {
			val[i] *= arg;
		}
		return *this;
	}

	// ��Z
	virtual GLpoint<T, N> operator *(const T arg) const
	{
		auto v = GLpoint<T, N>();
		for (auto i = size_t(); i < N; i++) {
			new(v.val + i)T(val[i] * arg);
		}
		return v;
	}

	// ����
	virtual T dot(const GLpoint<T, N> &point) const
	{
		auto d = T();
		for (auto i = size_t(); i < N; i++) {
			d += val[i] * point[i];
		}
		return d;
	}
};

template<typename T>
struct GLpoint2 : public GLpoint<T, 2>
{
	T &x, &y;

	// �f�t�H���g�R���X�g���N�^
	GLpoint2()
		: GLpoint(), x(val[0]), y(val[1])
	{
	}

	// �R���X�g���N�^
	GLpoint2(T x, T y)
		: GLpoint(x, y), x(val[0]), y(val[1])
	{
	}

	// �R�s�[�R���X�g���N�^
	GLpoint2(const GLpoint2<T> &p)
		: GLpoint(p), x(val[0]), y(val[1])
	{
	}

	// ���[�u�R���X�g���N�^
	GLpoint2(GLpoint2<T> &&p)
		: GLpoint(p), x(val[0]), y(val[1])
	{
	}

	// �^�ϊ�
	template<typename U>
	operator GLpoint2<U>() const
	{
		return GLpoint2<U>{ static_cast<U>(x), static_cast<U>(y) };
	}
};

typedef typename GLpoint2<GLdouble> GLpoint2d;
typedef typename GLpoint2<GLfloat> GLpoint2f;

template<typename T>
struct GLpoint3 : public GLpoint<T, 3>
{
	T &x, &y, &z;

	// �f�t�H���g�R���X�g���N�^
	GLpoint3()
		: GLpoint(), x(val[0]), y(val[1]), z(val[2])
	{
	}

	// �R���X�g���N�^
	GLpoint3(T x, T y, T z)
		: GLpoint(x, y, z), x(val[0]), y(val[1]), z(val[2])
	{
	}

	// �R�s�[�R���X�g���N�^
	GLpoint3(const GLpoint3<T> &p)
		: GLpoint(p), x(val[0]), y(val[1]), z(val[2])
	{
	}

	// ���[�u�R���X�g���N�^
	GLpoint3(GLpoint3<T> &&p)
		: GLpoint(std::move(p)), x(val[0]), y(val[1]), z(val[2])
	{
	}

	// �^�ϊ�
	template<typename U>
	operator GLpoint3<U>() const
	{
		return GLpoint3<U>{ static_cast<U>(x), static_cast<U>(y), static_cast<U>(z) };
	}

	// �^�ϊ�
	template<typename U>
	GLpoint<T, 4> operator +(U w) const
	{
		return GLpoint<T, 4>{ x, y, z, static_cast<T>(w) };
	}

	// �O��
	GLpoint3 cross(const GLpoint3 &point) const
	{
		return GLpoint3(y * point.z - z * point.y, z * point.x - x * point.z, x * point.y - y * point.x);
	}
};

typedef typename GLpoint3<GLdouble> GLpoint3d;
typedef typename GLpoint3<GLfloat> GLpoint3f;
