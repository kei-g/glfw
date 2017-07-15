#pragma once

#include "GLpoint.hpp"

struct GLcamera : public GLpoint3d
{
	// �����̌���(deg)
	GLpoint2d gaze;

	// �f�t�H���g�R���X�g���N�^
	GLcamera();

	// �R���X�g���N�^
	GLcamera(double x, double y, double z, double direction = 0);

	// �����x�N�g��
	GLpoint3d GetVector() const;

	// ������K�p����
	void LookAt();

	// �����̕����֐i��
	void MoveAhead(double distance);

	// �������Ɉړ�����
	void Shift(double distance);
};
