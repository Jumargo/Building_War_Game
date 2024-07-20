#include "Player.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp> // Incluir para usar glm::value_ptr
#include <iostream>

void Player::ProcessInput(GLFWwindow* window, const glm::vec3& cameraFront, float deltaTime)
{
    const float speed = 4.5f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Position += glm::vec3(cameraFront.x, 0.0f, cameraFront.z) * deltaTime * speed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Position -= glm::vec3(cameraFront.x, 0.0f, cameraFront.z) * deltaTime * speed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Position -= glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * deltaTime * speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Position += glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * deltaTime * speed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !isJumping)
    {
        isJumping = true;
        velocityY = jumpStrength;
    }
}

void Player::Update(float deltaTime)
{
    // Resetear isOnGround al inicio de cada actualización
    isOnGround = false;

    // Aplicar gravedad solo si el jugador no está en el suelo
    if (!isOnGround) {
        velocityY += gravity * deltaTime;
    } else {
        velocityY = 0;
    }

    // Aplicar movimiento en el eje Y
    Position.y += velocityY * deltaTime;

    // Log de la posición y velocidad
    std::cout << "Actualización del jugador - Posición: (" << Position.x << ", " << Position.y << ", " << Position.z << "), Velocidad Y: " << velocityY << std::endl;
}

glm::vec3 Player::getMin() const {
    return Position - Size * 0.5f;
}

glm::vec3 Player::getMax() const {
    return Position + Size * 0.5f;
}
