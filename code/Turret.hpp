/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#pragma once
#include "Entity.hpp"

using namespace std;

namespace GameBox2D
{

    class Turret : public Entity
    {
    private:

        b2RevoluteJoint* turret;

    public:

        Turret(string name, Scene* scene);

        void ActiveTurret (float speed);
    };

}