#pragma once

template<typename T>
struct GLcolor4
{
	T val[4], &red, &green, &blue, &alpha;

	// �f�t�H���g�R���X�g���N�^
	GLcolor4()
		: GLcolor4(0, 0, 0, 1)
	{
	}

	// �R���X�g���N�^
	GLcolor4(T red, T green, T blue, T alpha = 1.0)
		: val{ red, green, blue, alpha }, red(val[0]), green(val[1]), blue(val[2]), alpha(val[3])
	{
	}

	// �^�ϊ�
	template<typename U>
	operator GLcolor4<U>() const
	{
		return GLcolor4<U>{ static_cast<U>(red), static_cast<U>(green), static_cast<U>(blue), static_cast<U>(alpha) };
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
};

typedef typename GLcolor4<GLdouble> GLcolor4d;
typedef typename GLcolor4<GLfloat> GLcolor4f;

namespace GLcolor {
	// ��
	static const GLcolor4d White = GLcolor4d{ 1, 1, 1 };

	// �ƂĂ����邢�O���[
	static const GLcolor4d BrightGray = GLcolor4d{ 0.75, 0.75, 0.75 };

	// ���邢�O���[
	static const GLcolor4d LightGray = GLcolor4d{ 0.5, 0.5, 0.5 };

	// �O���[
	static const GLcolor4d Gray = GLcolor4d{ 0.25, 0.25, 0.25 };

	// �Â��O���[
	static const GLcolor4d DarkGray = GLcolor4d{ 0.125, 0.125, 0.125 };
}
