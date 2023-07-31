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
	bKey_1 = false;
	bKey_2 = false;

	bLampToggle = false;
	bCameraToggle = false;
	bTopToggle = false;

	this->ECurrentLightIntensity = LampIntensity::LOW;
	this->ECurrentActiveCamera = ActiveCamera::THIRDPERSON;
	this->EPreviousActiveCamera = ActiveCamera::THIRDPERSON;

	this->pTank = new Tank();
	CreateTankLight();
	CreateThirdPersonCam();
	CreateFirstPersonCam();
	CreateBirdEyeCam();

}
void entity::Player::CreateTankLight()
{
	/* Starting Values For Point Light */
	LightData startLightData;
	startLightData.light_position = glm::vec3(0.0f, 0.0f, 0.0f);
	startLightData.light_color = glm::vec3(1.0f, 1.0f, 1.0f);
	startLightData.ambient_color = glm::vec3(1.0f, 1.0f, 1.0f);
	startLightData.ambient_str = 0.2f;
	startLightData.spec_str = 0.5f;
	startLightData.spec_phong = 16.0f;
	startLightData.intensity = LOW_INTENSITY;

	this->pTankLight = new PointLight();
	this->pTankLight->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 0.0f, 10.0f));
	this->pTankLight->SetLightData(startLightData);
}

void entity::Player::CreateFirstPersonCam()
{
	this->pFirstPersonCam = new PerspectiveCamera();
	this->pFirstPersonCam->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 5.0f, 0.0f));
	this->pFirstPersonCam->SetCenter(PointForward());
	this->pFirstPersonCam->SetFOV(30.0f);
}

void entity::Player::CreateThirdPersonCam()
{
	this->pThirdPersonCam = new PerspectiveCamera();
	this->pThirdPersonCam->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 5.0f, -10.0f));
	this->pThirdPersonCam->SetCenter(this->pTank->GetTransform()->GetPosition());
	this->pThirdPersonCam->SetFOV(60.0f);
}

void entity::Player::CreateBirdEyeCam()
{
	this->pBirdEyeCam = new OrthographicCamera();
	this->pBirdEyeCam->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 10.0f, -5.0f));
	this->pBirdEyeCam->SetCenter(this->pTank->GetTransform()->GetPosition());
	this->pBirdEyeCam->SetSize(15.0f);
	this->pBirdEyeCam->SetFarPlane(1000.0f);
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

	this->bKey_1 = glfwGetKey(window, GLFW_KEY_1);
	this->bKey_2 = glfwGetKey(window, GLFW_KEY_2);
}

void Player::Update(float tDeltaTime)
{
	LampToggle();
	BirdEyeToggle();
		
	switch (ECurrentActiveCamera)
	{
		case ActiveCamera::THIRDPERSON:
			ThirdPersonMovement(tDeltaTime);
			PerspectiveCameraToggle();
			break;

		case ActiveCamera::FIRSTPERSON:
			FirstPersonMovement(tDeltaTime);
			PerspectiveCameraToggle();
			break;

		case ActiveCamera::BIRDSEYE:
			BirdEyeMovement(tDeltaTime);
			break;
	}
}

void entity::Player::BirdEyeMovement(float tDeltaTime)
{
	float movement = fMoveSpeed * tDeltaTime;

	if (this->bKey_W)
	{
		this->pBirdEyeCam->MovePositionAndCenter(glm::vec3(0.0f, 0.0f, movement), glm::vec3(0.0f, 0.0f, movement));
	}

	if (this->bKey_S)
	{
		this->pBirdEyeCam->MovePositionAndCenter(glm::vec3(0.0f, 0.0f, -movement), glm::vec3(0.0f, 0.0f, -movement));
	}

	if (this->bKey_A)
	{
		this->pBirdEyeCam->MovePositionAndCenter(glm::vec3(-movement, 0.0f, 0.0f), glm::vec3(-movement, 0.0f, 0.0f));
	}

	if (this->bKey_D)
	{
		this->pBirdEyeCam->MovePositionAndCenter(glm::vec3(movement, 0.0f, 0.0f), glm::vec3(movement, 0.0f, 0.0f));
	}
}

void entity::Player::BirdEyeToggle()
{
	if (this->bKey_2 && !this->bTopToggle)
	{
		this->bTopToggle = true;
		switch (ECurrentActiveCamera)
		{
		case ActiveCamera::BIRDSEYE:
			this->ECurrentActiveCamera = this->EPreviousActiveCamera;
			break;

		default:
			ResetBirdView();
			this->ECurrentActiveCamera = ActiveCamera::BIRDSEYE;
			break;
		}
	}
	else if (!this->bKey_2)
	{
		this->bTopToggle = false;
	}
}

void entity::Player::ResetBirdView()
{
	Transform* transform = this->pTank->GetTransform();
	this->pBirdEyeCam->SetPositionAndCenter(transform->GetPosition(), transform->GetPosition());
}

