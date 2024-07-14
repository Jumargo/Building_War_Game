#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Player
{
public:
    glm::vec3 Position;
    glm::vec3 Size;
    bool isJumping;
    float velocityY;
    const float gravity = -9.81f;
    const float jumpStrength = 5.0f;

    Player(glm::vec3 position, glm::vec3 size)
        : Position(position), Size(size), isJumping(false), velocityY(0.0f) {}

    void ProcessInput(GLFWwindow* window, const glm::vec3& cameraFront, float deltaTime);
    void Update(float deltaTime);
};
