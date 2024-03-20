/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#pragma once

#include <memory>
#include <vector>
#include <Box2D/Box2D.h>

#include "Utils.hpp"
#include "EventSystem.hpp"
#include "ContactListener.hpp"

using namespace std;

namespace GameBox2D
{
    class Entity;
    enum  BodyType;
    class EventSystem;

    class Scene
    {
    private:

        unique_ptr<b2World>         world;
        unique_ptr<EventSystem>     eventSystem     { new EventSystem()};
        unique_ptr<ContactListener> contatcListener { new ContactListener(this) };

        vector<shared_ptr<Entity>> entities;

    public:

        const float physics_to_graphics_scale;
        bool running = true;

        Scene(Vec2 gravity, float scale);

        b2World&           GetWorld()       const { return *world; }
        EventSystem&       GetEventSystem() const { return *eventSystem; }
        shared_ptr<Entity> GetEntity(string name);
        shared_ptr<Entity> GetEntity(b2Body* body);

        void Start();
        void Update(float deltaTime);

        shared_ptr<Entity> AddEntity  (string name, BodyType type);
        shared_ptr<Entity> AddVehicle (string name);
        shared_ptr<Entity> AddTurret  (string name);
        shared_ptr<Entity> AddPlatform  (string name);

    };
}