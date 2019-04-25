#include "Window.h"
#include "Component.h"
#include "CubeModel.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Script.h"
#include <glm/glm.hpp>
#include <sstream>

WindowComponent::WindowComponent(Component* c) : Window(), _component(c), _type(0) { }
WindowComponent::~WindowComponent() { }

void WindowComponent::Start() {
	_type = UNDEF;
	CubeModel* cubeModel = dynamic_cast<CubeModel*>(_component);
	if (cubeModel) _type = CUBM;
	Camera* camera = dynamic_cast<Camera*>(_component);
	if (camera) _type = CAM;
	DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(_component);
	if (dirLight) _type = DIRL;
	PointLight* pointLight = dynamic_cast<PointLight*>(_component);
	if (pointLight) _type = PNTL;
	Script* script = dynamic_cast<Script*>(_component);
	if (script) _type = SCR;
}

void WindowComponent::OnNewFrame() {
	switch (_type) {
		case UNDEF	: unknown();
					  break;
		case CUBM	: cubeModel();
					  break;
		case CAM	: camera();
					  break;
		case DIRL	: dirLight();
					  break;
		case PNTL	: pntLight();
					  break;
		case SCR	: script();
					  break;
	}
}

void* WindowComponent::getObject() {
	return _component;
}

void WindowComponent::unknown() {
	const void * address = static_cast<const void*>(_component);
	std::stringstream ss;
	ss << address;
	std::string name = ss.str();
	ImGui::Begin(("Unknown##"+name).c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::Text("No informations");	
	ImGui::End();
}

void WindowComponent::cubeModel() {
	const void * address = static_cast<const void*>(_component);
	std::stringstream ss;
	ss << address;
	std::string name = ss.str();
	ImGui::Begin(("CubeModel##"+name).c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::End();
}

void WindowComponent::camera() {
	const void * address = static_cast<const void*>(_component);
	std::stringstream ss;
	ss << address;
	std::string name = ss.str();
	ImGui::Begin(("Camera##"+name).c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::End();
}

void WindowComponent::dirLight() {
	float delta = 0.1f;
	const void * address = static_cast<const void*>(_component);
	std::stringstream ss;
	ss << address;
	std::string name = ss.str();
	DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(_component);
	ImGui::Begin(("DirectionalLight##"+name).c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::Text("Ambiant: R:%f G:%f B:%f",dirLight->getAmbient().r, dirLight->getAmbient().g, dirLight->getAmbient().b);
	ImGui::Columns(3, "mycolumns");
	ImGui::Separator();
	ImGui::Text("Red"); ImGui::NextColumn();
	ImGui::Text("Green"); ImGui::NextColumn();
	ImGui::Text("Blue"); ImGui::NextColumn();
	ImGui::Separator();
	if (ImGui::ArrowButton("-RA", ImGuiDir_Left)) { dirLight->setAmbient(dirLight->getAmbient().r - delta,  dirLight->getAmbient().g,  dirLight->getAmbient().b); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+RA", ImGuiDir_Right)) { dirLight->setAmbient(dirLight->getAmbient().r + delta,  dirLight->getAmbient().g,  dirLight->getAmbient().b); }
	ImGui::NextColumn();
	if (ImGui::ArrowButton("-GA", ImGuiDir_Left)) { dirLight->setAmbient(dirLight->getAmbient().r,  dirLight->getAmbient().g - delta,  dirLight->getAmbient().b); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+GA", ImGuiDir_Right)) { dirLight->setAmbient(dirLight->getAmbient().r,  dirLight->getAmbient().g + delta,  dirLight->getAmbient().b); }
	ImGui::NextColumn();
	if (ImGui::ArrowButton("-BA", ImGuiDir_Left)) { dirLight->setAmbient(dirLight->getAmbient().r,  dirLight->getAmbient().g,  dirLight->getAmbient().b - delta); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+BA", ImGuiDir_Right)) { dirLight->setAmbient(dirLight->getAmbient().r,  dirLight->getAmbient().g,  dirLight->getAmbient().b + delta); }
	ImGui::Columns(1);
	ImGui::Separator();	
	ImGui::Text("Diffuse: R:%f G:%f B:%f",dirLight->getDiffuse().r, dirLight->getDiffuse().g, dirLight->getDiffuse().b);
	ImGui::Columns(3, "mycolumns2");
	ImGui::Separator();
	ImGui::Text("Red"); ImGui::NextColumn();
	ImGui::Text("Green"); ImGui::NextColumn();
	ImGui::Text("Blue"); ImGui::NextColumn();
	ImGui::Separator();
	if (ImGui::ArrowButton("-RD", ImGuiDir_Left)) { dirLight->setDiffuse(dirLight->getDiffuse().r - delta,  dirLight->getDiffuse().g,  dirLight->getDiffuse().b); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+RD", ImGuiDir_Right)) { dirLight->setDiffuse(dirLight->getDiffuse().r + delta,  dirLight->getDiffuse().g,  dirLight->getDiffuse().b); }
	ImGui::NextColumn();
	if (ImGui::ArrowButton("-GD", ImGuiDir_Left)) { dirLight->setDiffuse(dirLight->getDiffuse().r,  dirLight->getDiffuse().g - delta,  dirLight->getDiffuse().b); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+GD", ImGuiDir_Right)) { dirLight->setDiffuse(dirLight->getDiffuse().r,  dirLight->getDiffuse().g + delta,  dirLight->getDiffuse().b); }
	ImGui::NextColumn();
	if (ImGui::ArrowButton("-BD", ImGuiDir_Left)) { dirLight->setDiffuse(dirLight->getDiffuse().r,  dirLight->getDiffuse().g,  dirLight->getDiffuse().b - delta); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+BD", ImGuiDir_Right)) { dirLight->setDiffuse(dirLight->getDiffuse().r,  dirLight->getDiffuse().g,  dirLight->getDiffuse().b + delta); }
	ImGui::Columns(1);
	ImGui::Separator();	
	ImGui::Text("Specular: R:%f G:%f B:%f",dirLight->getSpecular().r, dirLight->getSpecular().g, dirLight->getSpecular().b);
	ImGui::Columns(3, "mycolumns3");
	ImGui::Separator();
	ImGui::Text("Red"); ImGui::NextColumn();
	ImGui::Text("Green"); ImGui::NextColumn();
	ImGui::Text("Blue"); ImGui::NextColumn();
	ImGui::Separator();
	if (ImGui::ArrowButton("-RS", ImGuiDir_Left)) { dirLight->setSpecular(dirLight->getSpecular().r - delta,  dirLight->getSpecular().g,  dirLight->getSpecular().b); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+RS", ImGuiDir_Right)) { dirLight->setSpecular(dirLight->getSpecular().r + delta,  dirLight->getSpecular().g,  dirLight->getSpecular().b); }
	ImGui::NextColumn();
	if (ImGui::ArrowButton("-GS", ImGuiDir_Left)) { dirLight->setSpecular(dirLight->getSpecular().r,  dirLight->getSpecular().g - delta,  dirLight->getSpecular().b); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+GS", ImGuiDir_Right)) { dirLight->setSpecular(dirLight->getSpecular().r,  dirLight->getSpecular().g + delta,  dirLight->getSpecular().b); }
	ImGui::NextColumn();
	if (ImGui::ArrowButton("-BS", ImGuiDir_Left)) { dirLight->setSpecular(dirLight->getSpecular().r,  dirLight->getSpecular().g,  dirLight->getSpecular().b - delta); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+BS", ImGuiDir_Right)) { dirLight->setSpecular(dirLight->getSpecular().r,  dirLight->getSpecular().g,  dirLight->getSpecular().b + delta); }
	ImGui::Columns(1);
	ImGui::Separator();	
	ImGui::End();
}

void WindowComponent::pntLight() {
	float delta = 0.1f;
	const void * address = static_cast<const void*>(_component);
	std::stringstream ss;
	ss << address;
	std::string name = ss.str();
	PointLight* pointLight = dynamic_cast<PointLight*>(_component);
	ImGui::Begin(("PointLight##"+name).c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::Text("Ambiant: R:%f G:%f B:%f",pointLight->getAmbient().r, pointLight->getAmbient().g, pointLight->getAmbient().b);
	ImGui::Columns(3, "mycolumns");
	ImGui::Separator();
	ImGui::Text("Red"); ImGui::NextColumn();
	ImGui::Text("Green"); ImGui::NextColumn();
	ImGui::Text("Blue"); ImGui::NextColumn();
	ImGui::Separator();
	if (ImGui::ArrowButton("-RA", ImGuiDir_Left)) { pointLight->setAmbient(pointLight->getAmbient().r - delta,  pointLight->getAmbient().g,  pointLight->getAmbient().b); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+RA", ImGuiDir_Right)) { pointLight->setAmbient(pointLight->getAmbient().r + delta,  pointLight->getAmbient().g,  pointLight->getAmbient().b); }
	ImGui::NextColumn();
	if (ImGui::ArrowButton("-GA", ImGuiDir_Left)) { pointLight->setAmbient(pointLight->getAmbient().r,  pointLight->getAmbient().g - delta,  pointLight->getAmbient().b); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+GA", ImGuiDir_Right)) { pointLight->setAmbient(pointLight->getAmbient().r,  pointLight->getAmbient().g + delta,  pointLight->getAmbient().b); }
	ImGui::NextColumn();
	if (ImGui::ArrowButton("-BA", ImGuiDir_Left)) { pointLight->setAmbient(pointLight->getAmbient().r,  pointLight->getAmbient().g,  pointLight->getAmbient().b - delta); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+BA", ImGuiDir_Right)) { pointLight->setAmbient(pointLight->getAmbient().r,  pointLight->getAmbient().g,  pointLight->getAmbient().b + delta); }
	ImGui::Columns(1);
	ImGui::Separator();	
	ImGui::Text("Diffuse: R:%f G:%f B:%f",pointLight->getDiffuse().r, pointLight->getDiffuse().g, pointLight->getDiffuse().b);
	ImGui::Columns(3, "mycolumns2");
	ImGui::Separator();
	ImGui::Text("Red"); ImGui::NextColumn();
	ImGui::Text("Green"); ImGui::NextColumn();
	ImGui::Text("Blue"); ImGui::NextColumn();
	ImGui::Separator();
	if (ImGui::ArrowButton("-RD", ImGuiDir_Left)) { pointLight->setDiffuse(pointLight->getDiffuse().r - delta,  pointLight->getDiffuse().g,  pointLight->getDiffuse().b); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+RD", ImGuiDir_Right)) { pointLight->setDiffuse(pointLight->getDiffuse().r + delta,  pointLight->getDiffuse().g,  pointLight->getDiffuse().b); }
	ImGui::NextColumn();
	if (ImGui::ArrowButton("-GD", ImGuiDir_Left)) { pointLight->setDiffuse(pointLight->getDiffuse().r,  pointLight->getDiffuse().g - delta,  pointLight->getDiffuse().b); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+GD", ImGuiDir_Right)) { pointLight->setDiffuse(pointLight->getDiffuse().r,  pointLight->getDiffuse().g + delta,  pointLight->getDiffuse().b); }
	ImGui::NextColumn();
	if (ImGui::ArrowButton("-BD", ImGuiDir_Left)) { pointLight->setDiffuse(pointLight->getDiffuse().r,  pointLight->getDiffuse().g,  pointLight->getDiffuse().b - delta); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+BD", ImGuiDir_Right)) { pointLight->setDiffuse(pointLight->getDiffuse().r,  pointLight->getDiffuse().g,  pointLight->getDiffuse().b + delta); }
	ImGui::Columns(1);
	ImGui::Separator();	
	ImGui::Text("Specular: R:%f G:%f B:%f",pointLight->getSpecular().r, pointLight->getSpecular().g, pointLight->getSpecular().b);
	ImGui::Columns(3, "mycolumns3");
	ImGui::Separator();
	ImGui::Text("Red"); ImGui::NextColumn();
	ImGui::Text("Green"); ImGui::NextColumn();
	ImGui::Text("Blue"); ImGui::NextColumn();
	ImGui::Separator();
	if (ImGui::ArrowButton("-RS", ImGuiDir_Left)) { pointLight->setSpecular(pointLight->getSpecular().r - delta,  pointLight->getSpecular().g,  pointLight->getSpecular().b); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+RS", ImGuiDir_Right)) { pointLight->setSpecular(pointLight->getSpecular().r + delta,  pointLight->getSpecular().g,  pointLight->getSpecular().b); }
	ImGui::NextColumn();
	if (ImGui::ArrowButton("-GS", ImGuiDir_Left)) { pointLight->setSpecular(pointLight->getSpecular().r,  pointLight->getSpecular().g - delta,  pointLight->getSpecular().b); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+GS", ImGuiDir_Right)) { pointLight->setSpecular(pointLight->getSpecular().r,  pointLight->getSpecular().g + delta,  pointLight->getSpecular().b); }
	ImGui::NextColumn();
	if (ImGui::ArrowButton("-BS", ImGuiDir_Left)) { pointLight->setSpecular(pointLight->getSpecular().r,  pointLight->getSpecular().g,  pointLight->getSpecular().b - delta); }
	ImGui::SameLine();
	if (ImGui::ArrowButton("+BS", ImGuiDir_Right)) { pointLight->setSpecular(pointLight->getSpecular().r,  pointLight->getSpecular().g,  pointLight->getSpecular().b + delta); }
	ImGui::Columns(1);
	ImGui::Separator();	
	ImGui::End();
}

void WindowComponent::script() {
	const void * address = static_cast<const void*>(_component);
	std::stringstream ss;
	ss << address;
	std::string name = ss.str();
	Script* script = dynamic_cast<Script*>(_component);
	ImGui::Begin(("Script##"+name).c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::Text("Script:\n\t%s", script->getScriptName().c_str());
	ImGui::End();
}

int WindowComponent::getType() {
	return _type;
}
