#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Player
{
public:
    glm::vec3 Position;
    glm::vec3 Size;

    Player(glm::vec3 position, glm::vec3 size)
        : Position(position), Size(size) {}

    void ProcessInput(GLFWwindow* window, const glm::vec3& cameraFront, float deltaTime);
};
