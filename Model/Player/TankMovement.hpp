#pragma once
#ifndef INPUT_TANK_MOVEMENT_HPP
#define INPUT_TANK_MOVEMENT_HPP

#include "GLFW/glfw3.h"

namespace input
{
	class TankMovement
	{
	public:
		TankMovement();

		void ProcessInput(GLFWwindow* window);
		void Update(float tDeltaTime);
	};
}



#endif // !INPUT_TANK_MOVEMENT_HPP
