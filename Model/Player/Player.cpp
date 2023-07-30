#include "Player.hpp"
#include <iostream>

using namespace entity;

Player::Player()
{
	bKey_W = false;
	bKey_S = false;
	bKey_A = false;
	bKey_D = false;
	bKey_Q = false;
	bKey_E = false;
	bKey_F = false;

	this->pTank = new Tank();
	CreateLight();

	this->pTankCamera = new PerspectiveCamera();
	this->pTankCamera->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 5.0f, -10.0f));
	this->pTankCamera->SetFOV(90.0f);
}

void entity::Player::CreateLight()
{
	this->pTankLight = new PointLight();
	this->pTankLight->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 0.0f, 15.0f));

	LightData startLightData;
	startLightData.light_position = glm::vec3(0.0f, 0.0f, 0.0f);
	startLightData.light_color = glm::vec3(1.0f, 1.0f, 1.0f);
	startLightData.ambient_color = glm::vec3(1.0f, 1.0f, 1.0f);
	startLightData.ambient_str = 0.2f;
	startLightData.spec_str = 0.5f;
	startLightData.spec_phong = 16.0f;
	startLightData.intensity = 100.0f;

	this->pTankLight->SetLightData(startLightData);
}

void Player::ProcessInput(GLFWwindow* window)
{
	this->bKey_W = glfwGetKey(window, GLFW_KEY_W);
	this->bKey_S = glfwGetKey(window, GLFW_KEY_S);
	this->bKey_A = glfwGetKey(window, GLFW_KEY_A);
	this->bKey_D = glfwGetKey(window, GLFW_KEY_D);
	this->bKey_Q = glfwGetKey(window, GLFW_KEY_Q);
	this->bKey_E = glfwGetKey(window, GLFW_KEY_E);
	this->bKey_F = glfwGetKey(window, GLFW_KEY_F);
}

void Player::Update(float tDeltaTime)
{
	/* Same Transforms, Different Local Transfroms : 0 = Mesh, 1 = Camera, 2 = Light */
	std::vector<Transform*> playerTransforms;

	playerTransforms.push_back(this->pTank->GetTransform());
	playerTransforms.push_back(this->pTankCamera->GetTransform());
	playerTransforms.push_back(this->pTankLight->GetTransform());

	if (this->bKey_W)
	{
		glm::vec3 movement = playerTransforms[0]->GetForwardVector() * fMoveSpeed * tDeltaTime;
		
		for (Transform* object : playerTransforms)
		{
			object->Move(movement);
		}

		pTankCamera->MoveCenter(movement);

	}

	if (this->bKey_S)
	{
		glm::vec3 movement = playerTransforms[0]->GetForwardVector() * -fMoveSpeed * tDeltaTime;

		for (Transform* object : playerTransforms)
		{
			object->Move(movement);
		}

		pTankCamera->MoveCenter(movement);
	}

	if (this->bKey_A)
	{
		for (Transform* object : playerTransforms)
		{
			object->Rotate(RotationAxis::YAW, -fRotationSpeed * tDeltaTime);
		}
	}

	if (this->bKey_D)
	{
		for (Transform* object : playerTransforms)
		{
			object->Rotate(RotationAxis::YAW, fRotationSpeed * tDeltaTime);
		}
	}
}

void Player::Draw()
{
	LightData pointLightData = this->pTankLight->GetLightData();
	CameraData perspectiveCameraData = this->pTankCamera->GetCameraData();

	LightData directionalLightData;

	directionalLightData.light_direction = glm::vec3(0.0f, 3.0f, -10.0f);
	directionalLightData.light_color = glm::vec3(1.0f, 1.0f, 1.0f);
	directionalLightData.ambient_color = glm::vec3(1.0f, 1.0f, 1.0f);
	directionalLightData.ambient_str = 0.2f;
	directionalLightData.spec_str = 0.5f;
	directionalLightData.spec_phong = 16.0f;
	directionalLightData.intensity = 10.0f;

	pTank->Draw(perspectiveCameraData, pointLightData, directionalLightData);
}

CameraData Player::GetCameraData()
{
	return this->pTankCamera->GetCameraData();
}

LightData Player::GetPointLightData()
{
	return this->pTankLight->GetLightData();
}