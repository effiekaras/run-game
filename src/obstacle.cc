#include "obstacle.h"

namespace run_game {
    Obstacle::Obstacle(const glm::vec2 &velocity, const glm::vec2 &position, const cinder::Color &color) : 
    velocity_(velocity), position_(position), color_(color) {}

    void Obstacle::Draw() const {
        ci::gl::color(color_);
        ci::gl::drawSolidRect(ci::Rectf(position_ - glm::vec2(length_, length_), position_ + glm::vec2(length_, length_)));
    }

    const glm::vec2 &Obstacle::GetPosition() const {
        return position_;
    }

    void Obstacle::UpdatePosition() {
        position_ += velocity_;
    }

    float Obstacle::GetLength() const {
        return length_;
    }
}