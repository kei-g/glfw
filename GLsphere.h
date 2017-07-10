#pragma once

#include "GLquadric.h"

class GLsphere : public GLquadric
{
private:
	// ���a
	GLdouble radius;

	// �������̕�����
	GLint slices;

	// �c�����̕�����
	GLint stacks;

public:
	// �R���X�g���N�^
	GLsphere(GLdouble radius, GLint slices, GLint stacks);

	// �`�悷��
	virtual void Draw(GLdouble rotation);
};
