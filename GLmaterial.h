#pragma once

#include "GLcolor4.hpp"

struct GLmaterial
{
	GLcolor4f ambient;
	GLcolor4f diffuse;
	GLcolor4f specular;
	GLfloat shininess;

	// �f�t�H���g�R���X�g���N�^
	GLmaterial();

	// �R���X�g���N�^
	GLmaterial(const GLcolor4f &ambient, const GLcolor4f &diffuse, const GLcolor4f &specular, GLfloat shininess = 32.0f);

	// �f�X�g���N�^
	virtual ~GLmaterial();

	// ���̍ގ���K�p����
	void operator()(GLenum face) const;

	// �Ő�
	static const GLmaterial Jade;

	// ���邢
	static const GLmaterial Light;

	// ���r�[
	static const GLmaterial Ruby;

	// ��
	static const GLmaterial White;
};
