#include "MyApplication.h"

#include "GLmaterial.h"
#include "resource.h"

void MyApplication::KeyEvent(int key, int scan, int action, int mods)
{
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
		direction -= 0.5;
		break;
	case GLFW_KEY_RIGHT:
		direction += 0.5;
		break;
	case GLFW_KEY_1:
		queue.push_back(0);
		break;
	case GLFW_KEY_2:
		queue.push_back(1);
		break;
	case GLFW_KEY_3:
		queue.push_back(2);
		break;
	case GLFW_KEY_4:
		queue.push_back(3);
		break;
	case GLFW_KEY_5:
		queue.push_back(4);
		break;
	case GLFW_KEY_S:
		target = &sphere;
		break;
	case GLFW_KEY_T:
		target = &torus;
		break;
	case GLFW_KEY_O:
		torus.offset += static_cast<double>(1) / 128;
		break;
	case GLFW_KEY_L:
		torus.offset -= static_cast<double>(1) / 128;
		break;
	case GLFW_KEY_C:
		if (action == GLFW_RELEASE) {
			lookAtCenter = !lookAtCenter;
		}
		break;
	}
}

void MyApplication::MouseEvent(int button, int action, int mods)
{
	switch (action) {
	case GLFW_RELEASE:
		switch (button) {
		case GLFW_MOUSE_BUTTON_1:
			drag = nullptr;
			break;
		}
		break;
	case GLFW_PRESS:
		switch (button) {
		case GLFW_MOUSE_BUTTON_1:
			drag = std::shared_ptr<GLpoint3d>(new GLpoint3d{ cursor.x, cursor.y, direction });
			break;
		}
		break;
	case GLFW_REPEAT:
		break;
	}
}

MyApplication::MyApplication()
	: GLcamera(-3, 0, 0), drag(nullptr), rotation(0), sphere(1, 32, 32), target(&sphere), torus(0.875, 0.375, 128, 128)
{
	sphere.SetDrawStyle(GLU_FILL);
	sphere.SetNormals(GLU_SMOOTH);
	sphere.EnableTexture();
}

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
		// リソースID
		constexpr int resourceIDs[] = { IDR_IMAGE_EARTH, IDR_IMAGE_DQ2, IDR_IMAGE_DQ3, IDR_IMAGE_DQ4, IDR_IMAGE_DQ5 };

		// リソースからテクスチャを生成する
		GLtexture::Generate(&textures, GetModuleHandle(nullptr), resourceIDs, TEXT("Image"));
	}

	textures[pos].Bind();
}

std::shared_ptr<GLcontext> MyApplication::CreateContext(int width, int height, const char *title)
{
	auto context = GLapplication::CreateContext(width, height, title);

	windowWidth = width;
	windowHeight = height;
	context->SetCursorCallback([&](GLdouble x, GLdouble y) {
		cursor.x = x / windowWidth;
		cursor.y = y / windowHeight;
		if (drag && !lookAtCenter) {
			direction = fmod(drag->z + (cursor.x - drag->x) * 60, 360);
		}
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

	return context;
}

void MyApplication::Render()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, aspect, GLepsilon, 128);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	LookAt();

	// 消去
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// カメラの位置に光源を配置
	glLightfv(GL_LIGHT0, GL_POSITION, static_cast<GLpoint3f>(*this) + 1); // 0: 並行光源, 0以外: 点光源
	glLightfv(GL_LIGHT0, GL_AMBIENT, static_cast<GLcolor4f>(GLcolor::Gray));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, static_cast<GLcolor4f>(GLcolor::LightGray));
	glLightfv(GL_LIGHT0, GL_SPECULAR, static_cast<GLcolor4f>(GLcolor::White));

	// オブジェクトを描画する
	GLmaterial::Light(GL_FRONT);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	target->Draw(rotation);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void MyApplication::Update()
{
	// オブジェクトを回転させる
	rotation += 0.0625;
	if (360 < rotation) {
		rotation -= 360;
	}

	// テクスチャ画像の読み込み要求を処理する
	while (!queue.empty()) {
		auto pos = queue.front();
		queue.pop_front();
		BindTextureAt(pos);
	}
}
