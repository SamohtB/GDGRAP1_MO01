#ifndef ENTITY_CLUTTER_HPP
#define ENTITY_CLUTTER_HPP

#include "../BaseClass/Model.hpp"
#include "../BaseClass/Shader.hpp"
#include "../BaseClass/Texture/Texture.hpp"
#include "../BaseClass/Transform/Transform.hpp"
#include "../Camera/CameraData.hpp"
#include "../Light/LightData.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace entity
{
	using namespace base_class;

	class Clutter
	{
	public:
		Clutter();

		virtual void Initialize(std::string strMesh, std::string strTex, std::string strVert, std::string strFrag);
		void Draw(CameraData cameraData, LightData pointLight, LightData directionalLight);
		Transform* GetTransform();

	private:
		void VertexInit();

	private:
		Model* model;
		Shader* shader;
		Texture* texture;
		Transform* transform;
	};
}
#endif // !ENTITY_CLUTTER_HPP
