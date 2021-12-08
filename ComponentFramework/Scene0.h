#ifndef SCENE0_H
#define SCENE0_H
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