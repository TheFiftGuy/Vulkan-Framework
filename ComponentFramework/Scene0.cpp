#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene0.h"
#include "MMath.h"
#include "Debug.h"

Scene0::Scene0(Renderer *renderer_): 
	Scene(nullptr),renderer(renderer_){
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0() {}

bool Scene0::OnCreate() {
	
	switch (renderer->getRendererType()){
	case RendererType::VULKAN:
		break;

	case RendererType::OPENGL:
		break;
	}

	return true;
}

void Scene0::HandleEvents(const SDL_Event &sdlEvent) {

}

void Scene0::Update(const float deltaTime) {
	
}

void Scene0::Render() const {
	switch (renderer->getRendererType()) {
	case RendererType::VULKAN:
		renderer->Render();
		break;

	case RendererType::OPENGL:
		/// Clear the screen
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		/// Draw your scene here
		
		
		glUseProgram(0);
		
		break;
	}
}


void Scene0::OnDestroy() {
	
}
