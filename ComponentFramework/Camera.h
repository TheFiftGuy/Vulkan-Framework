#ifndef CAMERA_H
#define CAMERA_H

#include "MMath.h"

using namespace MATH;

class Camera	{
private:

	Matrix4 projection;
	Matrix4 view;
	Matrix4 rotate, translate;
	

public:
	Camera();
	~Camera();

	Matrix4 GetProjectionMatrix() const;
	Matrix4 GetViewMatrix() const;

	
};

#endif