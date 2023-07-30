#pragma once
#ifndef BASE_CLASS_SKYBOX_HPP
#define BASE_CLASS_SKYBOX_HPP

#include "../../stb_image.h"

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <string>
#include <vector>

namespace base_class
{
	class SkyBox
	{
		public:
			SkyBox(std::vector<std::string> strFileNames);
			~SkyBox();

			GLuint GetTexture();
			GLuint GetVAO();
			GLuint GetVBO();
			GLuint GetEBO();

		private:
			void LoadTextures(std::vector<std::string> strFileNames);

		private:
			GLuint VAO, VBO, EBO;
			GLuint texture;
	};
}
#endif