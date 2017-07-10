#include "glfw.h"

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	ImmDisableIME(-1);

	try {
		auto app = MyApplication();
		auto context = app.CreateContext(1280, 720, "glfw");
		if (!context) {
			throw std::exception("Can't create window");
		}
		auto thread = std::thread([&]() {
			context->MakeCurrent();
			app.ApplyCapabilities();
			app.BindTextureAt(0);
			while (!context->ShouldClose()) {
				app.Render();
				app.Update();
				context->SwapBuffers();
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		});
		while (!context->ShouldClose()) {
			glfwWaitEvents();
		}
		thread.join();
	}
	catch (const std::exception &e) {
		MessageBox(nullptr, e.what(), nullptr, MB_ICONHAND);
	}

	return 0;
}
