#include "SkyBox.hpp"

using namespace base_class;

SkyBox::SkyBox(std::vector<std::string> strFileNames)
{
    LoadTextures(strFileNames);

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
}

SkyBox::~SkyBox()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
    glDeleteTextures(1, &this->texture);
}

void SkyBox::LoadTextures(std::vector<std::string> strFileNames)
{
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);

    //Avoid Pixilated texture
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //Avoid Tiling
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++)
    {
        int w, h, skyCChannel;
        stbi_set_flip_vertically_on_load(false);

        unsigned char* data = stbi_load(strFileNames[i].c_str(), &w, &h, &skyCChannel, 0);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

            stbi_image_free(data);
        }
    }

    stbi_set_flip_vertically_on_load(true);
}

GLuint SkyBox::GetTexture()
{
    return this->texture;
}

GLuint SkyBox::GetVAO()
{
    return this->VAO;
}

GLuint SkyBox::GetVBO()
{
    return this->VBO;
}

GLuint SkyBox::GetEBO()
{
    return this->EBO;
}