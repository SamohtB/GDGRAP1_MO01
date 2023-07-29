#pragma once
#include "PerspectiveCamera.hpp"

using namespace camera;

PerspectiveCamera::PerspectiveCamera()
{
	this->FOV = 60.0f;
}

glm::mat4 PerspectiveCamera::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(this->FOV), ASPECT_RATIO, this->nearPlane, this->farPlane);
}

void PerspectiveCamera::SetFOV(float FOV)
{
	this->FOV = FOV;
}

void PerspectiveCamera::IncFOV(float inc)
{
	SetFOV(this->FOV + inc);
}

CameraData PerspectiveCamera::GetCameraData()
{
	CameraData data;

	data.camera_pos = this->transform->GetPosition();
	data.view_matrix = this->GetViewMatrix();
	data.projection_matrix = this->GetProjectionMatrix();

	return data;
}