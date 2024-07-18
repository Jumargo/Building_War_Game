#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include "Player.h"
#include "Chunk.h"
#include "Vertices.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

// Prototipos de funciones
void processInput(GLFWwindow* window, Player& player, Camera& camera, float deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
bool checkCollision(const glm::vec3& minA, const glm::vec3& maxA, const glm::vec3& minB, const glm::vec3& maxB);
bool resolveCollision(Player& player, const Block* block);

// Variables globales
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
Player player(glm::vec3(5.0f, 20.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f));
float lastX = 400, lastY = 300;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Tamaño del mapa
const int mapSize = 1;
std::vector<Chunk> chunks;

int main()
{
    Window window(800, 600, "Minecraft Clone");

    Shader shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    if (shader.Program == 0)
    {
        std::cerr << "Failed to create shader program." << std::endl;
        return -1;
    }

    GLuint cubeVBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint pyramidVBO, pyramidVAO;
    glGenVertexArrays(1, &pyramidVAO);
    glGenBuffers(1, &pyramidVBO);

    glBindVertexArray(pyramidVAO);

    glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Crear los chunks
    for (int x = 0; x < mapSize; ++x)
    {
        for (int z = 0; z < mapSize; ++z)
        {
            chunks.push_back(Chunk(glm::vec3(x, 0.0f, z)));
        }
    }

    // Configurar las callbacks de entrada
    glfwSetCursorPosCallback(window.window, mouse_callback);
    glfwSetScrollCallback(window.window, scroll_callback);
    glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Habilitar prueba de profundidad
    glEnable(GL_DEPTH_TEST);

    while (!window.shouldClose())
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window.window, player, camera, deltaTime);
        player.Update(deltaTime);

        bool collisionDetected = false;

        // Comprobar colisiones antes de actualizar la cámara
        for (auto& chunk : chunks)
        {
            for (int x = 0; x < CHUNK_SIZE; ++x) {
                for (int y = 0; y < CHUNK_SIZE; ++y) {
                    for (int z = 0; z < CHUNK_SIZE; ++z) {
                        Block* block = chunk.blocks[x][y][z];
                        if (block != nullptr) {
                            if (resolveCollision(player, block)) {
                                collisionDetected = true;
                                std::cout << "Colisión detectada con el bloque en: (" << x << ", " << y << ", " << z << ")\n";
                            }
                        }
                    }
                }
            }
        }

        if (!collisionDetected) {
            // Actualizar posición de la cámara para seguir al jugador desde atrás
            camera.UpdateCameraPosition(player);
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // Renderizar los chunks (cubos)
        for (auto& chunk : chunks)
        {
            chunk.Render(shader, cubeVAO);
        }

        // Renderizar la pirámide del jugador
        shader.setVec3("uniformColor", glm::vec3(0.0, 0.0, 0.0));  // Desactivar el color uniforme
        glm::mat4 model = glm::translate(glm::mat4(1.0f), player.Position);
        model = glm::scale(model, player.Size);
        shader.setMat4("model", model);

        glBindVertexArray(pyramidVAO);
        glDrawArrays(GL_TRIANGLES, 0, 18);

        window.swapBuffers();
        window.pollEvents();
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);

    glDeleteVertexArrays(1, &pyramidVAO);
    glDeleteBuffers(1, &pyramidVBO);

    return 0;
}

void processInput(GLFWwindow* window, Player& player, Camera& camera, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    player.ProcessInput(window, camera.Front, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // y al revés porque los valores de la ventana van de arriba a abajo

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

bool checkCollision(const glm::vec3& minA, const glm::vec3& maxA, const glm::vec3& minB, const glm::vec3& maxB) {
    return (minA.x <= maxB.x && maxA.x >= minB.x) &&
        (minA.y <= maxB.y && maxA.y >= minB.y) &&
        (minA.z <= maxB.z && maxA.z >= minB.z);
}

bool resolveCollision(Player& player, const Block* block) {
    glm::vec3 playerMin = player.getMin();
    glm::vec3 playerMax = player.getMax();
    glm::vec3 blockMin = block->getMin();
    glm::vec3 blockMax = block->getMax();

    if (checkCollision(playerMin, playerMax, blockMin, blockMax)) {
        // Corregir la posición del jugador dependiendo de la dirección de la colisión
        if (playerMax.y > blockMin.y && playerMin.y < blockMin.y) {
            // Colisión desde arriba
            player.Position.y = blockMin.y - player.Size.y * 0.5f;
            player.velocityY = 0;  // Detener la caída
            player.isJumping = false;  // Permitir saltar de nuevo
        }
        else if (playerMin.y < blockMax.y && playerMax.y > blockMax.y) {
            // Colisión desde abajo
            player.Position.y = blockMax.y + player.Size.y * 0.5f;
            player.velocityY = 0;  // Detener el ascenso
        }
        else if (playerMax.x > blockMin.x && playerMin.x < blockMin.x) {
            // Colisión desde la izquierda
            player.Position.x = blockMin.x - player.Size.x * 0.5f;
        }
        else if (playerMin.x < blockMax.x && playerMax.x > blockMax.x) {
            // Colisión desde la derecha
            player.Position.x = blockMax.x + player.Size.x * 0.5f;
        }
        else if (playerMax.z > blockMin.z && playerMin.z < blockMin.z) {
            // Colisión desde el frente
            player.Position.z = blockMin.z - player.Size.z * 0.5f;
        }
        else if (playerMin.z < blockMax.z && playerMax.z > blockMax.z) {
            // Colisión desde atrás
            player.Position.z = blockMax.z + player.Size.z * 0.5f;
        }
        return true;
    }
    return false;
}
