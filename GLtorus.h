#pragma once

#include "GLquadric.h"
#include "GLtorusVertex.h"

class GLtorus : public GLquadric
{
private:
	// �����a
	GLdouble radiusInner;

	// �唼�a
	GLdouble radiusOuter;

	// �c����
	const std::vector<GLtorusVertex> slices;

	// ������
	const std::vector<GLtorusVertex> stacks;

public:
	// �J�n�I�t�Z�b�g(deg)
	GLdouble offset;

private:
	//
	void Draw(const GLtorusVertex &s, const GLtorusVertex &t) const;

public:
	// �R���X�g���N�^
	GLtorus(GLdouble radiusOuter, GLdouble radiusInner, GLint slices, GLint stacks);

	// �`�悷��
	virtual void Draw(GLdouble rotation);
};
