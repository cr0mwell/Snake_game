#include <iostream>
#include <thread>
#include <future>

#include "game.h"
#include "SDL.h"


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake_user(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
    
    auto coords = Game::GetCoordinates();
    snake_bot = SnakeBot(grid_width, grid_height, coords),
    
    PlaceFood();
}

void Game::Run(Controller const controller, Renderer renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake_user);
    if (snake_user.alive) {
        std::future fut1 = std::async(std::launch::async, &Game::Update, this, std::ref(snake_user), false);
        fut1.wait();
    }
    if (snake_bot.alive) {
        std::future fut2 = std::async(std::launch::async, &Game::Update, this, std::ref(snake_bot), true);
        fut2.wait();
    }
    renderer.Render(snake_user, snake_bot, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

std::pair<int, int> Game::GetCoordinates() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by snakes before placing the food.
    if (!snake_user.SnakeCell(x, y) && !snake_bot.SnakeCell(x, y))
      return std::make_pair(x, y);
  }
}

void Game::PlaceFood(bool is_bot) {
  std::pair coords = Game::GetCoordinates();
  food.x = coords.first;
  food.y = coords.second;
  snake_bot.food = food;
}

void Game::Update(Snake &snake, bool is_bot) {
  snake.Update();
    
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  
  _mutex.lock();
  if (food.x == new_x && food.y == new_y) {
    PlaceFood(is_bot);
    
    // Grow snake and increase speed.
    snake.GrowBody();
    if(is_bot) {
        snake.speed += 0.005;
    } else {
        snake.speed += 0.01;
        score++;
    }
  }
  _mutex.unlock();
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake_user.size; }