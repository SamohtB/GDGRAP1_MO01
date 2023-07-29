#pragma once
#ifndef BASE_CLASS_SHADER_HPP
#define BASE_CLASS_SHADER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>

namespace base_class
{
	class Shader
	{
		public:
			Shader(std::string strVertex, std::string strFragment);

			GLuint GetShaderProgram();

		private:
			void LoadShader(std::string strVertex, std::string strFragment);

		protected:
			GLuint shaderProgram;
	};
}

#endif // !BASE_CLASS_SHADER_HPP
