#pragma once

#include "GLcamera.h"
#include "GLpoint.hpp"

struct PS4axes
{
	// L2��
	float L2;

	// L3��
	GLpoint2f L3;

	// R2��
	float R2;

	// R3��
	GLpoint2f R3;

	// �f�t�H���g�R���X�g���N�^
	PS4axes();

	// �R���X�g���N�^
	PS4axes(const float *axes);

	// �f�X�g���N�^
	virtual ~PS4axes();

	// �J�����ɓK�p����
	virtual void operator()(GLcamera &camera) const;
};
