#pragma once

#include "GLapplication.h"
#include "GLcamera.h"
#include "GLsphere.h"
#include "GLtexture.h"
#include "GLtorus.h"

class MyApplication : public GLapplication, public GLcamera {
private:
	struct DragContext {
		// �{�^��
		const int button;

		// �O��̍��W
		GLpoint2d last;

		// ���
		const int mods;

		// �h���b�O�J�n���W
		const GLpoint2d origin;

		// �R���X�g���N�^
		DragContext(int button, int mods, const GLpoint2d &cursor)
			: button(button), last(cursor), mods(mods), origin(origin)
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

	// �K�v�ȋ@�\��L���ɂ���
	void ApplyCapabilities();

	// �g�p����e�N�X�`�����w�肷��
	void BindTextureAt(size_t pos);

	// �J�[�\���C�x���g����������
	void CursorEvent(GLdouble x, GLdouble y);

	// �h���b�O�C�x���g����������
	void DragEvent(GLdouble dx, GLdouble dy);

	// �L�[�C�x���g����������
	void KeyEvent(int key, int scan, int action, int mods);

	// �}�E�X�C�x���g����������
	void MouseEvent(int button, int action, int mods);

	// �X�N���[���C�x���g����������
	void ScrollEvent(double x, double y);

protected:
	// �`�悷��[�`��X���b�h����Ă΂��]
	virtual void Render();

	// ����������[�`��X���b�h����Ă΂��]
	virtual void Setup();

	// �X�V����[�`��X���b�h����Ă΂��]
	virtual void Update();

public:
	// �f�t�H���g�R���X�g���N�^
	MyApplication();

	// �E�B���h�E�𐶐�����
	virtual std::shared_ptr<GLcontext> CreateContext(int width, int height, const char *title);

	// �A�v���P�[�V���������s����
	virtual void Run(std::shared_ptr<GLcontext> &context);
};
