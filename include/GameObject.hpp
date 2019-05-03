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
        GameObject(double priority = 1000);

        ~GameObject();

        void Update(float dt);

        void Render();

        void Start();

        bool IsDead() const;

        void RequestDelete();

        void NotifyCollision(GameObject& other);

        void AddComponent(Component* cpt);

        void RemoveComponent(Component* cpt);

        std::weak_ptr<Component> GetComponent(GameData::Types type);

        Rect box;

        double angleDeg;

        double priority;
    private:
        std::vector<std::shared_ptr<Component>> components;
        bool isDead;
        bool started;
};

#endif
