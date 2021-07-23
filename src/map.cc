#include <character.h>
#include "map.h"

using glm::vec2;

namespace run_game {
    Map::Map(const Character& character) : character_(character) {
        character_.SetPosition(resting_pos);
    }
    
    void Map::AdvanceOneFrame() {
        vec2 pos = character_.GetPosition();
        // Jump logic
        if (is_jumping && pos.y >= jump_height) {
            UpdateCharacterPosition(pos + vec2(0, -7));
        } else if (!is_jumping && pos.y < resting_pos.y) {
            UpdateCharacterPosition(pos + vec2(0, 7));
        }
        if (pos.y <= jump_height) {
            is_jumping = false;
        }
        
        // Spawns a new obstacle every spawn_rate_ frames
        if (spawn_counter_ % spawn_rate_ == 0) {
            GenerateObstacles();
            spawn_counter_ = 0;
        }
        
        // Updates the position of each obstacle using its velocity
        for (Obstacle& obstacle : obstacles_) {
            obstacle.UpdatePosition();
        }
        ++spawn_counter_;
        
        ++score_;
        // Every 100 points, increase the objects speed and spawn rate
        if (score_ % 100 == 0) {
            //  Sets -20 to the threshold for fastest obstacle speed
            if (obstacle_vel.x > fastest_speed_) {
                obstacle_vel -= glm::vec2(.5, 0);
            }
            // Sets 50 to the threshold for fastest spawn rate (so game doesn't become unplayable)
            if (spawn_rate_ > lowest_spawnrate_) {
                spawn_rate_ -= 2;
            }
        }
        if (!obstacles_.empty()) {
            is_game_over_ = IsCollision(obstacles_.at(0));
        }
    }

    void Map::Display() {
        // Generate map box
        ci::gl::color(kBackgroundColor_);
        ci::gl::drawSolidRect(ci::Rectf(vec2(kOffset_, kOffset_),
                                          vec2(kOffset_ + x_dim_, kOffset_ + y_dim_)));
        
        // Generate floor
        ci::gl::color(kFeatureColor_);
        ci::gl::lineWidth(kFloorWidth_);
        ci::gl::drawLine(vec2(kOffset_, kFloorOffset_),
                         vec2(kOffset_ + x_dim_, kFloorOffset_));

        // Draw Character
        character_.Draw();
        
        // Draw Obstacles
        for (const Obstacle& obstacle : obstacles_) {
            obstacle.Draw();
        }
    }

    void Map::UpdateCharacterPosition(const glm::vec2 &position) {
        character_.SetPosition(position);
    }

    void Map::UpdateCharacterColor(const cinder::Color &color) {
        character_.SetColor(color);
    }

    void Map::UpdateCharacterShape(Character::Shape shape) {
        character_.SetShape(shape);
    }
    
    const Character& Map::GetCharacter() const {
        return character_;
    }

    void Map::JumpCharacter() {
        is_jumping = true;
    }
    
    void Map::RemoveOffscreenObstacles() {
        if (!obstacles_.empty()) {
            Obstacle first = obstacles_.at(0);
            if (first.GetPosition().x < (float) kOffset_ + first.GetLength()) {
                obstacles_.erase(obstacles_.begin());
            }
        }
    }

    void Map::GenerateObstacles() {
        int range = obstacle_heights_.size();
        int i = rand() % range;
        obstacles_.push_back(Obstacle(obstacle_vel, obstacle_heights_[i], obstacle_color_));
    }
    
    const std::vector<Obstacle>& Map::GetObstacles() const {
        return obstacles_;
    }

    size_t Map::GetScore() const {
        return score_;
    }

    const vec2 & Map::GetObstacleVelocity() const {
        return obstacle_vel;
    }
    
    bool Map::IsCollision(const Obstacle& obstacle) {
        Character::Shape shape = character_.GetShape();
        if (shape == Character::SQUARE) {
            return IsSquareOverlap(obstacle);
        } else if (shape == Character::CIRCLE) {
            return IsCircleOverlap(obstacle);
        } else if (shape == Character::TRIANGLE) {
            return IsTriangleOverlap(obstacle);
        }
        return false;
    }
    
