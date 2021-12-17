#ifndef SCENE0_H
#define SCENE0_H
#include <vector>

#include "Matrix.h"
#include "Scene.h"
#include "Vector.h"
#include "Renderer.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;

class Scene0 : public Scene {
private:
	Renderer *renderer;
	class Camera* camera; //forward decleration included here
	Matrix4 marioModelMatrix;
	Matrix4 sphereModelMatrix;
	Vec4 lightPos[MAX_NUM_OF_LIGHTS];
	Vec4 specColor[MAX_NUM_OF_LIGHTS];
	Vec4 diffColor[MAX_NUM_OF_LIGHTS];
	
public:
	explicit Scene0(Renderer* renderer_);
	virtual ~Scene0();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE0_H