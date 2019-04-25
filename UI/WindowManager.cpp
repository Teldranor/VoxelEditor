#include "WindowManager.h"

WindowManager* WindowManager::_factory = 0;

WindowManager* WindowManager::getWindowManager(){
    if(!(_factory)){
        _factory = new WindowManager();
    }
    return _factory;
}

WindowManager::WindowManager() { }

WindowManager::~WindowManager() {
	_windows.clear();
}

void WindowManager::init(SDL_Window* w) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSdlGL3_Init(w);
	ImGui::StyleColorsDark();
}

int WindowManager::search(void* object) {
	int i = 0;
	while (i != _windows.size()) {
		if (_windows.at(i)->getObject() == object) return i;
		i++;
	}
	return -1;
}

void WindowManager::instanciate(int tag, void* object) {
	if (search(object) >= 0) { }
	else {
		switch (tag) {
			case WINAPP : _windows.push_back(new WindowApp((App*) object)); break;
			case WINSCENE : _windows.push_back(new WindowScene((Scene*) object)); break;
			case WINGO : _windows.push_back(new WindowGameObject((GameObject*) object)); break;
			case WINCOM : _windows.push_back(new WindowComponent((Component *) object)); break;
		}
		_windows.at(_windows.size() - 1)->Start();
	}
}

void WindowManager::free(void* object) {
	int i = search(object);
	if (i >= 0) { 
		_windows.at(i)->~Window();
		_windows.erase(_windows.begin() + i);
	}	
}

void WindowManager::render(SDL_Window* w) {
	ImGui_ImplSdlGL3_NewFrame(w);
	for (int i=0; i < _windows.size(); i++) {
		_windows.at(i)->OnNewFrame();
	}
	ImGui::Render();
	ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());
}

void WindowManager::destroy() {
	ImGui_ImplSdlGL3_Shutdown();
	ImGui::DestroyContext();
}

void WindowManager::event(SDL_Event* ev) {
	ImGui_ImplSdlGL3_ProcessEvent(ev);
}
