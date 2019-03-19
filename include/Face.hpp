#ifndef FACE_H
#define FACE_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <string>
#include "Component.hpp"
#include "GameObject.hpp"

class Face : public Component {
    public:
        Face(GameObject& associated);

        ~Face();

        void Damage(int damage);

        void Update(float dt);

        bool Is(const std::string& type);

        void Render();
    private:
        int hitpoints;
};

#endif
