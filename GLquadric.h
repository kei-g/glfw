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
	// �`�悷��
	virtual void Draw(GLdouble rotation) = 0;

	// �e�N�X�`���L��
	void EnableTexture();

	// �`�����
	void SetDrawStyle(GLenum drawStyle);

	// �@��
	void SetNormals(GLenum normals);

	// ���̂�`�悷��
	void Sphere(GLdouble radius, GLint slices, GLint stacks);
};
