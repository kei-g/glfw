#include "glfw.h"

// �ԓ��X�Ίp
constexpr auto Obliquity = 23.43;

// ���\�[�XID
constexpr int resourceIDs[] = { IDR_IMAGE_EARTH, IDR_IMAGE_DQ2, IDR_IMAGE_DQ3, IDR_IMAGE_DQ4, IDR_IMAGE_DQ5 };

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	ImmDisableIME(-1);

	try {
		auto app = GLapplication();

		auto context = app.CreateContext(1280, 720, "glfw");
		if (!context) {
			throw std::exception("Can't create window");
		}

		context->MakeCurrent();
		glfwSwapInterval(1);

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0, 0, 0, 1);

		// �e�N�X�`���쐬
		auto textures = GLtexture::Generate(hInstance, resourceIDs, TEXT("Image"));
		textures[0].Bind();

		// �\���I�u�W�F�N�g�̎��
		auto sphere = true;

		// �g�[���X�̃e�N�X�`���̊J�n�I�t�Z�b�g
		auto torusOffset = 0.5;

		// �J����
		auto camera = GLcamera{ -3, 0, 0 };

		// �L�[����
		context->SetKeyCallback([&](int key, int scan, int action, int mods) {
			switch (key) {
			case GLFW_KEY_F:
				camera.MoveAhead(static_cast<double>(1) / 128);
				break;
			case GLFW_KEY_B:
				camera.MoveAhead(static_cast<double>(-1) / 128);
				break;
			case GLFW_KEY_UP:
				camera.y += static_cast<double>(1) / 128;
				break;
			case GLFW_KEY_DOWN:
				camera.y -= static_cast<double>(1) / 128;
				break;
			case GLFW_KEY_LEFT:
				camera.direction -= 0.5;
				break;
			case GLFW_KEY_RIGHT:
				camera.direction += 0.5;
				break;
			case GLFW_KEY_1:
				textures[0].Bind();
				break;
			case GLFW_KEY_2:
				textures[1].Bind();
				break;
			case GLFW_KEY_3:
				textures[2].Bind();
				break;
			case GLFW_KEY_4:
				textures[3].Bind();
				break;
			case GLFW_KEY_5:
				textures[4].Bind();
				break;
			case GLFW_KEY_S:
				sphere = true;
				break;
			case GLFW_KEY_T:
				sphere = false;
				break;
			case GLFW_KEY_O:
				if (!sphere) {
					torusOffset += static_cast<double>(1) / 128;
				}
				break;
			case GLFW_KEY_L:
				if (!sphere) {
					torusOffset -= static_cast<double>(1) / 128;
				}
				break;
			case GLFW_KEY_C:
				if (action == GLFW_RELEASE) {
					camera.lookAtCenter = !camera.lookAtCenter;
				}
				break;
			}
		});

		// �A�X�y�N�g��
		auto aspect = 16.0 / 9;
		context->SetResizeCallback([&aspect](int w, int h) {
			aspect = static_cast<double>(w) / h;
		});

		// �I�u�W�F�N�g�𐶐�
		auto quadric = GLquadric();
		quadric.SetDrawStyle(GLU_FILL);
		quadric.SetNormals(GLU_SMOOTH);
		quadric.EnableTexture();

		auto angle = double();
		while (!context->ShouldClose()) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(60, aspect, GLepsilon, 128);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			camera.LookAt();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// �J�����̈ʒu�Ɍ�����z�u
			glLightfv(GL_LIGHT0, GL_POSITION, static_cast<GLpoint3f>(camera) + 1); // 0: ���s����, 0�ȊO: �_����
			glLightfv(GL_LIGHT0, GL_AMBIENT, static_cast<GLcolor4f>(GLcolor::Gray));
			glLightfv(GL_LIGHT0, GL_DIFFUSE, static_cast<GLcolor4f>(GLcolor::LightGray));
			glLightfv(GL_LIGHT0, GL_SPECULAR, static_cast<GLcolor4f>(GLcolor::White));

			// �I�u�W�F�N�g��`��
			GLmaterial::Light(GL_FRONT);
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			if (sphere) {
				glRotated(angle, 0, cos(Obliquity * M_PI / 180), sin(Obliquity * M_PI / 180)); // �n���ɑ΂����]
				glRotated(Obliquity - 90, 1, 0, 0); // �n���̌X�����Č�����
				quadric.Sphere(1, 32, 32);
			}
			else {
				glRotated(angle, 0, 1, 0);
				quadric.Torus(0.875, 0.375, 128, 128, [&torusOffset](GLdouble s, GLdouble t) {
					glTexCoord2d(1 - s, t - torusOffset);
				});
			}
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();

			// �I�u�W�F�N�g����]������
			angle += 0.0625;
			if (360 < angle) {
				angle -= 360;
			}

			context->SwapBuffers();

			glfwWaitEventsTimeout(0.015625);
		}
	}
	catch (const std::exception &e) {
		MessageBox(nullptr, e.what(), nullptr, MB_ICONHAND);
	}

	return 0;
}
