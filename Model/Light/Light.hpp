#pragma once
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <string>
#include "LightData.hpp"

namespace light
{
	class Light
	{
		public:
			Light();

			virtual void SetLightData(LightData data) = 0;
			virtual LightData GetLightData() = 0;

			void SetLightColor(glm::vec3 lightColor);
			void SetAmbientColor(glm::vec3 ambientColor);
			void SetIntensity(float intensity);

		protected:
			glm::vec3 light_color;
			glm::vec3 ambient_color;
			float ambient_str;
			float spec_str;
			float spec_phong;
			float intensity;

	};
}


#endif // !LIGHT_HPP
