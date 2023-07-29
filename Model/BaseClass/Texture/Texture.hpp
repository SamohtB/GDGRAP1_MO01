#ifndef BASE_CLASS_TEXTURE_HPP
#define BASE_CLASS_TEXTURE_HPP

#include "../../stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace base_class
{
	class Texture
	{
		public:
			Texture(std::string strTex);
			~Texture();

			GLuint GetTexture();

		private:
			void LoadTexture(std::string strTex);

		protected:
			GLuint texture;

	};
}
#endif // !BASE_CLASS_TEXTURE_HPP