void entity::Player::FirstPersonMovement(float tDeltaTime)
{
	Transform* cameraTransform = this->pFirstPersonCam->GetTransform();

	if (this->bKey_W)
	{
		cameraTransform->Rotate(RotationAxis::PITCH, fRotationSpeed * tDeltaTime);
		this->pFirstPersonCam->SetCenter(PointForward());
	}

	if (this->bKey_S)
	{
		cameraTransform->Rotate(RotationAxis::PITCH, -fRotationSpeed * tDeltaTime);
		this->pFirstPersonCam->SetCenter(PointForward());
	}

	if (this->bKey_A)
	{
		cameraTransform->Rotate(RotationAxis::YAW, fRotationSpeed * tDeltaTime);
		this->pFirstPersonCam->SetCenter(PointForward());
	}

	if (this->bKey_D)
	{
		cameraTransform->Rotate(RotationAxis::YAW, -fRotationSpeed * tDeltaTime);
		this->pFirstPersonCam->SetCenter(PointForward());
	}

	if (this->bKey_Q)
	{
		this->pFirstPersonCam->IncFOV(this->fZoomSpeed * -tDeltaTime);
	}

	if (this->bKey_E)
	{
		this->pFirstPersonCam->IncFOV(this->fZoomSpeed * tDeltaTime);
	}
}

void entity::Player::PerspectiveCameraToggle()
{
	if (this->bKey_1 && !this->bCameraToggle)
	{
		this->bCameraToggle = true;
		switch (ECurrentActiveCamera)
		{
			case ActiveCamera::FIRSTPERSON:
				this->ECurrentActiveCamera = ActiveCamera::THIRDPERSON;
				this->EPreviousActiveCamera = ActiveCamera::THIRDPERSON;
				break;

			case ActiveCamera::THIRDPERSON:
				this->ECurrentActiveCamera = ActiveCamera::FIRSTPERSON;
				this->EPreviousActiveCamera = ActiveCamera::FIRSTPERSON;
				break;

			default:
				break;
		}
	}
	else if (!this->bKey_1)
	{
		this->bCameraToggle = false;
	}
}

void entity::Player::LampToggle()
{
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

void entity::Player::ThirdPersonMovement(float tDeltaTime)
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

		playerTransforms[1]->SetPosition(playerTransforms[0]->GetPosition());
		playerTransforms[1]->SetLocalPosition(glm::vec3(0.0f, 5.0f, 0.0f));

		pThirdPersonCam->MoveCenter(movement);
		ResetBinoculars();
	}

	if (this->bKey_S)
	{
		glm::vec3 movement = playerTransforms[0]->GetForwardVector() * -fMoveSpeed * tDeltaTime;

		for (Transform* object : playerTransforms)
		{
			object->Move(movement);
		}

		playerTransforms[1]->SetPosition(playerTransforms[0]->GetPosition());
		playerTransforms[1]->SetLocalPosition(glm::vec3(0.0f, 5.0f, 0.0f));

		pThirdPersonCam->MoveCenter(movement);
		ResetBinoculars();
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
		playerTransforms[2]->SetLocalPosition((playerTransforms[0]->GetForwardVector() * -10.0f) + glm::vec3(0.0f, 5.0f, 0.0f));
		playerTransforms[3]->SetLocalPosition((playerTransforms[0]->GetForwardVector() * 10.0f));

		/* Reset Binoculars To Face The Front */
		ResetBinoculars();

		/* Set Camera Centers: FPCam always point forward, TPCam always point at tank */
		
		pThirdPersonCam->SetCenter(playerTransforms[0]->GetPosition());
		ResetBinoculars();
	}

	if (this->bKey_D)
	{
		float rotationAmount = -fRotationSpeed * tDeltaTime;

		playerTransforms[0]->Rotate(RotationAxis::YAW, rotationAmount);

		playerTransforms[2]->SetLocalPosition((playerTransforms[0]->GetForwardVector() * -10.0f) + glm::vec3(0.0f, 5.0f, 0.0f));
		playerTransforms[3]->SetLocalPosition((playerTransforms[0]->GetForwardVector() * 10.0f));

		pThirdPersonCam->SetCenter(playerTransforms[0]->GetPosition());
		ResetBinoculars();
	}
}

void entity::Player::ResetBinoculars()
{
	glm::vec3 rotation = this->pTank->GetTransform()->GetRotation();
	this->pFirstPersonCam->GetTransform()->SetRotation(RotationAxis::PITCH, rotation.x);
	this->pFirstPersonCam->GetTransform()->SetRotation(RotationAxis::YAW, rotation.y);
	this->pFirstPersonCam->GetTransform()->SetRotation(RotationAxis::ROLL, rotation.z);
	this->pFirstPersonCam->SetCenter(PointForward());
}

void Player::Draw()
{
	LightData pointLightData = this->pTankLight->GetLightData();
	CameraData cameraData = GetCameraData();

	pTank->Draw(cameraData, pointLightData, this->pDirectionaLightData);
}

const glm::vec3 entity::Player::PointForward()
{
	glm::vec3 Forward = this->pFirstPersonCam->GetTransform()->GetForwardVector() * 1000.0f;
	Forward += this->pFirstPersonCam->GetTransform()->GetPosition();
	return Forward;
}

CameraData Player::GetCameraData()
{
	CameraData cameraData;

	switch (ECurrentActiveCamera)
	{
		case ActiveCamera::THIRDPERSON:
			cameraData = this->pThirdPersonCam->GetCameraData();
			break;

		case ActiveCamera::FIRSTPERSON:
			cameraData = this->pFirstPersonCam->GetCameraData();
			break;

		case ActiveCamera::BIRDSEYE:
			cameraData = this->pBirdEyeCam->GetCameraData();
			break;
	}

	return cameraData;
}

LightData Player::GetPointLightData()
{
	return this->pTankLight->GetLightData();
}

void Player::AssignDirectionalLightData(LightData data)
{
	this->pDirectionaLightData = data;
}