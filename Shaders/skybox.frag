#version 330 core 

out vec4 FragColor; //pixel color

in vec3 texCoord;

uniform samplerCube skybox;
uniform bool NV;

void main()
{
	
	vec3 COLOR = vec3(1, 1, 1);

	if(NV)
	{
		COLOR = vec3(0.1, 0.95, 0.2);
	}

	FragColor = texture(skybox, texCoord) * vec4(COLOR, 1);
}