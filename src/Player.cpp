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
}
