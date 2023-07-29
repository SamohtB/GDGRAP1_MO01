#include "Shader.hpp"

using namespace base_class;

Shader::Shader(std::string strVertex, std::string strFragment)
{
	LoadShader(strVertex, strFragment);
}

void Shader::LoadShader(std::string strVertex, std::string strFragment)
{
    std::fstream vertSrc(strVertex);
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    std::fstream fragSrc(strFragment);
    std::stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();
    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &v, NULL);
    glCompileShader(vertShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &f, NULL);
    glCompileShader(fragShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);

    glLinkProgram(shaderProgram);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    this->shaderProgram = shaderProgram;
}

GLuint Shader::GetShaderProgram()
{
    return this->shaderProgram;
}