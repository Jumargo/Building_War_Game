#include "Chunk.h"

Chunk::Chunk(glm::vec3 position)
    : Position(position)
{
    // Inicializar bloques con diferentes tipos
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                // Alternar tipos de bloques para ejemplo
                if (x % 3 == 0) blocks[x][y][z] = new Block(WATER);
                else if (x % 3 == 1) blocks[x][y][z] = new Block(DIRT);
                else blocks[x][y][z] = new Block(STONE);
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
                shader.setVec3("uniformColor", block->Color);  // Pasar el color uniforme del bloque

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
    }
    glBindVertexArray(0);
}


