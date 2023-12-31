#pragma once
#include "OrthographicCamera.hpp"

using namespace camera;

OrthographicCamera::OrthographicCamera()
{
	this->size = 2.0f;
}

glm::mat4 OrthographicCamera::GetProjectionMatrix()
{
	return glm::ortho(-size, size, -size, size, this->nearPlane, this->farPlane);
}

void OrthographicCamera::SetSize(float size)
{
	this->size = size;
}

void OrthographicCamera::IncSize(float inc)
{
	SetSize(this->size + inc);
}

CameraData OrthographicCamera::GetCameraData()
{
	CameraData data;

	data.camera_pos = this->transform->GetPosition();
	data.view_matrix = glm::lookAt(this->pos, this->cameraCenter, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
	data.projection_matrix = this->GetProjectionMatrix();

	return data;
}