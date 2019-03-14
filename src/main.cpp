#include "Game.hpp"

int main (int argc, char** argv) {
    
    Game game = Game::GetInstance();
    game.Run();

    return 0;
}
