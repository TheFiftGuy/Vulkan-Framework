#include "Camera.h"

Camera::Camera()   {
    projection.loadIdentity();
    view.loadIdentity();
	
}

Camera::~Camera()   {
	
}

Matrix4 Camera::GetProjectionMatrix() const {
    return projection;
}

Matrix4 Camera::GetViewMatrix() const   {
    return view;
}

void Camera::SetProjectionMatrix(const Matrix4 projection_)  {
    projection = projection_;
}

void Camera::SetViewMatrix(const Matrix4 view_)   {
    view = view_;
}
