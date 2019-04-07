#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Component.hpp"
#include "Rect.hpp"
#include <string>
#include <vector>
#include <memory>

class GameObject {
    public:
        GameObject();

        ~GameObject();

        void Update(float dt);

        void Render();

        bool IsDead() const;

        void RequestDelete();

        void AddComponent(Component* cpt);

        void RemoveComponent(Component* cpt);

        std::weak_ptr<Component> GetComponent(const std::string& type);

        Rect box;
    private:
        std::vector<std::shared_ptr<Component>> components;
        bool isDead;

};

#endif
