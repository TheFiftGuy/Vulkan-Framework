#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene0.h"
#include "MMath.h"
#include "Debug.h"

#include "VulkanRenderer.h"

Scene0::Scene0(Renderer* renderer_) : Scene(nullptr), renderer(renderer_)	{
	camera = new Camera();
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
		// {} makes all of these variables local to here, which is what we want anyway. if missing the switch statement wont compile
		//Another solution is to initialize these before the switch, but we only need them for vulkan so that would be a waste
		{
			VulkanRenderer* vRenderer = dynamic_cast<VulkanRenderer*>(renderer);
			/// This is quick timer.  
			static auto startTime = std::chrono::high_resolution_clock::now();
			auto currentTime = std::chrono::high_resolution_clock::now();
			float elapsedTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

			Matrix4 oriention = MMath::rotate(180.0f, Vec3(0.0f, 1.0f, 0.0f));
			Matrix4 marioModelMatrix = MMath::rotate(elapsedTime * 90.0f, Vec3(0.0f, 1.0f, 0.0f)) * oriention;
		
			vRenderer->LoadUBO(marioModelMatrix, camera->GetViewMatrix(), camera->GetProjectionMatrix()); //ubo.model gets changed in VulkanRenderer::updateUniformBuffer
			vRenderer->Render();
		}
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
		default:
			throw std::runtime_error("renderer not supported");
	}
}


void Scene0::OnDestroy() {
	
}
