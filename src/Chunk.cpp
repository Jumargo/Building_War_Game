#include "Chunk.h"
#include "Block.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>

Chunk::Chunk(glm::vec3 position) : Position(position)
{
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                glm::vec3 blockPos = position + glm::vec3(x, y, z);
                if (x % 3 == 0) blocks[x][y][z] = new Block(WATER, blockPos);
                else if (x % 3 == 1) blocks[x][y][z] = new Block(DIRT, blockPos);
                else blocks[x][y][z] = new Block(STONE, blockPos);
            }
        }
    }
}

void Chunk::Render(Shader& shader, GLuint VAO)
{
    glBindVertexArray(VAO);
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                glm::vec3 blockPos = Position + glm::vec3(x, y, z);
                glm::mat4 model = glm::translate(glm::mat4(1.0f), blockPos);
                shader.setMat4("model", model);

                Block* block = blocks[x][y][z];
                if (block != nullptr) {
                    shader.setVec3("uniformColor", block->Color);  // Pasar el color uniforme del bloque

                    // Renderizar el bloque normalmente
                    glDrawArrays(GL_TRIANGLES, 0, 36);

                    // Cambiar al modo wireframe
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    glLineWidth(2.0f);
                    shader.setVec3("uniformColor", glm::vec3(0.0, 0.0, 0.0));  // Usar color negro para las líneas
                    glDrawArrays(GL_TRIANGLES, 0, 36);

                    // Restaurar el modo de relleno
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
            }
        }
    }
    glBindVertexArray(0);
}
