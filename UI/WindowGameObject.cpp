#include "Window.h"
#include "WindowManager.h"
#include "GameObject.h"
#include "CubeModel.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Script.h"
#include <glm/glm.hpp>

WindowGameObject::WindowGameObject(GameObject* g) : Window(), _gameObject(g), bl { false } { }
WindowGameObject::~WindowGameObject() { }

void WindowGameObject::OnNewFrame() {
	float delta = 0.1f;
	std::vector<Component*> cList = _gameObject->getComponents();
	Component* c;

	const void * address = static_cast<const void*>(_gameObject);
	std::stringstream ss;
	ss <<  _gameObject->getName() << "##" << address;
	std::string name = ss.str();

	ImGui::Begin((name).c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::Text("Position X:%.2f Y:%.2f Z:%.2f", _gameObject->getPosition().x, _gameObject->getPosition().y, _gameObject->getPosition().z);
		ImGui::Columns(3, "mycolumns4");
		ImGui::Separator();
		ImGui::Text("X"); ImGui::NextColumn();
		ImGui::Text("Y"); ImGui::NextColumn();
		ImGui::Text("Z"); ImGui::NextColumn();
		ImGui::Separator();
		if (ImGui::ArrowButton("Left", ImGuiDir_Left)) {
			_gameObject->setPosition(_gameObject->getPosition().x - delta, _gameObject->getPosition().y, _gameObject->getPosition().z);
		}
		ImGui::SameLine();
		if (ImGui::ArrowButton("Right", ImGuiDir_Right)) {
			_gameObject->setPosition(_gameObject->getPosition().x + delta, _gameObject->getPosition().y, _gameObject->getPosition().z);
		}
		ImGui::NextColumn();	
		if (ImGui::ArrowButton("Up", ImGuiDir_Left)) {
			_gameObject->setPosition(_gameObject->getPosition().x, _gameObject->getPosition().y + delta, _gameObject->getPosition().z);
		}
		ImGui::SameLine();
		if (ImGui::ArrowButton("Down", ImGuiDir_Right)) {
			_gameObject->setPosition(_gameObject->getPosition().x, _gameObject->getPosition().y - delta, _gameObject->getPosition().z);
		}
		ImGui::NextColumn();	
		if (ImGui::ArrowButton("Front", ImGuiDir_Left)) {
			_gameObject->setPosition(_gameObject->getPosition().x, _gameObject->getPosition().y, _gameObject->getPosition().z + delta);
		}
		ImGui::SameLine();
		if (ImGui::ArrowButton("End", ImGuiDir_Right)) {
			_gameObject->setPosition(_gameObject->getPosition().x, _gameObject->getPosition().y, _gameObject->getPosition().z - delta);
		}
		ImGui::Columns(1);
		ImGui::Separator();
		if (ImGui::CollapsingHeader("Components")) {
			for (int j = 0; j < cList.size(); j++) {
				c = cList.at(j);
				ImGui::Bullet();
				switch (searchType(c)) {
					case UNDEF	: if (ImGui::Selectable("Unknown", &bl[j])) WindowManager::getWindowManager()->instanciate(WINCOM, c);
								  if (!bl[j]) WindowManager::getWindowManager()->free(c);
								  break;
					case CUBM	: if (ImGui::Selectable("CubeModel", &bl[j])) WindowManager::getWindowManager()->instanciate(WINCOM, c);
								  if (!bl[j]) WindowManager::getWindowManager()->free(c);
								  break;
					case CAM	: if (ImGui::Selectable("Camera", &bl[j])) WindowManager::getWindowManager()->instanciate(WINCOM, c);
								  if (!bl[j]) WindowManager::getWindowManager()->free(c);
								  break;
					case DIRL	: if (ImGui::Selectable("DirectionnalLight", &bl[j])) WindowManager::getWindowManager()->instanciate(WINCOM, c);
								  if (!bl[j]) WindowManager::getWindowManager()->free(c);
								  break;
					case PNTL	: if (ImGui::Selectable("PointLight", &bl[j])) WindowManager::getWindowManager()->instanciate(WINCOM, c);
								  if (!bl[j]) WindowManager::getWindowManager()->free(c);
								  break;
					case SCR	: if (ImGui::Selectable("Script", &bl[j])) WindowManager::getWindowManager()->instanciate(WINCOM, c);
								  if (!bl[j]) WindowManager::getWindowManager()->free(c);
								  break;
				}
			}
		}
	ImGui::End();
}

void* WindowGameObject::getObject() {
	return _gameObject;
}

int WindowGameObject::searchType(Component* c) {
	int type = UNDEF;
	CubeModel* cubeModel = dynamic_cast<CubeModel*>(c);
	if (cubeModel) type = CUBM;
	Camera* camera = dynamic_cast<Camera*>(c);
	if (camera) type = CAM;
	DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(c);
	if (dirLight) type = DIRL;
	PointLight* pointLight = dynamic_cast<PointLight*>(c);
	if (pointLight) type = PNTL;
	Script* script = dynamic_cast<Script*>(c);
	if (script) type = SCR;

	return type;

}
