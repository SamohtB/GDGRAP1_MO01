#include "Environment.hpp"

using namespace entity;

Environment::Environment()
{
	this->shader = new Shader(strVert,strFrag);
    this->skybox = new SkyBox(strFileNames);
	this->LoadVertices();
}

void Environment::LoadVertices()
{
    glBindVertexArray(this->skybox->GetVAO());

    glBindBuffer(GL_ARRAY_BUFFER, this->skybox->GetVBO());
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->skyboxVertices), &this->skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->skybox->GetEBO());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_INT) * 36, &skyboxIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
}

void Environment::Draw(CameraData data)
{
    glUseProgram(this->shader->GetShaderProgram());

    glm::mat4 sky_view = glm::mat4(1.0f);
    sky_view = glm::mat4(glm::mat3(data.view_matrix));

    unsigned int skyProjectionLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "projection");
    glUniformMatrix4fv(skyProjectionLoc, 1, GL_FALSE, glm::value_ptr(data.projection_matrix));

    unsigned int skyViewLoc = glGetUniformLocation(this->shader->GetShaderProgram(), "view");
    glUniformMatrix4fv(skyViewLoc, 1, GL_FALSE, glm::value_ptr(sky_view));

    glBindVertexArray(this->skybox->GetVAO());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->skybox->GetTexture());

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
