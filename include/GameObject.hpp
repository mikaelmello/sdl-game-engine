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

        void Start();

        bool IsDead() const;

        void RequestDelete();

        void NotifyCollision(GameObject& other);

        void AddComponent(Component* cpt);

        void RemoveComponent(Component* cpt);

        Component* GetComponent(const std::string& type);

        Rect box;

        double angleDeg;
    private:
        std::vector<std::unique_ptr<Component>> components;
        bool isDead;
        bool started;
};

#endif
