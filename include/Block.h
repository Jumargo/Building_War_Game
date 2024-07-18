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
    glm::vec3 Position;  // Añadir la posición del bloque

    Block(BlockType type, glm::vec3 position);

    void Render(Shader& shader, GLuint VAO);

    glm::vec3 getMin() const;
    glm::vec3 getMax() const;
};
