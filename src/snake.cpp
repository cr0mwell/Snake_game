#include <limits>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "snake.h"


void Snake::Update() {
    SDL_Point prev_cell{
        static_cast<int>(head_x),
        static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
    UpdateHead();
    SDL_Point current_cell{
        static_cast<int>(head_x),
        static_cast<int>(head_y)};  // Capture the head's cell after updating.

    // Update all of the body vector items if the snake head has moved to a new
    // cell.
    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
        UpdateBody(current_cell, prev_cell);
    }
}

void Snake::UpdateHead() {
    switch (direction) {
    case Direction::kUp:
        head_y -= speed;
        break;

    case Direction::kDown:
        head_y += speed;
        break;

    case Direction::kLeft:
        head_x -= speed;
        break;

    case Direction::kRight:
        head_x += speed;
        break;
    }

    // Wrap the Snake around to the beginning if going off of the screen.
    head_x = fmod(head_x + grid_width, grid_width);
    head_y = fmod(head_y + grid_height, grid_height);
}

float SnakeBot::GetDistance(float x, float y) {
    return std::sqrt(std::pow((x - food.x), 2) + std::pow((y - food.y), 2));
}

void SnakeBot::UpdateHead() {
    std::vector<std::pair<Snake::Direction, float>> new_distances;
    
    // Forbidding the bot to move to the neighbour cell if it belongs to its body
    int x = static_cast<int>(head_x), y = static_cast<int>(head_y);
    if(static_cast<int>(head_y-speed) != y && this->SnakeCell(head_x, head_y-speed))
        new_distances.push_back(std::make_pair(Direction::kUp, std::numeric_limits<float>::max()));
    else
        new_distances.push_back(std::make_pair(Direction::kUp, GetDistance(head_x, head_y-speed)));
    if(static_cast<int>(head_y+speed) != y && this->SnakeCell(head_x, head_y+speed))
        new_distances.push_back(std::make_pair(Direction::kDown, std::numeric_limits<float>::max()));
    else
        new_distances.push_back(std::make_pair(Direction::kDown, GetDistance(head_x, head_y+speed)));
    if(static_cast<int>(head_x-speed) != x && this->SnakeCell(head_x-speed, head_y))
        new_distances.push_back(std::make_pair(Direction::kLeft, std::numeric_limits<float>::max()));
    else
        new_distances.push_back(std::make_pair(Direction::kLeft, GetDistance(head_x-speed, head_y)));
    if(static_cast<int>(head_x+speed) != x && this->SnakeCell(head_x+speed, head_y))
        new_distances.push_back(std::make_pair(Direction::kRight, std::numeric_limits<float>::max()));
    else
        new_distances.push_back(std::make_pair(Direction::kRight, GetDistance(head_x+speed, head_y)));
    
    switch (direction) {
        case Direction::kUp:
            new_distances[1].second = std::numeric_limits<float>::max();
            break;

        case Direction::kDown:
            new_distances[0].second = std::numeric_limits<float>::max();
            break;

        case Direction::kLeft:
            new_distances[3].second = std::numeric_limits<float>::max();
            break;

        case Direction::kRight:
            new_distances[2].second = std::numeric_limits<float>::max();
            break;
    }
    
    // Find the minimum distance to the food and setting the new direction 
    sort(new_distances.begin(),
         new_distances.end(),
         [](const std::pair<Snake::Direction, float> a, std::pair<Snake::Direction, float> b){ return a.second > b.second;});
    direction = new_distances.back().first;

    Snake::UpdateHead();
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
    // Add previous head location to vector
    (*body).push_back(prev_head_cell);

    if (!growing) {
        // Remove the tail from the vector.
        (*body).erase((*body).begin());
    } else {
        growing = false;
        size++;
    }

    // Check if the snake has died.
    for (auto const &item : *body) {
        if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
            alive = false;
        }
    }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
    if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
        return true;
    }
    for (auto const &item : *body) {
        if (x == item.x && y == item.y) {
            return true;
        }
    }
    return false;
}