#pragma once

// �g�[���X�̒��_���
struct GLtorusVertex
{
	// �]��
	GLdouble cos;

	// ����
	GLdouble sin;

	// �}��ϐ�
	GLdouble t;

	// �R���X�g���N�^
	GLtorusVertex(GLdouble t, GLdouble radian);

	// �g�[���X�̒��_���𐶐�����
	static std::vector<GLtorusVertex> Build(GLint N);

	// �Öق̌^�ϊ�
	operator GLdouble() const;
};
