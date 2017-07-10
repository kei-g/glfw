#pragma once

#include "GLapplication.h"
#include "GLcamera.h"
#include "GLquadric.h"
#include "GLtexture.h"

class MyApplication : public GLapplication, public GLcamera, protected GLquadric {
private:
	// �A�X�y�N�g��
	GLdouble aspect;

	// ��]
	GLdouble rotation;

	// ��or�g�[���X
	bool sphere;

	// �e�N�X�`��
	std::vector<GLtexture> textures;

	// �g�[���X�̃I�t�Z�b�g
	GLdouble torusOffset;

	// �L�[�C�x���g����������
	void KeyEvent(int key, int scan, int action, int mods);

public:
	// �f�t�H���g�R���X�g���N�^
	MyApplication(HMODULE hModule);

	// �K�v�ȋ@�\��L���ɂ���
	void ApplyCapabilities();

	// �g�p����e�N�X�`�����w�肷��
	void BindTextureAt(size_t pos);

	// �E�B���h�E�𐶐�����
	virtual std::shared_ptr<GLcontext> CreateContext(int width, int height, const char *title);

	// �`�悷��
	void Render();

	// �X�V����
	void Update();
};
