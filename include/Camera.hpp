#ifndef CAMERA_H
#define CAMERA_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Vec2.hpp"
#include "GameObject.hpp"

class Camera {
    public:
        static void Follow(GameObject* newFocus);

        static void Unfollow();

        static void Update(float dt);

        static Vec2 pos;

        static Vec2 speed;
    private:
        static GameObject* focus;
};

#endif
