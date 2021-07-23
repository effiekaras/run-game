#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "map.h"
#include "cinder/gl/gl.h"
#include "menu.h"

namespace run_game {
class RunGameApp : public ci::app::App {
    public:
      /**
       * Constructor for the application window
       */
      RunGameApp();
      /**
       * Describes current game state.
       */
      enum State {
          MENU,
          INGAME,
          GAMEOVER
      };
      /**
       * Draws the menu and game shapes
       */
      void draw() override;
      /**
       * Updates the game loop
       */
      void update() override;
      /**
       * Construct the behavior for the keyboard keys in the application
       * @param event 
       */
      void keyDown(ci::app::KeyEvent event) override;
      const int kWindowXSize = 800;
      const int kWindowYSize = 500;
      const ci::Color kBackgroundColor_ = ci::Color("black");
      const ci::Color kGameOverColor_ = ci::Color("red");

private:
      Character character_ = Character(glm::vec2(400,400), Character::CIRCLE, ci::Color("gray"));
      Map map_;
      Menu menu_;
      State state = MENU;
      glm::vec2 resting_pos_ = glm::vec2(160,358);
      const ci::Font kSmallFont = ci::Font("Arial", 25.0f);
      const ci::Font kMedFont = ci::Font("Arial", 40.0f);
      const ci::Font kBigFont = ci::Font("Arial", 72.0f);
      std::string hi_score_ = "HIGH SCORE: ";
      std::string score_ = "SCORE: ";
      std::string game_over_ = "GAME OVER";
      std::string play_again_ = "Press Enter to play again!";
      std::string back_to_menu_ = "Select Backspace to change your character!";
      size_t high_score_ = 0;
};
} // namespace run_game