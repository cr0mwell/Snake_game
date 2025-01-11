#include <iostream>
#include <fstream>
#include "structures.h"
#include "controller.h"
#include "game.h"
#include "renderer.h"


void printResults(Game &game) {
    std::cout << "Game has terminated successfully!\n";
    std::cout << "Score: " << game.GetScore() << "\n";
    std::cout << "Size: " << game.GetSize() << "\n";
    
    std::ofstream f;
    f.open("results.txt");
    if(f.is_open()) {
        f << "Score: " << game.GetScore() << "\n";
        f << "Snake size: " << game.GetSize() << "\n";
    }
    
    f.close();
}

int main() {
    std::size_t kMsPerFrame{1000 / FPS};
    std::size_t kScreenWidth{SCREEN[0]};
    std::size_t kScreenHeight{SCREEN[1]};
    std::size_t kGridWidth{GRID[0]};
    std::size_t kGridHeight{GRID[1]};

    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    Controller controller;
    Game game(kGridWidth, kGridHeight);
    game.Run(std::move(controller), std::move(renderer), kMsPerFrame);
    printResults(game);
    return 0;
}