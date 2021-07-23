#pragma once
#include <glm/vec2.hpp>
#include <cinder/Color.h>
#include "cinder/gl/gl.h"

namespace run_game {
    class Obstacle {
    public:
        /**
         * Creates a new obstacle in the map for the player to avoid 
         * @param velocity directional speed of the obstacle moving on the map
         * @param position the current position of the obstacle
         * @param color the color of the obstacle
         */
        Obstacle(const glm::vec2 &velocity, const glm::vec2 &position, const cinder::Color &color);
        /**
         * Draws a specific Obstacle object.
         */
        void Draw() const;
        /**
         * Updates the new position using the current velocity.
         */
        void UpdatePosition();
        const glm::vec2& GetPosition() const;
        float GetLength() const;

    private:
        glm::vec2 velocity_;
        glm::vec2 position_;
        ci::Color color_;
        float length_ = 17;
    };
}