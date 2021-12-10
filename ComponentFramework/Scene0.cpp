#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene0.h"
#include "MMath.h"
#include "Debug.h"

#include "VulkanRenderer.h"
#include "Camera.h"

Scene0::Scene0(Renderer* renderer_) : Scene(nullptr), camera(nullptr), renderer(renderer_)	{
	camera = new Camera();
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0()	{
	if(camera !=nullptr)	{
		delete camera;
		camera = nullptr;
	}
}

bool Scene0::OnCreate() {
	
	switch (renderer->getRendererType()){
	case RendererType::VULKAN:	{
		int width, heigth;
		SDL_GetWindowSize(dynamic_cast<VulkanRenderer*>(renderer)->GetWindow(), &width, &heigth);
		float aspectRatio = static_cast<float>(width) / static_cast<float>(heigth);
		Matrix4 proj = MMath::perspective(45.0f, aspectRatio, 0.1f, 20.0f);
		camera->SetProjectionMatrix(proj);
		camera->SetViewMatrix(MMath::lookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f)));
			
		lightPos[0] = Vec4(-15.0f, 0.0f, -5.0f, 1.0f);//left
		lightPos[1] = Vec4(15.0f, 0.0f, -5.0f, 1.0f);//right
		lightPos[2] = Vec4(0.0f, 15.0f, -5.0f, 1.0f);//up
		lightPos[3] = Vec4(0.0f, -15.0f, -5.0f, 1.0f);//down
		lightPos[4] = Vec4(0.0f, 0.0f, 10.0f, 1.0f);//front
		
		specColor[0] = Vec4(0.0f, 0.0f, 0.3f, 0.0f);//blue
		specColor[1] = Vec4(0.3f, 0.0f, 0.0f, 0.0f);//red
		specColor[2] = Vec4(0.0f, 0.3f, 0.0f, 0.0f);//green
		specColor[3] = Vec4(0.3f, 0.3f, 0.0f, 0.0f);//yellow
		specColor[4] = Vec4(0.3f, 0.0f, 0.3f, 0.0f);//purple
			
		diffColor[0] = Vec4(0.0f, 0.0f, 0.3f, 0.0f);//blue
		diffColor[1] = Vec4(0.3f, 0.0f, 0.0f, 0.0f);//red
		diffColor[2] = Vec4(0.0f, 0.3f, 0.0f, 0.0f);//green
		diffColor[3] = Vec4(0.3f, 0.3f, 0.0f, 0.0f);//yellow
		diffColor[4] = Vec4(0.3f, 0.3f, 0.0f, 0.0f);//yellow
		
		//using 4/5 lights	
		}
		break;

	case RendererType::OPENGL:
		break;
	}

	return true;
}

void Scene0::HandleEvents(const SDL_Event &sdlEvent) {
	if(sdlEvent.type == SDL_WINDOWEVENT)	{
		//std::cout << "Window Event" << std::endl;

		switch (sdlEvent.window.event)	{
		case SDL_WINDOWEVENT_SIZE_CHANGED: {
			std::cout << "Window changed size" << std::endl;
			float aspectRatio = static_cast<float>(sdlEvent.window.data1) / static_cast<float>(sdlEvent.window.data2);
			Matrix4 proj = MMath::perspective(45.0f, aspectRatio, 0.1f, 20.0f);
			camera->SetProjectionMatrix(proj);
			}
			break;
			
		}
		
	}

}

void Scene0::Update(const float deltaTime) {
	static float elapsedTime = 0.0f;
	elapsedTime += deltaTime;
	marioModelMatrix = MMath::rotate(elapsedTime * 180.0f, Vec3(0.0f, 1.0f, 0.0f));
}

void Scene0::Render() const {
	switch (renderer->getRendererType()) {
	case RendererType::VULKAN:
		//tell scott about this - ep8 he mentions he would want to look into it
		// {} makes all of these variables local to here, which is what we want anyway. if missing the switch statement wont compile
		//Another solution is to initialize these before the switch, but we only need them for vulkan so that would be a waste
		{
			VulkanRenderer* vRenderer = dynamic_cast<VulkanRenderer*>(renderer);					
			vRenderer->SetModelUBO(marioModelMatrix);
			vRenderer->SetLightUBO(lightPos, specColor, diffColor, 5);
			vRenderer->SetCameraUBO(camera->GetViewMatrix(), camera->GetProjectionMatrix());
			vRenderer->Render();
			//std::cout << "Scene0 Vulkan render end" << std::endl;
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
