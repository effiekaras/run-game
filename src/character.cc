#include "character.h"

namespace run_game {
    Character::Character(const glm::vec2 &position, Shape shape, const cinder::Color &color)
            : position_(position), shape_(shape), color_(color) {}

    void Character::Draw() const {
        ci::gl::color(color_);
        if (shape_ == Shape::CIRCLE) {
            // Draw Circle
            ci::gl::drawSolidCircle(position_, length_);
        } else if (shape_ == Shape::SQUARE) {
            // Draw Square
             ci::gl::drawSolidRect(ci::Rectf(position_ - glm::vec2(length_, length_), position_ + glm::vec2(length_, length_)));
        } else if (shape_ == Shape::TRIANGLE) {
            // Draw Triangle
            ci::gl::drawSolidTriangle(position_ - glm::vec2(0, length_),
                          position_ - glm::vec2(length_, -length_), position_ + glm::vec2(length_, length_));
        }
    }

    float Character::GetLength() const {
        return length_;
    }

    void Character::SetPosition(const glm::vec2 &position) {
        position_ = position;
    }

    void Character::SetColor(const cinder::Color &color) {
        color_ = color;
    }

    void Character::SetShape(Shape shape) {
        shape_ = shape;
    }
    
    const glm::vec2 &Character::GetPosition() const {
        return position_;
    }
    
    Character::Shape Character::GetShape() const {
        return shape_;
    }
}