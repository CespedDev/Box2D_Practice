/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#pragma once
#include "Entity.hpp"

using namespace std;

namespace GameBox2D
{

    class Platform : public Entity
    {
    private:

        float speed = .3f;
        float maxPosY = -1.f;

    public:

        Platform(string name, Scene* scene);

        void Update(float deltaTime) override;

        void SpawnPlatform() {
            maxPosY = 0.2f;
        }
    };

}