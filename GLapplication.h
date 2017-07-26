#pragma once

#include "GLcontext.h"

class GLapplication
{
	friend class GLcontext;

protected:
	// �`�悷��[�`��X���b�h����Ă΂��]
	virtual void Render() = 0;

	// ����������[�`��X���b�h����Ă΂��]
	virtual void Setup() = 0;

	// �X�V����[�`��X���b�h����Ă΂��]
	virtual void Update() = 0;

public:
	// �f�t�H���g�R���X�g���N�^
	GLapplication();

	// �f�X�g���N�^
	virtual ~GLapplication();

	// �E�B���h�E�𐶐�����
	virtual std::shared_ptr<GLcontext> CreateContext(int width, int height, const char *title);

	// �A�v���P�[�V���������s����[���C���X���b�h����Ă΂��]
	virtual void Run(std::shared_ptr<GLcontext> &context);
};
