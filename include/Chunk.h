#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "Shader.h"

class Chunk
{
public:
    glm::vec3 Position;
    Chunk(glm::vec3 position);
    void Render(Shader& shader, GLuint VAO);
};

