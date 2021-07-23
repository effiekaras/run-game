#pragma once
#include <cinder/Color.h>
#include "cinder/gl/gl.h"

namespace run_game {
    class Character {
    public:
        /**
         * Three options for the shape of the character.
         */
        enum Shape {
            CIRCLE,
            SQUARE,
            TRIANGLE
        };
        /**
         * The character model for the game
         * @param position the position of the character
         * @param shape_index the index correlating to the characters shape
         * @param color the color of the character
         */
        Character(const glm::vec2 &position, Shape shape, const ci::Color &color);
        /**
         * Draws the character in the window
         */
        void Draw() const;
        float GetLength() const;
        const glm::vec2& GetPosition() const;
        void SetPosition(const glm::vec2& position);
        void SetColor(const ci::Color& color);
        void SetShape(Shape shape);
        Shape GetShape() const;

    private:
        glm::vec2 position_;
        Shape shape_;
        ci::Color color_;
        float length_ = 20;
    };
}