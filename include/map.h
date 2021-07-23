#pragma once
#include <cinder/Color.h>
#include "cinder/gl/gl.h"
#include "character.h"
#include "obstacle.h"

namespace run_game {
    class Map {
    public:
    /**
     * Creates a map that has a character
     * @param character the character model
     */
    explicit Map(const Character& character);
    /**
     * Advances one frame in the loop for the game
     */
    void AdvanceOneFrame();
    /**
     * Displays the current state of the game of the map and the character
     */
    void Display();
    /**
     * Updates the character's position stored in the map.
     * @param position the new position
     */
    void UpdateCharacterPosition(const glm::vec2 &position);
    /**
     * Updates the character's color stored in the map.
     * @param color the new color
     */
    void UpdateCharacterColor(const cinder::Color& color);
    /**
     * Updates the character's shape stored in the map
     * @param shape the new shape
     */
    void UpdateCharacterShape(Character::Shape shape);
    /**
     * Initiates the jumping ability.
     */
    void JumpCharacter();
    /**
     * Spawns a new obstacle in the map, using one of three possible height presets and the 
     * current speed of the obstacles using the game progress.
     */
    void GenerateObstacles();
    /**
     * Deletes the obstacle from the stored obstacles once it hits the back end of the game window.
     */
    void RemoveOffscreenObstacles();
    /**
     * Determines whether or not the character is colliding with an obstacle
     * @param obstacle The obstacle to check a collision with
     * @return True if a collision is occurring, false otherwise
     */
    bool IsCollision(const Obstacle &obstacle);
    /**
     * Restarts the game to default settings so user can play again.
     */
    void Restart();
    /**
     * Returns the current status of the game
     * @return True if the game is over, false otherwise
     */
    bool IsGameOver() const;
    const std::vector<Obstacle> &GetObstacles() const;
    const Character &GetCharacter() const;
    size_t GetScore() const;
    const glm::vec2 & GetObstacleVelocity() const;


    private:
    // Collision overlap helper functions
    /**
     * Determines whether or not the square shaped character is overlapping with an obstacle
     * @param obstacle The obstacle to check the collision with
     * @return True if an overlap/collision is occurring, false otherwise
     */
    bool IsSquareOverlap(const Obstacle &obstacle);
    /**
     * Determines whether or not the circle shaped character is overlapping with an obstacle
     * @param obstacle The obstacle to check the collision with
     * @return True if an overlap/collision is occurring, false otherwise
     */
    bool IsCircleOverlap(const Obstacle &obstacle);
    /**
     * Determines whether or not the triangle shaped character is overlapping with an obstacle
     * @param obstacle The obstacle to check the collision with
     * @return True if an overlap/collision is occurring, false otherwise
     */
    bool IsTriangleOverlap(const Obstacle &obstacle);
        
    // Window/Map details
    const ci::Color kBackgroundColor_ = ci::Color("white");
    const ci::Color kFeatureColor_ = ci::Color("dimgray");
    const int kFloorOffset_ = 380;
    const float kFloorWidth_ = 4;
    const int kOffset_ = 100;
    const size_t x_dim_ = 600;
    const size_t y_dim_ = 300;
    // Character details
    const float kCharacterOffset = 60;
    Character character_ = Character(glm::vec2(160,358), Character::CIRCLE, ci::Color("gray"));
    float length_ = character_.GetLength();
    glm::vec2 resting_pos = glm::vec2((float) kOffset_ + kCharacterOffset, (float) kFloorOffset_ - length_ - kFloorWidth_ / 2);
    bool is_jumping = false;
    float jump_height = resting_pos.y - 100;
    // Obstacle details
    std::vector<Obstacle> obstacles_;
    std::vector<glm::vec2> obstacle_heights_ = {glm::vec2(700-length_, 361), glm::vec2(700-length_, 347), glm::vec2(700-length_, 300)};
    size_t spawn_rate_ = 70;
    glm::vec2 obstacle_vel = glm::vec2(-6,0);
    ci::Color obstacle_color_ = ci::Color("gray");
    // Score/Speed/Rate details
    int spawn_counter_ = 0;
    size_t score_ = 0;
    float fastest_speed_ = -20;
    size_t lowest_spawnrate_ = 40;
    bool is_game_over_ = false;
    };
} // namespace run_game