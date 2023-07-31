#pragma once
#include "Camera.hpp"

using namespace camera;

Camera::Camera()
{
	this->cameraCenter = glm::vec3(0.0f, 0.0f, 0.0f);

	this->nearPlane = 0.1f;
	this->farPlane = 100.0f;

	this->transform = new Transform();
}

void Camera::SetCamera(glm::vec3 position)
{
	this->transform->SetPosition(position);
}

void Camera::MoveCamera(glm::vec3 position)
{
	this->SetCamera(this->transform->GetPosition() + position);
}

void Camera::SetCenter(glm::vec3 center)
{
	this->cameraCenter = center;
}

void Camera::MoveCenter(glm::vec3 center)
{
	this->SetCenter(this->cameraCenter + center);
}

void Camera::SetPositionAndCenter(glm::vec3 pos, glm::vec3 center)
{
	this->SetCamera(pos);
	this->SetCenter(center);
}
void Camera::MovePositionAndCenter(glm::vec3 pos, glm::vec3 center)
{
	this->MoveCamera(pos);
	this->MoveCenter(center);
}

void Camera::SetNearPlane(float near)
{
	nearPlane = near;
}

void Camera::SetFarPlane(float far)
{
	farPlane = far;
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::mat4 cameraPosMatrix = glm::translate(glm::mat4(1.0f), this->GetTransform()->GetPosition() * -1.0f);
	glm::vec3 F = (cameraCenter - this->GetTransform()->GetPosition());
	F = glm::normalize(F);
	glm::vec3 R = glm::cross(F, WORLD_UP);
	glm::vec3 U = glm::cross(R, F);

	glm::mat4 cameraOrientation = glm::mat4(1.0f);

	//Matrix[C][R]
	//R
	cameraOrientation[0][0] = R.x;
	cameraOrientation[1][0] = R.y;
	cameraOrientation[2][0] = R.z;
	//U
	cameraOrientation[0][1] = U.x;
	cameraOrientation[1][1] = U.y;
	cameraOrientation[2][1] = U.z;
	//-F
	cameraOrientation[0][2] = -F.x;
	cameraOrientation[1][2] = -F.y;
	cameraOrientation[2][2] = -F.z;

	glm::mat4 view_matrix = cameraOrientation * cameraPosMatrix;
	//glm::mat4 view_matrix = glm::lookAt(this->transform->GetPosition(), this->cameraCenter, WORLD_UP);
	return view_matrix;
}

Transform* Camera::GetTransform()
{
	return this->transform;
}