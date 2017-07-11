#pragma once

#include "GLapplication.h"
#include "GLcamera.h"
#include "GLsphere.h"
#include "GLtexture.h"
#include "GLtorus.h"

class MyApplication : public GLapplication, public GLcamera {
private:
	struct DragContext {
		const int button;
		const int mods;
		const GLpoint2d cursor;
		const GLdouble direction;
		DragContext(int button, int mods, const GLpoint2d &cursor, GLdouble direction)
			: button(button), mods(mods), cursor(cursor), direction(direction)
		{
		}
	};

	// �A�X�y�N�g��
	GLdouble aspect;

	// �}�E�X�J�[�\���̍��W
	GLpoint2d cursor;

	// �h���b�O���
	std::shared_ptr<DragContext> dragContext;

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

	// �J�[�\���C�x���g����������
	void CursorEvent(GLdouble x, GLdouble y);

	// �h���b�O�C�x���g����������
	void DragEvent(GLdouble dx, GLdouble dy);

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
