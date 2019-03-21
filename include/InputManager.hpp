#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <string>
#include <unordered_map>

class InputManager {
    public:
        void Update();

        bool KeyPress(int key) const;
        bool KeyRelease(int key) const;
        bool IsKeyDown(int key) const;

        bool MousePress(int button) const;
        bool MouseRelease(int button) const;
        bool IsMouseDown(int button) const;

        int GetMouseX() const;
        int GetMouseY() const;

        bool QuitRequested() const;

        InputManager& GetInstance();
    private:
        InputManager();

        ~InputManager();

        bool mouseState[6];
        int mouseUpdate[6];

        std::unordered_map<int, bool> keyState;
        std::unordered_map<int, int> keyUpdate;

        bool quitRequested;
        int updateCounter;

        int mouseX;
        int mouseY;
};

#endif
