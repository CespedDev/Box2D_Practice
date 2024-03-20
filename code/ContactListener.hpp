/*
    Codigo de dominio p�blico
    Carlos Cabrera Fern�ndez - 2024
*/

#pragma once

#include <Box2D/Box2D.h>

namespace GameBox2D{
    
    class Scene;

    class ContactListener : public b2ContactListener
    {
    private:

        Scene* scene;

    public:
        ContactListener(Scene* scene) : scene(scene) {};

        void BeginContact(b2Contact* contact);

        void EndContact(b2Contact* contact);
    };
}