#include "Chunk.h"

Chunk::Chunk(glm::vec3 position)
    : Position(position)
{
}

void Chunk::Render(Shader& shader, GLuint VAO)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), Position);
    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
