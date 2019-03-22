#ifndef FACE_H
#define FACE_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Component.hpp"
#include "GameObject.hpp"
#include <string>

class Face : public Component {
    public:
        Face(GameObject& associated);

        void Damage(int damage);

        void Update(float dt) override;

        bool Is(const std::string& type) const override;

        void Render() override;
    private:
        int hitpoints;
};

#endif
