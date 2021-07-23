#include <catch2/catch.hpp>
#include <run_game_app.h>

using run_game::Character;
using run_game::Map;
using run_game::Obstacle;

TEST_CASE("Jump") {
    Character character = Character(glm::vec2(160,358), Character::CIRCLE, ci::Color("gray"));
    Map map = Map(character);
    
    SECTION("Motion of jump going up and down") {
        REQUIRE(character.GetPosition() == glm::vec2(160, 358));
        map.JumpCharacter();
        map.AdvanceOneFrame();
        REQUIRE(map.GetCharacter().GetPosition() == glm::vec2(160, 351)); // Moves 7 units at a time
        for (int i = 1; i < 15; ++i) {
            map.AdvanceOneFrame(); // Ascent
        }
        REQUIRE(map.GetCharacter().GetPosition() == glm::vec2(160, 253)); // Peak of the jump
        for (int i = 0; i < 16; ++i) {
            map.AdvanceOneFrame(); // Descent
        }
        REQUIRE(map.GetCharacter().GetPosition() == glm::vec2(160, 358)); // Back at resting position
    }
}

TEST_CASE("Remove offscreen obstacles") {
    
    Character character_ = Character(glm::vec2(400,400), Character::CIRCLE, ci::Color("gray"));
    Map map = Map(character_);
    SECTION("Removing when there are no obstacles, doesn't throw an exception") {
        REQUIRE_NOTHROW(map.RemoveOffscreenObstacles()); 
    }
    SECTION("Successfully removes offscreen obstacle") {
        map.AdvanceOneFrame();
        REQUIRE(map.GetObstacles().size() == 1);
        for (int i = 0; i < 80; i++) {
            map.AdvanceOneFrame();
        }
        REQUIRE(map.GetObstacles().size() == 2); 
        for (int i = 0; i < 20; i++) {
            map.AdvanceOneFrame();
        }
        map.RemoveOffscreenObstacles();
        REQUIRE(map.GetObstacles().size() == 1); // Front most obstacle got removed after 100 frames
    }
}


TEST_CASE("Generate obstacles") {
    Character character = Character(glm::vec2(400,400), Character::CIRCLE, ci::Color("gray"));
    Map map = Map(character);
    SECTION("Obstacles always have valid y position") {
        // Sample size of 1000 frames
        for (int i = 0; i < 1000; ++i) {
            map.AdvanceOneFrame();
            std::vector<run_game::Obstacle> obstacles = map.GetObstacles();
            // Checks that each obstacles height is always one of the three preset ones
            for (const run_game::Obstacle& obstacle : obstacles) {
                float y = obstacle.GetPosition().y;
                bool check = y == 361 || y == 347 || y == 300;
                REQUIRE(check);
            }
        }
    }
    
    SECTION("Obstacles speed up after x amount of frames") {
        map.AdvanceOneFrame();
        REQUIRE(map.GetObstacleVelocity() == glm::vec2(-6,0));
        for (int i = 0; i < 100; ++i) {
            map.AdvanceOneFrame();
        }
        // After 100 frames the speed increases by .5
        REQUIRE(map.GetObstacleVelocity() == glm::vec2(-6.5, 0));
        for (int i = 0; i < 5000; ++i) {
            map.AdvanceOneFrame();
        }
        // Velocity is capped at -20
        REQUIRE(map.GetObstacleVelocity() == glm::vec2(-20, 0));
    }
}

