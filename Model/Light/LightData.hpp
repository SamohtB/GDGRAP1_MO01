#pragma once
#ifndef LIGHT_DATA_HPP
#define LIGHT_DATA_HPP

#include "glm/glm.hpp"

struct LightData
{
	glm::vec3 light_position = glm::vec3(0.0f);
	glm::vec3 light_direction = glm::vec3(0.0f);
	glm::vec3 light_color = glm::vec3(0.0f);
	glm::vec3 ambient_color = glm::vec3(0.0f);

	float ambient_str = 0.0f;
	float spec_str = 0.0f;
	float spec_phong = 0.0f;
	float intensity = 0.0f;
};

#endif // !LIGHT_DATA_HPP