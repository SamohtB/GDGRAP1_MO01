#ifndef ENTITY_TANK_HPP
#define ENTITY_TANK_HPP

#include "../BaseClass/Model.hpp"
#include "../BaseClass/Shader.hpp"
#include "../BaseClass/Texture/Texture.hpp"
#include "../BaseClass/Texture/Normals.hpp"
#include "../BaseClass/Transform/Transform.hpp"
#include "../Camera/CameraData.hpp"
#include "../Light/LightData.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace entity
{
	using namespace base_class;

	class Tank
	{
		public:
			Tank();

			void Draw(CameraData cameraData, LightData pointLight, LightData directionalLight);
			Transform* GetTransform();

		private:
			void VertexInit();

		private:
			Model* model;
			Shader* shader;
			Texture* texture;
			Normals* normals;
			Transform* transform;

			/* File Names */
			const std::string strMesh = "3D/Tank/Tank.obj";
			const std::string strTex = "3D/Tank/Body_d.jpg";
			const std::string strNorm = "3D/Tank/Body_n.jpg";
			const std::string strVert = "Shaders/tank.vert";
			const std::string strFrag = "Shaders/tank.frag";
	};
}
#endif // !ENTITY_TANK_HPP
