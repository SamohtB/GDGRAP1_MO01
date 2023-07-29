#ifndef BASE_CLASS_NORMALS_HPP
#define BASE_CLASS_NORMALS_HPP

#include "../../stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace base_class
{
	class Normals
	{
		public:
			Normals(std::string strNorm);
			~Normals();

			GLuint GetNormals();

		private:
			void LoadNormals(std::string strNorm);

		protected:
			GLuint normals_texture;

	};
}
#endif // !BASE_CLASS_NORMALS_HPP