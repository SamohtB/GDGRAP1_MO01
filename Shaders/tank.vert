#version 330 core 

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 aTex;
layout(location = 3) in vec3 m_tan;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

out vec2 texCoord;
out vec3 normCoord;
out vec3 fragPos;
out mat3 TBN;

void main()
{
	//projection -> camera -> transform -> local point
	gl_Position = projection * view * transform * vec4(aPos, 1.0);

	mat3 modelMat = mat3(transpose(inverse(transform)));
	normCoord =  modelMat * vertexNormal;

	vec3 T = normalize(modelMat * m_tan);
	vec3 N = normalize(normCoord);
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);

	TBN = mat3(T, B, N);

	fragPos = vec3(transform * vec4(aPos, 1.0));

	texCoord = aTex;
}