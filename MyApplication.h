#pragma once

#include "GLapplication.h"
#include "GLcamera.h"
#include "GLsphere.h"
#include "GLtexture.h"
#include "GLtorus.h"

class MyApplication : public GLapplication, public GLcamera {
private:
	// �A�X�y�N�g��
	GLdouble aspect;

	// �}�E�X�J�[�\���̍��W
	GLpoint3d cursor;

	// �h���b�O���
	std::shared_ptr<GLpoint3d> drag;

	// �e�N�X�`���摜�̓ǂݍ��ݗv��
	std::deque<size_t> queue;

	// ��]
	GLdouble rotation;

	// ����
	GLsphere sphere;

	// �`��Ώ�
	GLquadric *target;

	// �e�N�X�`��
	std::vector<GLtexture> textures;

	// �g�[���X
	GLtorus torus;

	// �E�B���h�E�̍���
	int windowHeight;

	// �E�B���h�E�̕�
	int windowWidth;

	// �L�[�C�x���g����������
	void KeyEvent(int key, int scan, int action, int mods);

	// �}�E�X�C�x���g����������
	void MouseEvent(int button, int action, int mods);

public:
	// �f�t�H���g�R���X�g���N�^
	MyApplication();

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
