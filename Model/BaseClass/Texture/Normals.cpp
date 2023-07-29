#include "Normals.hpp"

using namespace base_class;

Normals::Normals(std::string strNorm)
{
    LoadNormals(strNorm);
}

Normals::~Normals()
{
    glDeleteTextures(1, &this->normals_texture);
}

void Normals::LoadNormals(std::string strNorm)
{
    stbi_set_flip_vertically_on_load(true);
    int img_width, img_height, colorChannels;

    const char* path = strNorm.c_str();
    unsigned char* tex_bytes = stbi_load(path, &img_width, &img_height, &colorChannels, 0);

    glGenTextures(1, &this->normals_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->normals_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    std::string strFileType = strNorm.substr(strNorm.length() - 3);

    if (strFileType == "png")
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_bytes);
    }
    else if (strFileType == "jpg")
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_bytes);
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(tex_bytes);
}

GLuint Normals::GetNormals()
{
    return this->normals_texture;
}