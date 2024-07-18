#include "Block.h"
#include "Shader.h"
#include <GL/glew.h>

Block::Block(BlockType type, glm::vec3 position) : Type(type), Position(position) {
    switch (type) {
    case WATER: Color = glm::vec3(0.0f, 0.0f, 1.0f); break;
    case DIRT: Color = glm::vec3(0.5f, 0.35f, 0.05f); break;
    case STONE: Color = glm::vec3(0.3f, 0.3f, 0.3f); break;
    }
}

void Block::Render(Shader& shader, GLuint VAO) {
    shader.use();
    glUniform3fv(glGetUniformLocation(shader.Program, "ourColor"), 1, glm::value_ptr(Color));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

glm::vec3 Block::getMin() const {
    return Position - glm::vec3(0.5f, 0.5f, 0.5f);  // Ajustar según el tamaño del bloque
}

glm::vec3 Block::getMax() const {
    return Position + glm::vec3(0.5f, 0.5f, 0.5f);  // Ajustar según el tamaño del bloque
}
