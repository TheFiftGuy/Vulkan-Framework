#include "Camera.h"

Camera::Camera()   {
    projection = MMath::perspective(45.0f, 1.77777f, 0.1f, 20.0f);
	view = MMath::lookAt(Vec3(0.0f, 0.0f, -5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
}

Camera::~Camera()   {
	
}

Matrix4 Camera::GetProjectionMatrix() const {
    return projection;
}

Matrix4 Camera::GetViewMatrix() const   {
    return view;
}
