#pragma once

class GLquadric
{
protected:
	GLUquadric *state;

public:
	// �f�t�H���g�R���X�g���N�^
	GLquadric();

	// �R���X�g���N�^
	GLquadric(GLUquadric *state);

	// �f�X�g���N�^
	virtual ~GLquadric();

public:
	// �e�N�X�`���L��
	void EnableTexture();

	// �`�����
	void SetDrawStyle(GLenum drawStyle);

	// �@��
	void SetNormals(GLenum normals);

	// ���̂�`�悷��
	void Sphere(GLdouble radius, GLint slices, GLint stacks);

	// �g�[���X��`�悷��
	void Torus(GLdouble radius, GLdouble small, GLint slices, GLint stacks, const std::function<void(GLdouble, GLdouble)> &texCoord = [](GLdouble s, GLdouble t) { glTexCoord2d(1 - s, t - 0.5); });
};
