#pragma once
#ifndef CONTROLLER_GAME_HPP
#define CONTROLLER_GAME_HPP

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Config/Settings.hpp"

namespace Controller
{

	class Game
	{
		public:
			Game();
			//void DebugInit();
			void Run();

		private:
			/* GameObjects */

		private:
			void Initialize();
			void ProcessInput();
			void Update(float tDeltaTime);
			void Render();

		private:
			GLFWwindow* gameWindow;

		private:
			//Debug test;

	};
}


#endif // !SYSTEM_GAME_H

