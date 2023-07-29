#pragma once
#ifndef LIGHT_POINT_LIGHT_HPP
#define LIGHT_POINT_LIGHT_HPP

#include "Light.hpp"
#include "../BaseClass/Transform/Transform.hpp"

namespace light
{
	class PointLight : public Light
	{
		public:
			PointLight();

			void SetLightData(LightData data);
			LightData GetLightData();

		private:
			Transform* transform;
	};
}

#endif // !LIGHT_POINT_LIGHT_HPP

