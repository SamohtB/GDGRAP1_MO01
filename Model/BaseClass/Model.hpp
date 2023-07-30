#pragma once
#ifndef BASE_CLASS_MODEL_HPP
#define BASE_CLASS_MODEL_HPP

#include "../../tiny_obj_loader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.hpp"

namespace base_class
{
	class Model
	{
		public:
			Model(std::string strMesh);
			~Model();

			GLuint GetVAO();
			GLuint GetVBO();
			std::vector<GLfloat> GetVertexData();

		private:
			void LoadModel(std::string strMesh);

		protected:
			GLuint VAO, VBO;
			std::vector<GLfloat> fullVertexData;
	};
}

#endif