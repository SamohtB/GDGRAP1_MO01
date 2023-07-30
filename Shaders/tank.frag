#version 330 core 

out vec4 FragColor; //pixel color

uniform sampler2D tex0;
uniform sampler2D norm_tex;

uniform vec3 pointLightPos;
uniform vec3 pointLightColor;
uniform vec3 pointLightAmbientColor;
uniform float pointLightAmbientStr;
uniform float pointLightSpecStr;
uniform float pointLightSpecPhong;
uniform float pointLightIntensity;

uniform vec3 directionalLightDir;
uniform vec3 directionalLightColor;
uniform vec3 directionalLightAmbientColor;
uniform float directionalLightAmbientStr;
uniform float directionalLightSpecStr;
uniform float directionalLightSpecPhong;
uniform float dirLightIntensity;

uniform vec3 cameraPos;

in vec2 texCoord;
in vec3 normCoord;
in vec3 fragPos;
in mat3 TBN;

vec3 CalculateDirectionalLight()
{
	vec3 normal = texture(norm_tex, texCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(TBN * normal);

	vec3 lightDir = directionalLightDir;
	
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * directionalLightColor;

	vec3 ambientCol = directionalLightAmbientColor * directionalLightAmbientStr;

	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(reflectDir, viewDir), 0.1), directionalLightSpecPhong);
	vec3 specColor = spec * directionalLightSpecStr * directionalLightColor;

	vec3 finalColor = (specColor + diffuse + ambientCol) * dirLightIntensity;

	return finalColor;
}

vec3 CalculatePointLight()
{
	vec3 normal = texture(norm_tex, texCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(TBN * normal);

	vec3 lightDir = normalize(pointLightPos - fragPos);
	
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * pointLightColor;

	vec3 ambientCol = pointLightAmbientColor * pointLightSpecStr;

	vec3 viewDir = normalize(cameraPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(reflectDir, viewDir), 0.1), pointLightSpecPhong);
	vec3 specColor = spec * pointLightSpecStr * pointLightColor;

	float distance = distance(pointLightPos, fragPos);
	float intensity = pointLightIntensity * (1 / (distance * distance));

	vec3 finalColor = (specColor + diffuse + ambientCol) * intensity;

	return finalColor;
}


void main()
{
	vec4 pixelColor = texture(tex0, texCoord);

	if(pixelColor.a < 0.1)
	{
		discard;
	}

	vec3 pointLight = CalculatePointLight();
	vec3 directionalLight = CalculateDirectionalLight();

	vec3 finalColor = pointLight + directionalLight;

	FragColor = vec4(finalColor, 1.0) * pixelColor;
}