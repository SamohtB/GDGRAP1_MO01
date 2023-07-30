#pragma once
#ifndef CONTROLLER_GAME_HPP
#define CONTROLLER_GAME_HPP

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Config/Settings.hpp"

#include "../Model/Player/Player.hpp"
#include "../Model/Clutter/Clutter.hpp"

namespace Controller
{
	using namespace entity;

	class Game
	{
		public:
			Game();
			void Run();

		private:
			/* GameObjects */
			Player* player;
			std::vector<Clutter*> clutterList;

		private:
			void Initialize();
			void ProcessInput();
			void Update(float tDeltaTime);
			void Render();

		private:
			GLFWwindow* gameWindow;

	};
}


#endif // !SYSTEM_GAME_H

