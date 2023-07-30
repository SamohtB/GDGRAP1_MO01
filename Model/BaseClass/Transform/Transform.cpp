#pragma once
#include "Transform.hpp"

using namespace base_class;

Transform::Transform()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	local_position = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f);
	local_scale = glm::vec3(1.0f);

	pitch = 0.f;
	yaw = 0.f;
	roll = 0.f;
	local_pitch = 0.f;
	local_yaw = 0.f;
	local_roll = 0.f;
	
}

void Transform::Move(float x, float y, float z)
{
	glm::vec3 move_amt = this->position + glm::vec3(x, y, z);
	this->SetPosition(move_amt);
}

void Transform::Move(glm::vec3 vector)
{
	this->SetPosition(this->position + vector);
}

void Transform::SetPosition(float x, float y, float z)
{
	glm::vec3 new_pos = glm::vec3(x, y, z);
	this->SetPosition(new_pos);
}

void Transform::SetPosition(glm::vec3 vector)
{
	this->position = vector;
}

void Transform::SetLocalPosition(float x, float y, float z)
{
	glm::vec3 new_pos = glm::vec3(x, y, z);
	this->local_position = new_pos;
}

void Transform::SetLocalPosition(glm::vec3 vector)
{
	this->local_position = vector;
}

void Transform::Rotate(RotationAxis axis, float theta)
{
	switch (axis)
	{
		case RotationAxis::PITCH:
			this->SetRotation(axis, this->pitch + theta);
			break;
		case RotationAxis::YAW:
			this->SetRotation(axis, this->yaw + theta);
			break;
		case RotationAxis::ROLL:
			this->SetRotation(axis, this->roll + theta);
			break;
	}
}

void Transform::SetRotation(RotationAxis axis, float theta)
{
	switch (axis)
	{
	case RotationAxis::PITCH:
		this->pitch = theta;
		break;
	case RotationAxis::YAW:
		this->yaw = theta;
		break;
	case RotationAxis::ROLL:
		this->roll = theta;
		break;
	}
}

void Transform::SetLocalRotation(RotationAxis axis, float theta)
{
	switch (axis)
	{
	case RotationAxis::PITCH:
		this->local_pitch = theta;
		break;
	case RotationAxis::YAW:
		this->local_yaw = theta;
		break;
	case RotationAxis::ROLL:
		this->local_roll = theta;
		break;
	}
}

void Transform::Scale(glm::vec3 scalar)
{
	this->SetScale(this->scale + scalar);
}

void Transform::Scale(float x, float y, float z)
{
	glm::vec3 new_scalar = glm::vec3(x, y, z);
	this->SetScale(this->scale + new_scalar);
}

void Transform::Scale(float scalar)
{
	glm::vec3 new_scalar = glm::vec3(scalar, scalar, scalar);
	this->SetScale(this->scale + new_scalar);
}

void Transform::SetScale(float x, float y, float z)
{
	glm::vec3 new_scalar = glm::vec3(x, y, z);
	this->SetScale(new_scalar);
}

void Transform::SetScale(float scalar)
{
	glm::vec3 new_scalar = glm::vec3(scalar, scalar, scalar);
	this->SetScale(new_scalar);
}

void Transform::SetScale(glm::vec3 scalar)
{
	this->scale = scalar;
}

void Transform::SetLocalScale(float x, float y, float z)
{
	glm::vec3 new_scalar = glm::vec3(x, y, z);
	this->SetLocalScale(new_scalar);
}

void Transform::SetLocalScale(float scalar)
{
	glm::vec3 new_scalar = glm::vec3(scalar, scalar, scalar);
	this->SetLocalScale(new_scalar);
}

void Transform::SetLocalScale(glm::vec3 scalar)
{
	this->local_scale = scalar;
}

glm::vec3 Transform::GetPosition()
{
	return this->position + this->local_position;
}

glm::vec3 Transform::GetForwardVector()
{
	glm::vec3 forwardVector;
	forwardVector.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	forwardVector.y = sin(glm::radians(pitch));
	forwardVector.z = cos(glm::radians(pitch)) * cos(glm::radians(yaw));

	// Normalize the forward vector to make it a unit vector
	return glm::normalize(forwardVector);
}

glm::mat4 Transform::GetModelMatrix()
{
	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, position + local_position);
	model_matrix = glm::scale(model_matrix, scale * local_scale);
	model_matrix = glm::rotate(model_matrix, glm::radians(pitch + local_pitch), glm::vec3(1.f, 0.f, 0.f));
	model_matrix = glm::rotate(model_matrix, glm::radians(yaw + local_yaw), glm::vec3(0.f, 1.f, 0.f));
	model_matrix = glm::rotate(model_matrix, glm::radians(roll + local_roll), glm::vec3(0.f, 0.f, 1.f));

	return model_matrix;
}