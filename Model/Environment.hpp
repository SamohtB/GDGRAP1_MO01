#ifndef ENTITY_ENVIRONMENT_HPP
#define ENTITY_ENVIRONMENT_HPP

#include "BaseClass/Shader.hpp"
#include "BaseClass/Texture/SkyBox.hpp"
#include "Camera/CameraData.hpp"

#include "glm/gtc/type_ptr.hpp"

namespace entity
{
	using namespace base_class;

	class Environment
	{
		public:
			Environment();

			void Draw(CameraData data);

		private:
			void LoadVertices();

		private:
			Shader* shader;
			SkyBox* skybox;

		private:
			const std::string strVert = "Shaders/skybox.vert";
			const std::string strFrag = "Shaders/skybox.frag";
			const std::vector<std::string> strFileNames
			{
				"3D/Skybox/Night_rt.png",
				"3D/Skybox/Night_lf.png",
				"3D/Skybox/Night_up.png",
				"3D/Skybox/Night_dn.png",
				"3D/Skybox/Night_ft.png",
				"3D/Skybox/Night_bk.png"
			};

			const float skyboxVertices[24]{
				-1.f, -1.f, 1.f,
				1.f, -1.f, 1.f,
				1.f, -1.f, -1.f,
				-1.f, -1.f, -1.f,
				-1.f, 1.f, 1.f,
				1.f, 1.f, 1.f,
				1.f, 1.f, -1.f,
				-1.f, 1.f, -1.f
			};

			const  unsigned int skyboxIndices[36]{
				1,2,6,
				6,5,1,

				0,4,7,
				7,3,0,

				4,5,6,
				6,7,4,

				0,3,2,
				2,1,0,

				0,1,5,
				5,4,0,

				3,7,6,
				6,2,3
			};
	};
}
#endif // !ENTITY_ENVIRONMENT_HPP
