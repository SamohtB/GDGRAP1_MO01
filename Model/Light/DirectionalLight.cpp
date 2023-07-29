#pragma once
#include "DirectionalLight.hpp"

using namespace light;

DirectionalLight::DirectionalLight()
{
	this->lightDirection = glm::vec3(0.0f, 1.0f, 0.0f);
}

void DirectionalLight::SetDirection(glm::vec3 direction)
{
	this->lightDirection = direction;
}

void DirectionalLight::SetLightData(LightData data)
{
	this->lightDirection = data.light_direction;
	this->light_color = data.light_color;
	this->ambient_color = data.ambient_color;
	this->ambient_str = data.ambient_str;
	this->spec_str = data.spec_str;
	this->spec_phong = data.spec_phong;
	this->intensity = data.intensity;
}

LightData DirectionalLight::GetLightData()
{
	LightData data;

	data.light_direction = this->lightDirection;
	data.light_color = this->light_color;
	data.ambient_color = this->ambient_color;
	data.ambient_str = this->ambient_str;
	data.spec_str = this->spec_str;
	data.spec_phong = this->spec_phong;
	data.intensity = this->intensity;

	return data;
}
