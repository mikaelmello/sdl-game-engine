#ifndef CAMERAFOLLOWOER_H
#define CAMERAFOLLOWOER_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Component.hpp"
#include "GameObject.hpp"
#include <string>

class CameraFollower : public Component {
    public:
        CameraFollower(GameObject& associated);

        void Update(float dt) override;

        bool Is(const std::string& type) const override;

        void Render() override;
};

#endif