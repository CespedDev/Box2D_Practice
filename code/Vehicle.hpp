/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#pragma once
#include "Entity.hpp"

using namespace std;

namespace GameBox2D
{

    class Vehicle : public Entity
    {
    private:

        b2WheelJoint*  left_wheel;
        b2WheelJoint* right_wheel;

        b2RevoluteJoint* basket;

        bool alive = true;

    public:

        Vehicle(string name, Scene* scene);

        void Update(float deltaTime) override;

        void SetMovement  (float speed);
        void ActiveBasket (float speed);
    };

}