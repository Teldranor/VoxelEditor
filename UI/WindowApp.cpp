#include "Window.h"
#include "App.h"

WindowApp::WindowApp(App* a) : Window(), _app(a) { }
WindowApp::~WindowApp() { }

void WindowApp::OnNewFrame() {
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Program")) {
				if (ImGui::MenuItem("Quit")) _app->setEndOfProgram(true);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void* WindowApp::getObject() {
	return _app;
}
