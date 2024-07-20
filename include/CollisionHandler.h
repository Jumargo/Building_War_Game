#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Player.h"
#include "Chunk.h"

class CollisionHandler
{
public:
    static bool checkCollision(const glm::vec3& minA, const glm::vec3& maxA, const glm::vec3& minB, const glm::vec3& maxB);
    static bool resolveCollision(Player& player, const Block* block);
};
