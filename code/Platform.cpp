/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#pragma once
#include "Platform.hpp"

using namespace std;

namespace GameBox2D
{
    Platform::Platform(string name, Scene* scene) : Entity(name, scene, BodyType::kinematicBody)
    {
        //CREAR BODY
        AddFixture_Box(1.2f, 0.1f, Vec2(0.f, 0.f), 0.f);

        shared_ptr<Entity> entity;
        entity = scene->AddEntity("PlatformSensor", BodyType::staticBody);
        entity->AddFixture_Box(0.6f, 0.1f, Vec2(0.f, 0.f), 0.f);
        entity->GetBody()->GetFixtureList()[0].SetSensor(true);
        entity->SetPosition(Vec2(0.f, 0.4f));
        childs.push_back(entity);

        #pragma region Events
        scene->GetEventSystem().subscribe("ACTIVATE_TURRET",   [this] { maxPosY = 0.2f; });
        scene->GetEventSystem().subscribe("ACTIVATE_PLATFORM", [this] { maxPosY = 3.4f; });
        #pragma endregion
    }

    void Platform::Update(float deltaTime){
        if(m_body->GetPosition().y < maxPosY)
            SetPosition(Vec2(m_body->GetPosition().x, m_body->GetPosition().y + speed * deltaTime));
    }
}