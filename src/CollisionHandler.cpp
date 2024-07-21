#include "CollisionHandler.h"
#include <iostream>

bool CollisionHandler::checkCollision(const glm::vec3& minA, const glm::vec3& maxA, const glm::vec3& minB, const glm::vec3& maxB)
{
    bool collisionX = minA.x <= maxB.x && maxA.x >= minB.x;
    bool collisionY = minA.y <= maxB.y && maxA.y >= minB.y;
    bool collisionZ = minA.z <= maxB.z && maxA.z >= minB.z;

    if (collisionX && collisionY && collisionZ) {
        std::cout << "Colisión detectada entre los límites: " << std::endl;
        std::cout << "A: (" << minA.x << ", " << minA.y << ", " << minA.z << ") - (" << maxA.x << ", " << maxA.y << ", " << maxA.z << ")" << std::endl;
        std::cout << "B: (" << minB.x << ", " << minB.y << ", " << minB.z << ") - (" << maxB.x << ", " << maxB.y << ", " << maxB.z << ")" << std::endl;
    }

    return collisionX && collisionY && collisionZ;
}

bool CollisionHandler::resolveCollision(Player& player, const Block* block)
{
    glm::vec3 playerMin = player.getMin();
    glm::vec3 playerMax = player.getMax();
    glm::vec3 blockMin = block->getMin();
    glm::vec3 blockMax = block->getMax();

    if (checkCollision(playerMin, playerMax, blockMin, blockMax))
    {
        glm::vec3 correction = glm::vec3(0.0f);
        glm::vec3 previousPosition = player.Position;

        // Detectar colisión en el eje Y (arriba/abajo)
        if (playerMax.y > blockMin.y && playerMin.y < blockMin.y) {
            // Colisión desde arriba
            correction.y = blockMin.y - playerMax.y - 0.1f; // Añadir margen extra
            player.velocityY = 0;  // Detener la caída

            std::cout << "Colisión en el eje Y desde arriba, corrección: " << correction.y << std::endl;
        }
        else if (playerMin.y < blockMax.y && playerMax.y > blockMax.y) {
            // Colisión desde abajo
            correction.y = blockMax.y - playerMin.y + 0.1f; // Añadir margen extra
            player.isJumping = false;  // Permitir saltar de nuevo
            player.isOnGround = true; // Indicar que el jugador está en el suelo
            player.velocityY = 0;  // Detener el ascenso
            std::cout << "Colisión en el eje Y desde abajo, corrección: " << correction.y << std::endl;
        }

        // Detectar colisión en el eje X (izquierda/derecha)
        if (playerMax.x > blockMin.x && playerMin.x < blockMin.x) {
            // Colisión desde la izquierda
            correction.x = blockMin.x - playerMax.x - 0.1f; // Añadir margen extra
            std::cout << "Colisión en el eje X desde la izquierda, corrección: " << correction.x << std::endl;
        }
        else if (playerMin.x < blockMax.x && playerMax.x > blockMax.x) {
            // Colisión desde la derecha
            correction.x = blockMax.x - playerMin.x + 0.1f; // Añadir margen extra
            std::cout << "Colisión en el eje X desde la derecha, corrección: " << correction.x << std::endl;
        }

        // Detectar colisión en el eje Z (frente/atrás)
        if (playerMax.z > blockMin.z && playerMin.z < blockMin.z) {
            // Colisión desde el frente
            correction.z = blockMin.z - playerMax.z - 0.1f; // Añadir margen extra
            std::cout << "Colisión en el eje Z desde el frente, corrección: " << correction.z << std::endl;
        }
        else if (playerMin.z < blockMax.z && playerMax.z > blockMax.z) {
            // Colisión desde atrás
            correction.z = blockMax.z - playerMin.z + 0.1f; // Añadir margen extra
            std::cout << "Colisión en el eje Z desde atrás, corrección: " << correction.z << std::endl;
        }

        // Aplicar corrección a la posición del jugador
        player.Position += correction;
        std::cout << "Corrección aplicada a la posición del jugador: " << player.Position.x << ", " << player.Position.y << ", " << player.Position.z << std::endl;

        // Verificar si la posición ha cambiado para evitar bucles infinitos
        if (player.Position == previousPosition) {
            std::cout << "Corrección no fue efectiva, ajuste manual de la posición" << std::endl;
            player.Position += glm::vec3(0.1f); // Ajuste manual pequeño
        }

        return true;
    }
    return false;
}
