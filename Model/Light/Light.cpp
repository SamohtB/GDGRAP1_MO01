#pragma once
#include "Light.hpp"

using namespace light;

Light::Light()
{
	light_color = glm::vec3(0.0f, 0.0f, 0.0f);
	ambient_color = glm::vec3(0.0f, 0.0f, 0.0f);
	ambient_str = 0.0f;
	spec_str = 0.0f;
	spec_phong = 0.0f;
	intensity = 0.0f;
}

void Light::SetLightColor(glm::vec3 lightColor)
{
	light_color = lightColor;
}

void Light::SetAmbientColor(glm::vec3 ambientColor)
{
	ambient_color = ambientColor;
}

void Light::SetIntensity(float intensity)
{
	this->intensity = intensity;
}

