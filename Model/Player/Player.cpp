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

	dCurrentMouseX = 0.0f;
	dCurrentMouseY = 0.0f;

	dPreviousMouseX = 0.0f;
	dPreviousMouseY = 0.0f;

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
	this->pFirstPersonCam->SetFarPlane(225.0f);
}

void entity::Player::CreateThirdPersonCam()
{
	this->pThirdPersonCam = new PerspectiveCamera();
	this->pThirdPersonCam->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 5.0f, -10.0f));
	this->pThirdPersonCam->SetCenter(this->pTank->GetTransform()->GetPosition());
	this->pThirdPersonCam->SetFOV(60.0f);
	this->pThirdPersonCam->SetFarPlane(150.0f);
}

void entity::Player::CreateBirdEyeCam()
{
	this->pBirdEyeCam = new OrthographicCamera();
	this->pBirdEyeCam->SetPosition(glm::vec3(0.0f, 20.0f, -1.0f));
	this->pBirdEyeCam->SetCenter(this->pTank->GetTransform()->GetPosition());
	this->pBirdEyeCam->SetSize(45.0f);
	this->pBirdEyeCam->SetFarPlane(100.0f);
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

	glfwGetCursorPos(window, &this->dCurrentMouseX, &this->dCurrentMouseY);
}

