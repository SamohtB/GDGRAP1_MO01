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

	bLampToggle = false;
	bCameraToggle = false;

	this->ECurrentLightIntensity = LampIntensity::LOW;
	this->ECurrentActiveCamera = ActiveCamera::FIRSTPERSON;

	/* Starting Values For Point Light */
	LightData startLightData;
	startLightData.light_position = glm::vec3(0.0f, 0.0f, 0.0f);
	startLightData.light_color = glm::vec3(1.0f, 1.0f, 1.0f);
	startLightData.ambient_color = glm::vec3(1.0f, 1.0f, 1.0f);
	startLightData.ambient_str = 0.2f;
	startLightData.spec_str = 0.5f;
	startLightData.spec_phong = 16.0f;
	startLightData.intensity = LOW_INTENSITY;

	this->pTank = new Tank();

	this->pTankLight = new PointLight();
	this->pTankLight->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 0.0f, 10.0f));
	this->pTankLight->SetLightData(startLightData);

	CreateThirdPersonCam();
	CreateFirstPersonCam();
}



const glm::highp_vec3& entity::Player::PointForward()
{
	return this->pTank->GetTransform()->GetPosition() + this->pTank->GetTransform()->GetForwardVector();
}

void entity::Player::CreateFirstPersonCam()
{
	this->pFirstPersonCam = new PerspectiveCamera();
	this->pFirstPersonCam->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 5.0f, 15.0f));
	this->pFirstPersonCam->SetCenter(PointForward());
	this->pFirstPersonCam->SetFOV(60.0f);
}

void entity::Player::CreateThirdPersonCam()
{
	this->pThirdPersonCam = new PerspectiveCamera();
	this->pThirdPersonCam->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 5.0f, -10.0f));
	this->pThirdPersonCam->SetCenter(this->pTank->GetTransform()->GetPosition());
	this->pThirdPersonCam->SetFOV(60.0f);
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
	/* Same Transforms, Different Local Transfroms : 0 = Mesh, 1 = FPCamera, 2 = TPCamera, 3 = Light */
	std::vector<Transform*> playerTransforms;

	playerTransforms.push_back(this->pTank->GetTransform());
	playerTransforms.push_back(this->pFirstPersonCam->GetTransform());
	playerTransforms.push_back(this->pThirdPersonCam->GetTransform());
	playerTransforms.push_back(this->pTankLight->GetTransform());
	

	if (this->bKey_W)
	{
		glm::vec3 movement = playerTransforms[0]->GetForwardVector() * fMoveSpeed * tDeltaTime;
		
		for (Transform* object : playerTransforms)
		{
			object->Move(movement);
		}

		pFirstPersonCam->SetCenter(PointForward());
		pThirdPersonCam->MoveCenter(movement);
	}

	if (this->bKey_S)
	{
		glm::vec3 movement = playerTransforms[0]->GetForwardVector() * -fMoveSpeed * tDeltaTime;

		for (Transform* object : playerTransforms)
		{
			object->Move(movement);
		}

		pFirstPersonCam->SetCenter(PointForward());
		pThirdPersonCam->MoveCenter(movement);
	}

	if (this->bKey_A)
	{
		/* Rotate Mesh Directly */
		playerTransforms[0]->Rotate(RotationAxis::YAW, fRotationSpeed * tDeltaTime);

		/*
		 *	Calculate Camera And Light Position Using The Tank's Forward Vector *
		 *	FORMULA:
		 *		NEW_POS = (ForwardVector * Radius * Direction) + Offset
		 *		Radius = Distance Away From Tank
		 *		Direction = if Forward (1), if Backward(-1)
		 *      Offset = Y Offset for TPCamera, because camera is above the object
		 */

		playerTransforms[1]->SetLocalPosition((playerTransforms[0]->GetForwardVector() * 15.0f));
		playerTransforms[2]->SetLocalPosition((playerTransforms[0]->GetForwardVector() * -10.0f) + glm::vec3(0.0f, 5.0f, 0.0f));
		playerTransforms[3]->SetLocalPosition((playerTransforms[0]->GetForwardVector() * 10.0f));

		/* Set Camera Centers: FPCam always point forward, TPCam always point at tank */
		pFirstPersonCam->SetCenter(PointForward());
		pThirdPersonCam->SetCenter(playerTransforms[0]->GetPosition());
	}

	if (this->bKey_D)
	{
		float rotationAmount = -fRotationSpeed * tDeltaTime;

		playerTransforms[0]->Rotate(RotationAxis::YAW, rotationAmount);

		playerTransforms[1]->SetLocalPosition((playerTransforms[0]->GetForwardVector() * 15.0f));
		playerTransforms[2]->SetLocalPosition((playerTransforms[0]->GetForwardVector() * -10.0f) + glm::vec3(0.0f, 5.0f, 0.0f));
		playerTransforms[3]->SetLocalPosition((playerTransforms[0]->GetForwardVector() * 10.0f));

		pFirstPersonCam->SetCenter(PointForward());
		pThirdPersonCam->SetCenter(playerTransforms[0]->GetPosition());
	}

	if (this->bKey_F && !this->bLampToggle)
	{
		this->bLampToggle = true;
		switch (ECurrentLightIntensity)
		{
			case LampIntensity::LOW:
				this->ECurrentLightIntensity = LampIntensity::MID;
				this->pTankLight->SetIntensity(MID_INTENSITY);
				break;

			case LampIntensity::MID:
				this->ECurrentLightIntensity = LampIntensity::HIGH;
				this->pTankLight->SetIntensity(HIGH_INTENSITY);
				break;

			case LampIntensity::HIGH:
				this->ECurrentLightIntensity = LampIntensity::LOW;
				this->pTankLight->SetIntensity(LOW_INTENSITY);
				break;
			default:
				break;
		}
	}
	else if (!this->bKey_F)
	{
		this->bLampToggle = false;
	}
}

void Player::Draw()
{
	LightData pointLightData = this->pTankLight->GetLightData();
	CameraData perspectiveCameraData = this->pThirdPersonCam->GetCameraData();

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
	return this->pThirdPersonCam->GetCameraData();
}

LightData Player::GetPointLightData()
{
	return this->pTankLight->GetLightData();
}