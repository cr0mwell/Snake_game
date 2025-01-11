#ifndef GAME_H
#define GAME_H

#include <random>
#include <mutex>

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"


class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const controller, Renderer renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake_user;
  SnakeBot snake_bot;
  SDL_Point food;
  std::mutex _mutex;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
    
  std::pair<int, int> GetCoordinates();
  void PlaceFood(bool is_bot=false);
  void Update(Snake &snake, bool is_bot);
};

#endif