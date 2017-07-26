#pragma once

#include "GLcontext.h"

class GLapplication
{
public:
	// �f�t�H���g�R���X�g���N�^
	GLapplication();

	// �f�X�g���N�^
	virtual ~GLapplication();

	// �E�B���h�E�𐶐�����
	virtual std::shared_ptr<GLcontext> CreateContext(int width, int height, const char *title);

	// �A�v���P�[�V���������s����
	virtual void Run(std::shared_ptr<GLcontext> &context) = 0;
};
