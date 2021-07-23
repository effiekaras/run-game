#include <cinder/gl/gl.h>
#include "menu.h"

namespace run_game {
    void Menu::Display() {
        ci::gl::color(icon_color_);
        DrawShapeOptions();
        DrawColorOptions();
        DrawText();
        character_.Draw();
    }

    void Menu::DrawShapeOptions() {
        // Draw Circle
        glm::vec2 position_crc = glm::vec2(150, 170);
        ci::gl::drawSolidCircle(position_crc, length_);
        ci::gl::drawString("1", position_crc - text_offset_, icon_label_, kFont);
        // Draw Square
        glm::vec2 position_sq = glm::vec2(400, 170);
        ci::gl::drawSolidRect(ci::Rectf(position_sq - glm::vec2(length_, length_), position_sq + glm::vec2(length_, length_)));
        ci::gl::drawString("2", position_sq - text_offset_, icon_label_, kFont);
        // Draw Triangle
        glm::vec2 position_tri = glm::vec2(650, 170);
        ci::gl::drawSolidTriangle(position_tri - glm::vec2(0, length_),
                                  position_tri - glm::vec2(length_, -length_), position_tri + glm::vec2(length_, length_));
        ci::gl::drawString("3", position_tri - text_offset_, icon_label_, kFont);
    }

    void Menu::DrawColorOptions() {
        if (color_options_.size() > 6) {
            throw std::invalid_argument("Cannot have more than 6 color options");
        }
        glm::vec2 position = glm::vec2(110, 300);
        size_t string_label = 4;
        for (size_t i = 0; i < color_options_.size(); i++) {
            ci::gl::color(color_options_[i]);
            ci::gl::drawSolidCircle(position, color_length_);
            ci::gl::drawString(std::to_string(string_label), position - text_offset_,
                               color_label_, kFont);
            position += glm::vec2(110, 0);
            ++string_label;
        }
    }

    void Menu::DrawText() {
        ci::gl::drawStringCentered(shape_message_, 
                                   glm::vec2(400, 90), icon_color_, kFont);

        ci::gl::drawStringCentered(color_message_,
                                   glm::vec2(400, 220), icon_color_, kFont);

        ci::gl::drawStringCentered(char_message_, glm::vec2(400, 350),
                                   icon_color_, kSmallFont);

        ci::gl::drawStringCentered(begin_message_, glm::vec2(400, 450),
                                   icon_label_, kFont);
    }

    const std::vector<ci::Color> &Menu::GetColorOptions() const {
        return color_options_;
    }

    void Menu::UpdateCurrentCharacter(const Character &current_character) {
        character_ = current_character;
    }
} // namespace run_game