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

        void Damage(int damage);

        void Update(float dt) override;

        bool Is(const std::string& type) override;

        void Render() override;
    private:
        int hitpoints;
};

#endif
