#pragma once
#ifndef LIGHT_DIRECTIONAL_LIGHT_HPP
#define LIGHT_DIRECTIONAL_LIGHT_HPP

#include "Light.hpp"

namespace light
{
	class DirectionalLight : public Light
	{
		public:
			DirectionalLight();

			void SetDirection(glm::vec3 direction);
			void SetLightData(LightData data);
			LightData GetLightData();

		private:
			glm::vec3 lightDirection;
	};
}
#endif // !LIGHT_DIRECTIONAL_LIGHT_HPP