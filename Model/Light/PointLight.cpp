#pragma once
#include "PointLight.hpp"

using namespace light;

PointLight::PointLight()
{
	this->transform = new Transform();
}

void PointLight::SetLightData(LightData data)
{
	this->light_color = data.light_color;
	this->ambient_color = data.ambient_color;
	this->ambient_str = data.ambient_str;
	this->spec_str = data.spec_str;
	this->spec_phong = data.spec_phong;
	this->intensity = data.intensity;
}

LightData PointLight::GetLightData()
{
	LightData data;

	data.light_position = this->transform->GetPosition();
	data.light_color = this->light_color;
	data.ambient_color = this->ambient_color;
	data.ambient_str = this->ambient_str;
	data.spec_str = this->spec_str;
	data.spec_phong = this->spec_phong;
	data.intensity = this->intensity;

	return data;
}