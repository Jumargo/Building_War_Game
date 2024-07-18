#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "Shader.h"
#include "Block.h"

const int CHUNK_SIZE = 10;

class Chunk {
public:
    glm::vec3 Position;
    Block* blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]; // Matriz 3D de bloques

    Chunk(glm::vec3 position);
    void Render(Shader& shader, GLuint VAO);
};
