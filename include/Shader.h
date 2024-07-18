#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    GLuint Program;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;  // Declaraci�n de la funci�n setVec3
private:
    std::string readFile(const char* filePath);
    void checkCompileErrors(GLuint shader, std::string type);
};
