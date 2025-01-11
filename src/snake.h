#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <memory>
#include <iostream>
#include "SDL.h"

class Snake {
 public:
    enum class Direction { kUp, kDown, kLeft, kRight };
    Snake() {};
    Snake(std::size_t &_grid_width, std::size_t &_grid_height)
      : grid_width(_grid_width),
        grid_height(_grid_height),
        head_x(_grid_width / 2),
        head_y(_grid_height / 2) {};
    
    Snake(std::size_t &_grid_width, std::size_t &_grid_height, std::pair<int, int> &coords)
      : grid_width(_grid_width),
        grid_height(_grid_height),
        head_x(coords.first),
        head_y(coords.second) {};

    void Update();
    void GrowBody();
    bool SnakeCell(int x, int y);

    Direction direction = Direction::kUp;

    float speed{0.1f};
    int size{1};
    bool alive{true};
    float head_x;
    float head_y;
    std::shared_ptr<std::vector<SDL_Point>> body = std::make_shared<std::vector<SDL_Point>>();

protected:
    virtual void UpdateHead();
    void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

    bool growing{false};
    std::size_t grid_width;
    std::size_t grid_height;
};


class SnakeBot: public Snake {
 public:
    using Snake::Snake;
    SDL_Point food;
    
 private:
    void UpdateHead();
    float GetDistance(float x, float y);
};

#endif