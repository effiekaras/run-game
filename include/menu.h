#pragma once
#include <cinder/Color.h>
#include <cinder/Font.h>
#include "character.h"

namespace run_game {
    class Menu {

    public:
        /**
         * Displays the graphics for the menu
         */
        void Display();
        const std::vector<ci::Color>& GetColorOptions() const;
        /**
         * Setter for the character
         * @param current_character the character to update with 
         */
        void UpdateCurrentCharacter(const Character& current_character);
        
    private:
        /**
         * Draws the shape options the player can select for its character
         */
        void DrawShapeOptions();
        /**
         * Draws the color icons the player can select for its character
         */
        void DrawColorOptions();
        /**
         * Draws all the text labels for the menu
         */
        void DrawText();

        Character character_ = Character(glm::vec2(400,400), Character::CIRCLE, ci::Color("gray"));
        float length_ = 30;
        float color_length_ = 20;
        ci::Color icon_color_ = ci::Color("white");
        ci::Color icon_label_ = ci::Color("red");
        ci::Color color_label_ = ci::Color("black");
        const ci::Font kFont = ci::Font("Arial", 32.0f);
        const ci::Font kSmallFont = ci::Font("Arial", 25.0f);
        glm::vec2 text_offset_ = glm::vec2(10, 10);
        std::vector<ci::Color> color_options_ = {ci::Color("red"), ci::Color("darkorange"), ci::Color("gold"), ci::Color("lime"), ci::Color("lightskyblue"), ci::Color("mediumpurple")};
        // Menu strings
        std::string shape_message_ = "Use your keyboard (1-3) to select your character's shape: ";
        std::string color_message_ = "Use your keyboard (4-9) to select your character's color: ";
        std::string char_message_ = "Your current character: ";
        std::string begin_message_ = "Select the Enter key to begin!";
    };
}

