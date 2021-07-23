#include <character.h>
#include "run_game_app.h"

namespace run_game {
    RunGameApp::RunGameApp() : map_(Map(character_)), menu_(Menu()) {
        ci::app::setWindowSize(kWindowXSize, kWindowYSize);
    }
    
    void RunGameApp::draw() {
        ci::gl::clear();
        ci::Color background_color(kBackgroundColor_);
        ci::gl::clear(background_color);
        if (state == State::MENU) {
            map_.UpdateCharacterPosition(glm::vec2(400,400));
            menu_.UpdateCurrentCharacter(map_.GetCharacter());
            menu_.Display();
        } else if (state == State::INGAME) {
            map_.Display();
            
            // Draw score
            size_t current_score = map_.GetScore();
            
            if (current_score > high_score_) {
                high_score_ = current_score;
            }
            ci::gl::drawStringCentered(hi_score_ + std::to_string(high_score_) + "  " + std::to_string(current_score),
                                       glm::vec2(580, 110), kBackgroundColor_, kSmallFont);
        } else if (state == State::GAMEOVER) {
            map_.Display();
            // Draw Game Over message
            ci::gl::drawStringCentered(game_over_, glm::vec2(400, 140),
                                       kGameOverColor_, kBigFont);
            // Ask player to start again
            ci::gl::drawStringCentered(play_again_, glm::vec2(400, 240), kBackgroundColor_, kSmallFont);
            // Score message
            ci::gl::drawStringCentered(score_ + std::to_string(map_.GetScore()),
                                       glm::vec2(400, 200), kBackgroundColor_, kMedFont);
            // Go back to menu
            ci::gl::drawStringCentered("or", glm::vec2(400, 260), kBackgroundColor_, kSmallFont);
            ci::gl::drawStringCentered(back_to_menu_, glm::vec2(400, 280), kBackgroundColor_, kSmallFont);
        }
    }

    void RunGameApp::update() {
        if (map_.IsGameOver()) {
            state = State::GAMEOVER;
        }
        if (state == State::INGAME) {
            map_.AdvanceOneFrame();
            map_.RemoveOffscreenObstacles();
        }
    }

    void RunGameApp::keyDown(ci::app::KeyEvent event) {
        std::vector<ci::Color> colors = menu_.GetColorOptions();
        switch (event.getCode()) {
            case ci::app::KeyEvent::KEY_1:
                map_.UpdateCharacterShape(Character::CIRCLE);
                break;
            case ci::app::KeyEvent::KEY_2:
                map_.UpdateCharacterShape(Character::SQUARE); 
                break;
            case ci::app::KeyEvent::KEY_3:
                map_.UpdateCharacterShape(Character::TRIANGLE);
                break;
            case ci::app::KeyEvent::KEY_4:
                map_.UpdateCharacterColor(colors[0]);
                break;
            case ci::app::KeyEvent::KEY_5:
                map_.UpdateCharacterColor(colors[1]);
                break;
            case ci::app::KeyEvent::KEY_6:
                map_.UpdateCharacterColor(colors[2]);
                break;
            case ci::app::KeyEvent::KEY_7:
                map_.UpdateCharacterColor(colors[3]);
                break;
            case ci::app::KeyEvent::KEY_8:
                map_.UpdateCharacterColor(colors[4]);
                break;
            case ci::app::KeyEvent::KEY_9:
                map_.UpdateCharacterColor(colors[5]);
                break;
            case ci::app::KeyEvent::KEY_SPACE:
                // Only jumps when the character is on the floor
                if (map_.GetCharacter().GetPosition().y == resting_pos_.y) {
                    map_.JumpCharacter();
                }
                break;
            case ci::app::KeyEvent::KEY_RETURN:
                if (state == State::MENU) {
                    map_.UpdateCharacterPosition(resting_pos_);
                    state = State::INGAME;
                }
                if (state == State::GAMEOVER) {
                    map_.Restart();
                    state = State::INGAME;
                }
                break;
            case ci::app::KeyEvent::KEY_BACKSPACE:
                if (state == State::GAMEOVER) {
                    map_.Restart();
                    state = State::MENU;
                }
                break;
        }
    }
}