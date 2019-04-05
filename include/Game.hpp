#ifndef GAME_H
#define GAME_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define INCLUDE_SDL
#include "SDL_include.h"
#include "Vec2.hpp"
#include "State.hpp"
#include <string>
#include <stack>
#include <memory>

class Game {
    public:
        ~Game();

        void Run();

        SDL_Renderer* GetRenderer();

        State& GetCurrentState();

        void Push(State* state);

        static Game& GetInstance();        

        float GetDeltaTime() const;

        int GetWidth() const;

        int GetHeight() const;
    private:
        Game(const std::string& title, int width, int height);

        void CalculateDeltaTime();

        static Game* instance;

        SDL_Window* window;

        SDL_Renderer* renderer;

        std::stack<std::unique_ptr<State>> stateStack;

        State* storedState;

        int frameStart;

        float dt;

        int width;

        int height;
};

#endif