    bool Map::IsSquareOverlap(const Obstacle& obstacle) {
        float char_length = character_.GetLength();
        glm::vec2 char_position = character_.GetPosition();
        float char_x  = char_position.x;
        float char_y = char_position.y;
        
        glm::vec2 obs_position = obstacle.GetPosition();
        float obs_length = obstacle.GetLength();
        float obs_x = obs_position.x;
        float obs_y = obs_position.y;
       
        float char_right_edge_x = char_x + char_length;
        float obs_left_edge_x = obs_x - obs_length;
        float char_left_edge_x = char_x - char_length;
        float obs_right_edge_x = obs_x + obs_length;
        // If character is on either side of the obstacle, no collision occurring
        if (char_right_edge_x < obs_left_edge_x || obs_right_edge_x < char_left_edge_x) {
            return false;
        }
        float char_ceiling = char_y - char_length;
        float char_floor = char_y + char_length;
        float obs_ceiling = obs_y - obs_length;
        float obs_floor = obs_y + obs_length;
        // If character is below or above the obstacle, no collision occurring
        if (char_floor < obs_ceiling || obs_floor < char_ceiling) {
            return false;
        }
        return true;
    }
    
    bool Map::IsCircleOverlap(const Obstacle& obstacle) {
        glm::vec2 character_pos = character_.GetPosition();
        glm::vec2 obstacle_pos = obstacle.GetPosition();
        float radius = character_.GetLength();
        float obs_length = obstacle.GetLength();
        float circle_distance_x = abs(character_pos.x - obstacle_pos.x);
        float circle_distance_y = abs(character_pos.y - obstacle_pos.y);
        
        //  Code below derived from: 
        // https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
        if (circle_distance_x > (obs_length + radius) || circle_distance_y > (obs_length + radius)) {
            return false;
        }
        if (circle_distance_x <= obs_length || circle_distance_y <= obs_length) {
            return true;
        }
        float corner_distance = pow(circle_distance_x - obs_length, 2) + pow(circle_distance_y - obs_length, 2);
        return corner_distance <= pow(radius, 2);
    }
    
    bool Map::IsTriangleOverlap(const Obstacle &obstacle) {
        float char_length = character_.GetLength();
        glm::vec2 char_position = character_.GetPosition();
        float char_x  = char_position.x;
        float char_y = char_position.y;

        glm::vec2 obs_position = obstacle.GetPosition();
        float obs_length = obstacle.GetLength();
        float obs_x = obs_position.x;
        float obs_y = obs_position.y;

        float char_ceiling = char_y - char_length;
        float char_floor = char_y + char_length;
        float obs_ceiling = obs_y - obs_length;
        float obs_floor = obs_y + obs_length;
        if (char_floor < obs_ceiling || obs_floor < char_ceiling ) {
            return false;
        }

        size_t count = 0;
        float obs_left_edge_x = obs_x - obs_length;
        float obs_right_edge_x = obs_x + obs_length;
        for (size_t y = 1; y <= char_length*2; ++y) {
            // Calculates the width of the triangle at every height of the triangle
            float mid_width_triangle = (float) y / 2;
            float char_right_edge_x = char_x + mid_width_triangle;
            float char_left_edge_x = char_x - mid_width_triangle;
            if (char_right_edge_x < obs_left_edge_x || obs_right_edge_x < char_left_edge_x) {
                count++;
            }
        }
        // Each unit of height passes the test, where the edge of the triangle is on the non-collision side of the obstacle
        if (count == char_length*2) {
            return false;
        }
        
        return true;
    }
    
    bool Map::IsGameOver() const {
        return is_game_over_;
    }
    
    void Map::Restart() {
        character_.SetPosition(resting_pos);
        score_ = 0;
        obstacles_.clear();
        spawn_rate_ = 70;
        obstacle_vel = glm::vec2(-6,0);
        is_game_over_ = false;
        spawn_counter_ = 0;
    }
} // namespace run_game