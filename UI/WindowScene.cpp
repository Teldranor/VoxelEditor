#include "Window.h"
#include "WindowManager.h"
#include "Scene.h"
#include "GameObject.h"

WindowScene::WindowScene(Scene* s) : Window(), _scene(s) { }
WindowScene::~WindowScene() { }

void WindowScene::OnNewFrame() {
	std::vector<GameObject*> goList = _scene->getGameObjects();
	GameObject* go;
	if(ImGui::Begin("SceneViewer", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse)) {
		if (ImGui::CollapsingHeader("GameObjects")) {
			for (int i = 0; i < _scene->getGetGameObjectSize(); i++) {
				go = goList.at(i);
				char str[32];
				sprintf(str, "%s", go->getName().c_str());
				ImGui::Bullet();
				if (ImGui::Selectable(str, &bl[i])) {
					WindowManager::getWindowManager()->instanciate(WINGO, go);
					if (!bl[i]) WindowManager::getWindowManager()->free(go);
				}
			}
		}
		ImGui::End();
	}
}

void* WindowScene::getObject() {
	return _scene;
}
