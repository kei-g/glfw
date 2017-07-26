#include "MyApplication.h"

#include "GLmaterial.h"
#include "PS4joystick.h"

#include "cage.hpp"
#include "resource.h"

void MyApplication::ApplyCapabilities()
{
	glfwSwapInterval(1);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0, 0, 0, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void MyApplication::BindTextureAt(size_t pos)
{
	if (textures.empty()) {
		// ���\�[�XID
		constexpr int resourceIDs[] = { IDR_IMAGE_EARTH, IDR_IMAGE_DQ2, IDR_IMAGE_DQ3, IDR_IMAGE_DQ4, IDR_IMAGE_DQ5 };

		// ���\�[�X����e�N�X�`���𐶐�����
		GLtexture::Generate(&textures, GetModuleHandle(nullptr), resourceIDs, TEXT("Image"));
	}

	textures[pos].Read();
	queue.push_back(pos);
}

void MyApplication::CursorEvent(GLdouble x, GLdouble y)
{
	cursor.x = x /= windowWidth;
	cursor.y = y /= windowHeight;
	if (dragContext) {
		DragEvent(x - dragContext->last.x, y - dragContext->last.y);
		dragContext->last.x = x;
		dragContext->last.y = y;
	}
}

void MyApplication::DragEvent(GLdouble dx, GLdouble dy)
{
}

void MyApplication::KeyEvent(int key, int scan, int action, int mods)
{
	switch (action) {
	case GLFW_RELEASE:
		switch (key) {
		case GLFW_KEY_1:
			BindTextureAt(0);
			break;
		case GLFW_KEY_2:
			BindTextureAt(1);
			break;
		case GLFW_KEY_3:
			BindTextureAt(2);
			break;
		case GLFW_KEY_4:
			BindTextureAt(3);
			break;
		case GLFW_KEY_5:
			BindTextureAt(4);
			break;
		case GLFW_KEY_S:
			target = &sphere;
			break;
		case GLFW_KEY_T:
			target = &torus;
			break;
		}
		break;
	case GLFW_PRESS:
	case GLFW_REPEAT:
		switch (key) {
		case GLFW_KEY_F:
			MoveAhead(static_cast<double>(1) / 128);
			break;
		case GLFW_KEY_B:
			MoveAhead(static_cast<double>(-1) / 128);
			break;
		case GLFW_KEY_UP:
			y += static_cast<double>(1) / 128;
			break;
		case GLFW_KEY_DOWN:
			y -= static_cast<double>(1) / 128;
			break;
		case GLFW_KEY_LEFT:
			gaze.x = fmod(gaze.x - 0.5, 360);
			break;
		case GLFW_KEY_RIGHT:
			gaze.x = fmod(gaze.x + 0.5, 360);
			break;
		case GLFW_KEY_O:
			torus.offset += static_cast<double>(1) / 128;
			break;
		case GLFW_KEY_L:
			torus.offset -= static_cast<double>(1) / 128;
			break;
		}
		break;
	}
}

void MyApplication::MouseEvent(int button, int action, int mods)
{
	switch (action) {
	case GLFW_RELEASE:
		if (dragContext && dragContext->button == button) {
			dragContext = nullptr;
		}
		switch (button) {
		case GLFW_MOUSE_BUTTON_1:
			gaze.x = fmod(gaze.x + (cursor.x - 0.5) * aspect * 60, 360);
			gaze.y = cage::clip(-45.0, gaze.y + (cursor.y - 0.5) * 60, 45.0);
			break;
		}
		break;
	case GLFW_PRESS:
		if (!dragContext) {
			dragContext = std::make_shared<DragContext>(button, mods, cursor);
		}
		break;
	case GLFW_REPEAT:
		break;
	}
}

void MyApplication::ScrollEvent(double x, double y)
{
	if (x != 0) {
		GLcamera::Shift(x / 16);
	}
	if (y != 0) {
		GLcamera::MoveAhead(y / 16);
	}
}

void MyApplication::Render()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, aspect, GLepsilon, 128);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	LookAt();

	// ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �J�����̈ʒu�Ɍ�����z�u
	glLightfv(GL_LIGHT0, GL_POSITION, static_cast<GLpoint3f>(*this) + 1); // 0: ���s����, 0�ȊO: �_����
	glLightfv(GL_LIGHT0, GL_AMBIENT, static_cast<GLcolor4f>(GLcolor::Gray));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, static_cast<GLcolor4f>(GLcolor::LightGray));
	glLightfv(GL_LIGHT0, GL_SPECULAR, static_cast<GLcolor4f>(GLcolor::White));

	// �O���b�h��`�悷��
	GLmaterial::Jade(GL_FRONT);
	glBegin(GL_LINES);
	for (auto i = -10; i <= 10; i++) {
		glVertex3d(i, -1, -10);
		glVertex3d(i, -1, +10);
		glVertex3d(-10, -1, i);
		glVertex3d(+10, -1, i);
		glVertex3d(i, 1, -10);
		glVertex3d(i, 1, +10);
		glVertex3d(-10, 1, i);
		glVertex3d(+10, 1, i);
	}
	glEnd();

	// �I�u�W�F�N�g��`�悷��
	GLmaterial::Light(GL_FRONT);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	target->Draw(rotation);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void MyApplication::Setup()
{
	ApplyCapabilities();
	BindTextureAt(0);
}

void MyApplication::Update()
{
	// �I�u�W�F�N�g����]������
	rotation += 0.0625;
	if (360 < rotation) {
		rotation -= 360;
	}

	// �e�N�X�`���摜�̓ǂݍ��ݗv������������
	if (!queue.empty()) {
		auto pos = queue.front();
		queue.pop_front();
		textures[pos].Bind();
	}
}

MyApplication::MyApplication()
	: GLcamera(-3, 0, 0), dragContext(nullptr), rotation(0), sphere(1, 32, 32), target(&sphere), torus(0.875, 0.375, 128, 128)
{
	sphere.SetDrawStyle(GLU_FILL);
	sphere.SetNormals(GLU_SMOOTH);
	sphere.EnableTexture();
}

std::shared_ptr<GLcontext> MyApplication::CreateContext(int width, int height, const char *title)
{
	auto context = GLapplication::CreateContext(width, height, title);

	windowWidth = width;
	windowHeight = height;

	context->SetCursorCallback([&](GLdouble x, GLdouble y) {
		CursorEvent(x, y);
	});

	context->SetKeyCallback([&](int key, int scan, int action, int mods) {
		KeyEvent(key, scan, action, mods);
	});

	context->SetMouseCallback([&](int button, int action, int mods) {
		MouseEvent(button, action, mods);
	});

	aspect = static_cast<double>(width) / height;
	context->SetResizeCallback([&](int w, int h) {
		aspect = static_cast<double>(w) / h;
		windowWidth = w;
		windowHeight = h;
	});

	context->SetScrollCallback([&](double x, double y) {
		ScrollEvent(x, y);
	});

	return context;
}

void MyApplication::Run(std::shared_ptr<GLcontext> &context)
{
	// PS4�R���g���[�����͊Ď��X���b�h
	auto input = std::thread([&]() {
		auto ps4 = PS4joystick(GLFW_JOYSTICK_1); // PS4�R���g���[��
		auto axes = PS4axes(); // PS4�R���g���[���̏��
		while (!context->ShouldClose()) {
			ps4.Poll(axes);
			axes(*this);
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	});

	// ���N���X�̏��������s����
	GLapplication::Run(context);

	// PS4�R���g���[�����͊Ď��X���b�h���I������܂őҋ@
	input.join();
}
