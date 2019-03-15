#define INCLUDE_SDL
#include "SDL_include.h"
#include "Game.hpp"
#include <iostream>

int main (int argc, char** argv) {
    try {
        Game game = Game::GetInstance();
        game.Run();
    } catch (std::exception ex) {
        std::cout << "Game crashed\n\n" << std::endl;
        std::cout << "Exception: " << ex.what() << std::endl;
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
    }

    return 0;
}
