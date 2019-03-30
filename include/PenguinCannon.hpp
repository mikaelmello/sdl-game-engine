#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Component.hpp"
#include "GameObject.hpp"
#include <string>
#include <memory>

class PenguinCannon : public Component {
    public:
        PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);

        void Update(float dt) override;

        bool Is(const std::string& type) const override;

        void Render() override;

        void Shoot();
    private:
        std::weak_ptr<GameObject> penguinBody;
        float angle;
};

#endif
