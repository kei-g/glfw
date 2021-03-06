#include "GLcontext.h"

#include "GLapplication.h"

GLcontext::GLcontext(GLapplication &app, GLFWwindow *window)
	: app(app), window(window)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y) {
		auto context = GLcontext::FromWindow(window);
		if (context && context->cursorEvent) {
			context->cursorEvent(x, y);
		}
	});
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
		auto context = GLcontext::FromWindow(window);
		if (context && context->resizeEvent) {
			context->resizeEvent(width, height);
		}
	});
	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scan, int action, int mods) {
		auto context = GLcontext::FromWindow(window);
		if (context && context->keyEvent) {
			context->keyEvent(key, scan, action, mods);
		}
	});
	glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
		auto context = GLcontext::FromWindow(window);
		if (context && context->mouseEvent) {
			context->mouseEvent(button, action, mods);
		}
	});
	glfwSetScrollCallback(window, [](GLFWwindow *window, double x, double y) {
		auto context = GLcontext::FromWindow(window);
		if (context && context->scrollEvent) {
			context->scrollEvent(x, y);
		}
	});
}

GLcontext::~GLcontext()
{
	glfwDestroyWindow(window);
}

void GLcontext::MakeCurrent()
{
	glfwMakeContextCurrent(window);
}

void GLcontext::Run()
{
	// 描画スレッド
	auto renderer = std::thread([&]() {
		MakeCurrent();
		app.Setup();
		while (!ShouldClose()) {
			app.Render();
			app.Update();
			SwapBuffers();
		}
	});

	// イベントループ
	while (!ShouldClose()) {
		glfwWaitEvents();
	}

	// 描画スレッドが終了するまで待機
	renderer.join();
}

void GLcontext::SetCursorCallback(const std::function<void(double, double)> &cbfunc)
{
	cursorEvent = cbfunc;
}

void GLcontext::SetKeyCallback(const std::function<void(int, int, int, int)> &cbfunc)
{
	keyEvent = cbfunc;
}

void GLcontext::SetMouseCallback(const std::function<void(int, int, int)> &cbfunc)
{
	mouseEvent = cbfunc;
}

void GLcontext::SetResizeCallback(const std::function<void(int, int)> &cbfunc)
{
	resizeEvent = cbfunc;
}

void GLcontext::SetScrollCallback(const std::function<void(double, double)> &cbfunc)
{
	scrollEvent = cbfunc;
}

bool GLcontext::ShouldClose() const
{
	return !!glfwWindowShouldClose(window);
}

void GLcontext::SwapBuffers()
{
	glfwSwapBuffers(window);
}

GLcontext *GLcontext::FromWindow(GLFWwindow *window)
{
	return static_cast<GLcontext *>(glfwGetWindowUserPointer(window));
}