TEST_CASE("Test Square Character collision") {
    // 17 and 20 are the lengths of the obstacle and character respectively, so these values are added to the position
    // for a perfect collision
    SECTION("Detect x collision") {
        Character character = Character(glm::vec2(160,358), Character::SQUARE, ci::Color("gray"));
        Map map = Map(character);
        Obstacle obstacle = Obstacle(glm::vec2(0,0), glm::vec2(160 + 17 + 20,358), ci::Color("black"));
        REQUIRE(map.IsCollision(obstacle));
    }
    SECTION("Detect y collision") {
        Character character = Character(glm::vec2(160,358), Character::SQUARE, ci::Color("gray"));
        Map map = Map(character);
        Obstacle obstacle = Obstacle(glm::vec2(0,0), glm::vec2(160,358 - 17 - 20), ci::Color("black"));
        REQUIRE(map.IsCollision(obstacle));
    }
    SECTION("Detects corner collision") {
        Character character = Character(glm::vec2(160,358), Character::SQUARE, ci::Color("gray"));
        Map map = Map(character);
        Obstacle obstacle = Obstacle(glm::vec2(0,0), glm::vec2(160 + 20 + 17,358 - 20 - 17), ci::Color("black"));
        REQUIRE(map.IsCollision(obstacle));
    }
    SECTION("Does not detect collision") {
        Character character = Character(glm::vec2(160,358), Character::SQUARE, ci::Color("gray"));
        Map map = Map(character);
        // 1 unit off from collision
        Obstacle obstacle = Obstacle(glm::vec2(0,0), glm::vec2(160,358 - 17 - 20 - 1), ci::Color("black"));
        REQUIRE(!map.IsCollision(obstacle));
    }
}

TEST_CASE("Test Circle Character collision") {
    SECTION("Detect x collision") {
        Character character = Character(glm::vec2(160,358), Character::CIRCLE, ci::Color("gray"));
        Map map = Map(character);
        Obstacle obstacle = Obstacle(glm::vec2(0,0), glm::vec2(160 + 17 + 20,358), ci::Color("black"));
        REQUIRE(map.IsCollision(obstacle));
    }
    SECTION("Detect y collision") {
        Character character = Character(glm::vec2(160,358), Character::CIRCLE, ci::Color("gray"));
        Map map = Map(character);
        Obstacle obstacle = Obstacle(glm::vec2(0,0), glm::vec2(160,358 - 17 - 20), ci::Color("black"));
        REQUIRE(map.IsCollision(obstacle));
    }
    SECTION("Does not detect the corner collision for the circle") {
        Character character = Character(glm::vec2(160,358), Character::CIRCLE, ci::Color("gray"));
        Map map = Map(character);
        Obstacle obstacle = Obstacle(glm::vec2(0,0), glm::vec2(160 + 20 + 17,358 - 20 - 17), ci::Color("black"));
        REQUIRE(!map.IsCollision(obstacle));
    }
    SECTION("Does not detect collision") {
        Character character = Character(glm::vec2(160,358), Character::CIRCLE, ci::Color("gray"));
        Map map = Map(character);
        // 1 unit off from collision
        Obstacle obstacle = Obstacle(glm::vec2(0,0), glm::vec2(160,358 - 17 - 20 - 1), ci::Color("black"));
        REQUIRE(!map.IsCollision(obstacle));
    }
}

TEST_CASE("Test Triangle Character collision") {
    SECTION("Detect x base collision") {
        Character character = Character(glm::vec2(160,358), Character::TRIANGLE, ci::Color("gray"));
        Map map = Map(character);
        Obstacle obstacle = Obstacle(glm::vec2(0,0), glm::vec2(160 + 17 + 20,358), ci::Color("black"));
        REQUIRE(map.IsCollision(obstacle));
    }
    SECTION("Detect y point of triangle collision") {
        Character character = Character(glm::vec2(160, 358), Character::TRIANGLE, ci::Color("gray"));
        Map map = Map(character);
        Obstacle obstacle = Obstacle(glm::vec2(0,0), glm::vec2(160,358 - 17 - 20), ci::Color("black"));
        REQUIRE(map.IsCollision(obstacle));
    }
    SECTION("Detect collision midway through triangle height at slope") {
        Character character = Character(glm::vec2(160, 358), Character::TRIANGLE, ci::Color("gray"));
        Map map = Map(character);
        Obstacle obstacle = Obstacle(glm::vec2(0,0), glm::vec2(160 + 17 + 20,358 - 20 - 17), ci::Color("black"));
        REQUIRE(map.IsCollision(obstacle));
    }
    SECTION("Does not detect collision") {
        // One off from collision
        Character character = Character(glm::vec2(160, 358), Character::TRIANGLE, ci::Color("gray"));
        Map map = Map(character);
        Obstacle obstacle = Obstacle(glm::vec2(0,0), glm::vec2(160 + 17 + 20 + 1,358 - 20 - 17 - 1), ci::Color("black"));
        REQUIRE(!map.IsCollision(obstacle));
    }
}