void Player::Update(float tDeltaTime)
{
	/* Lamp Toggle and Bird's Eye Toggle Always Active*/
	LampToggle();
	BirdEyeToggle();
		
	switch (ECurrentActiveCamera)
	{
		/* Only Toggle FPCam and TPCam when using a perspective camera */
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

/* Ortho Camera Movement - Moves the camera and the center */
void entity::Player::BirdEyeMovement(float tDeltaTime)
{
	float movement = fMoveSpeed * tDeltaTime;

	if (this->bKey_W)
	{
		this->pBirdEyeCam->SetPosition(glm::vec3(0.0f, 0.0f, movement) + this->pBirdEyeCam->GetPosition());
		this->pBirdEyeCam->MoveCenter(glm::vec3(0.0f, 0.0f, movement));
	}

	if (this->bKey_S)
	{
		this->pBirdEyeCam->SetPosition(glm::vec3(0.0f, 0.0f, -movement) + this->pBirdEyeCam->GetPosition());
		this->pBirdEyeCam->MoveCenter(glm::vec3(0.0f, 0.0f, -movement));
	}

	if (this->bKey_A)
	{
		this->pBirdEyeCam->SetPosition(glm::vec3(movement, 0.0f, 0.0f) + this->pBirdEyeCam->GetPosition());
		this->pBirdEyeCam->MoveCenter(glm::vec3(movement, 0.0f, 0.0f));
	}

	if (this->bKey_D)
	{
		this->pBirdEyeCam->SetPosition(glm::vec3(-movement, 0.0f, 0.0f) + this->pBirdEyeCam->GetPosition());
		this->pBirdEyeCam->MoveCenter(glm::vec3(-movement, 0.0f, 0.0f));
	}
}

/* Swtiches Between Bird Eye Cam and Previous Camera State */
void entity::Player::BirdEyeToggle()
{
	if (this->bKey_2 && !this->bTopToggle)
	{
		/* Only Read Once Per Press */
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

/* Resets the Ortho Cam to Start on the Player */
void entity::Player::ResetBirdView()
{
	this->pBirdEyeCam->SetPosition(this->pTank->GetTransform()->GetPosition() + glm::vec3(0.0, 20.0, -1.0f));
	this->pBirdEyeCam->SetCenter(this->pTank->GetTransform()->GetPosition());
}

/* FPCam Movement - Rotates the camera's transform. */
/*Calculates forward vector given the euler rotations to make the camera face forward */
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

/* Swtiches Between First Person and Third Person Camera */
void entity::Player::PerspectiveCameraToggle()
{
	if (this->bKey_1 && !this->bCameraToggle)
	{
		/* Only Read Once Per Press */
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

/* Cycles Light Intensity */
void entity::Player::LampToggle()
{
	if (this->bKey_F && !this->bLampToggle)
	{
		/* Only Read Once Per Press */
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

/* Third Person Camera Movement */
void entity::Player::ThirdPersonMovement(float tDeltaTime)
{
	double dDeltaX = this->dCurrentMouseX - this->dPreviousMouseX;
	double dDeltaY = this->dCurrentMouseY - this->dPreviousMouseY;

	this->dPreviousMouseX = this->dCurrentMouseX;
	this->dPreviousMouseY = this->dCurrentMouseY;

	/* Same Transforms, Different Local Transfroms : 0 = Mesh, 1 = FPCamera, 2 = TPCamera, 3 = Light */
	std::vector<Transform*> playerTransforms;

	playerTransforms.push_back(this->pTank->GetTransform());
	playerTransforms.push_back(this->pFirstPersonCam->GetTransform());
	playerTransforms.push_back(this->pThirdPersonCam->GetTransform());
	playerTransforms.push_back(this->pTankLight->GetTransform());

	if (this->bKey_W)
	{
		glm::vec3 movement = playerTransforms[0]->GetForwardVector() * fMoveSpeed * tDeltaTime;

		/* Move Everything Forward - Whatever Forward is */
		for (Transform* object : playerTransforms)
		{
			object->Move(movement);
		}

		/* Set FP Cam Above the Mesh */
		playerTransforms[1]->SetPosition(playerTransforms[0]->GetPosition());
		playerTransforms[1]->SetLocalPosition(glm::vec3(0.0f, 5.0f, 0.0f));

		/* Also Move the center when moving */
		pThirdPersonCam->MoveCenter(movement);
		/* Make FPCam to face forward */
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
		float rotationAmount = fRotationSpeed * tDeltaTime;

		/* Rotate Mesh and Third Person Cam */
		playerTransforms[0]->Rotate(RotationAxis::YAW, rotationAmount);
		playerTransforms[2]->Rotate(RotationAxis::YAW, rotationAmount);

		/* Set TPCamera To be 10 units behind the mesh + up offset */
		playerTransforms[2]->SetLocalPosition((playerTransforms[0]->GetForwardVector() * -10.0f)
			+ glm::vec3(0.0f, 5.0f, 0.0f));

		/* Set FPCamera To be 10 units in front the mesh */
		playerTransforms[3]->SetLocalPosition((playerTransforms[0]->GetForwardVector() * 10.0f));

		/* Set TPCam Center according to the new forward vector */
		pThirdPersonCam->SetCenter(playerTransforms[2]->GetPosition() + playerTransforms[2]->GetForwardVector());
		/* Reset Binoculars To Face The Front */
		ResetBinoculars();
	}

	if (this->bKey_D)
	{
		float rotationAmount = -fRotationSpeed * tDeltaTime;

		playerTransforms[0]->Rotate(RotationAxis::YAW, rotationAmount);

		playerTransforms[2]->SetLocalPosition((playerTransforms[0]->GetForwardVector() * -10.0f)
			+ glm::vec3(0.0f, 5.0f, 0.0f));
		playerTransforms[2]->Rotate(RotationAxis::YAW, rotationAmount);
		playerTransforms[3]->SetLocalPosition((playerTransforms[0]->GetForwardVector() * 10.0f));

		pThirdPersonCam->SetCenter(playerTransforms[2]->GetPosition() + playerTransforms[2]->GetForwardVector());
		ResetBinoculars();
	}

	/* Rotate the TPCam only: along with its center */
	/* Mouse Movement */
	if(dDeltaX > 10.0f)
	{
		pThirdPersonCam->GetTransform()->Rotate(RotationAxis::YAW, -fRotationSpeed * tDeltaTime);
		pThirdPersonCam->SetCenter(playerTransforms[2]->GetPosition() + playerTransforms[2]->GetForwardVector());
	}

	if (dDeltaX < -10.0f)
	{
		pThirdPersonCam->GetTransform()->Rotate(RotationAxis::YAW, fRotationSpeed * tDeltaTime);
		pThirdPersonCam->SetCenter(playerTransforms[2]->GetPosition() + playerTransforms[2]->GetForwardVector());
	}

	if (dDeltaY > 10.0f)
	{
		pThirdPersonCam->GetTransform()->Rotate(RotationAxis::PITCH, -fRotationSpeed * tDeltaTime);
		pThirdPersonCam->SetCenter(playerTransforms[2]->GetPosition() + playerTransforms[2]->GetForwardVector());
	}

	if (dDeltaY < -10.0f)
	{
		pThirdPersonCam->GetTransform()->Rotate(RotationAxis::PITCH, fRotationSpeed * tDeltaTime);
		pThirdPersonCam->SetCenter(playerTransforms[2]->GetPosition() + playerTransforms[2]->GetForwardVector());
	}
}

/* Make FPCam have the same rotation as the Mesh, then point the cam forward */
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

/* Return Camera Data depending on active camera */
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