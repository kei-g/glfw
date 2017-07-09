#pragma once

#include "GLpoint.hpp"

struct GLcamera : public GLpoint3d
{
	// �����̌���(deg)
	double direction;

	// ���S������
	bool lookAtCenter;

	// �f�t�H���g�R���X�g���N�^
	GLcamera();

	// �R���X�g���N�^
	GLcamera(double x, double y, double z, double direction = 0);

	// ������K�p����
	void LookAt();

	// �����̕����֐i��
	void MoveAhead(double distance);
};
