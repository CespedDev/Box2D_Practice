/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#include "Scene.hpp"
#include "Entity.hpp"
#include "ContactListener.hpp"

namespace GameBox2D
{
    void ContactListener::BeginContact(b2Contact* contact) {
        shared_ptr<Entity> entityA = scene->GetEntity(contact->GetFixtureA()->GetBody());
        shared_ptr<Entity> entityB = scene->GetEntity(contact->GetFixtureB()->GetBody());
        
        if (entityA == nullptr || entityB == nullptr)
            return;

        if ((entityA->GetName() == "Player"       || entityB->GetName() == "Player") &&
            (entityA->GetName() == "TurretSensor" || entityB->GetName() == "TurretSensor"))
        {
            scene->GetEventSystem().trigger("ACTIVATE_TURRET");
        }
        else 
        if ((entityA->GetName() == "Player"         || entityB->GetName() == "Player") &&
            (entityA->GetName() == "PlatformSensor" || entityB->GetName() == "PlatformSensor"))
            scene->GetEventSystem().trigger("ACTIVATE_PLATFORM");
        else
        if ((entityA->GetName() == "Player" || entityB->GetName() == "Player") &&
            (entityA->GetName() == "DeadSensor" || entityB->GetName() == "DeadSensor"))
            scene->GetEventSystem().trigger("PLAYER_DEAD");
        
    }

    void ContactListener::EndContact(b2Contact* contact) {

    }
}