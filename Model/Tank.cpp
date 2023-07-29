#include "Tank.hpp"

using namespace entity;

Tank::Tank()
{
	this->model = new Model(strMesh);
	this->shader = new Shader(strVert, strFrag);
	this->texture = new Texture(strTex);
	this->normals = new Normals(strNorm);
	this->transform = new Transform();

	this->transform->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
	this->transform->SetScale(1.0f);
}

void Tank::Draw(CameraData cameraData, LightData pointLight, LightData directionalLight)
{
    const GLuint SHADER_PROG = this->shader->GetShaderProgram();
    glUseProgram(SHADER_PROG);

    unsigned int transformLoc = glGetUniformLocation(SHADER_PROG, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform->GetModelMatrix()));

    unsigned int viewLoc = glGetUniformLocation(SHADER_PROG, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cameraData.view_matrix));

    unsigned int projectionLoc = glGetUniformLocation(SHADER_PROG, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraData.projection_matrix));

    GLuint cameraPosLoc = glGetUniformLocation(SHADER_PROG, "cameraPos");
    glUniform3fv(cameraPosLoc, 1, glm::value_ptr(cameraData.camera_pos));

    glActiveTexture(GL_TEXTURE0);
    GLuint tex0Loc = glGetUniformLocation(SHADER_PROG, "tex0");
    glBindTexture(GL_TEXTURE_2D, this->texture->GetTexture());
    glUniform1i(tex0Loc, 0);

    glActiveTexture(GL_TEXTURE1);
    GLuint tex1Loc = glGetUniformLocation(SHADER_PROG, "norm_tex");
    glBindTexture(GL_TEXTURE_2D, this->normals->GetNormals());
    glUniform1i(tex1Loc, 1);

    /* pass point light data */
    GLuint pointPosLoc = glGetUniformLocation(SHADER_PROG, "pointLightPos");
    glUniform3fv(pointPosLoc, 1, glm::value_ptr(pointLight.light_position));

    GLuint pointColorLoc = glGetUniformLocation(SHADER_PROG, "pointLightColor");
    glUniform3fv(pointColorLoc, 1, glm::value_ptr(pointLight.light_color));

    GLuint pointAmbientStrLoc = glGetUniformLocation(SHADER_PROG, "pointLightAmbientStr");
    glUniform1f(pointAmbientStrLoc, pointLight.ambient_str);

    GLuint pointAmbientColorLoc = glGetUniformLocation(SHADER_PROG, "pointLightAmbientColor");
    glUniform3fv(pointAmbientColorLoc, 1, glm::value_ptr(pointLight.ambient_color));

    GLuint pointSpecStrLoc = glGetUniformLocation(SHADER_PROG, "pointLightSpecStr");
    glUniform1f(pointSpecStrLoc, pointLight.spec_str);

    GLuint pointSpecPhongLoc = glGetUniformLocation(SHADER_PROG, "pointLightSpecPhong");
    glUniform1f(pointSpecPhongLoc, pointLight.spec_phong);

    GLuint pointIntensityLoc = glGetUniformLocation(SHADER_PROG, "pointLightIntensity");
    glUniform1f(pointIntensityLoc, pointLight.intensity);

    /* pass directional light data */
    GLuint dirDirLoc = glGetUniformLocation(SHADER_PROG, "directionalLightDir");
    glUniform3fv(dirDirLoc, 1, glm::value_ptr(directionalLight.light_direction));

    GLuint dirColorLoc = glGetUniformLocation(SHADER_PROG, "directionalLightColor");
    glUniform3fv(dirColorLoc, 1, glm::value_ptr(directionalLight.light_color));

    GLuint dirAmbientStrLoc = glGetUniformLocation(SHADER_PROG, "directionalLightAmbientStr");
    glUniform1f(dirAmbientStrLoc, directionalLight.ambient_str);

    GLuint dirAmbientColorLoc = glGetUniformLocation(SHADER_PROG, "directionalLightAmbientColor");
    glUniform3fv(dirAmbientColorLoc, 1, glm::value_ptr(directionalLight.ambient_color));

    GLuint dirSpecStrLoc = glGetUniformLocation(SHADER_PROG, "directionalLightSpecStr");
    glUniform1f(dirSpecStrLoc, directionalLight.spec_str);

    GLuint dirSpecPhongLoc = glGetUniformLocation(SHADER_PROG, "directionalLightSpecPhong");
    glUniform1f(dirSpecPhongLoc, directionalLight.spec_phong);

    GLuint dirIntensityLoc = glGetUniformLocation(SHADER_PROG, "dirLightIntensity");
    glUniform1f(dirIntensityLoc, directionalLight.intensity);

    glBindVertexArray(model->GetVAO());

    glDrawArrays(GL_TRIANGLES, 0, model->GetVertexData().size() / 11);
}