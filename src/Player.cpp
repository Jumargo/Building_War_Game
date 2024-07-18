#include "Player.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp> // Incluir para usar glm::value_ptr

void Player::ProcessInput(GLFWwindow* window, const glm::vec3& cameraFront, float deltaTime)
{
    const float speed = 2.5f;
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
    if (isJumping)
    {
        Position.y += velocityY * deltaTime;
        velocityY += gravity * deltaTime;
        if (Position.y <= 0.0f) // Suponemos que el suelo está en y = 0
        {
            Position.y = 0.0f;
            isJumping = false;
            velocityY = 0.0f;
        }
    }
}

glm::vec3 Player::getMin() const {
    return Position - Size * 0.5f;
}

glm::vec3 Player::getMax() const {
    return Position + Size * 0.5f;
}
