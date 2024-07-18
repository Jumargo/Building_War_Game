#pragma once
#include <GL/glew.h> 
#include <glm/glm.hpp>

enum BlockType {
    WATER,
    DIRT,
    STONE
};

class Shader; // Forward declaration

class Block {
public:
    BlockType Type;
    glm::vec3 Color;

    Block(BlockType type);

    void Render(Shader& shader, GLuint VAO);
};
