/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#pragma once

#include "Turret.hpp"

using namespace std;

namespace GameBox2D
{
    Turret::Turret(string name, Scene* scene) : Entity(name, scene, BodyType::staticBody)
    {
        AddFixture_Box(0.1f, 1.2f, Vec2(0.f,0.f), 0.f);
        m_body->GetFixtureList()[0].SetSensor(true);

        #pragma region Basket
        childs.push_back(make_shared<Entity>("Basket", scene, BodyType::dynamicBody));
        childs.back()->AddFixture_Box(0.1f, 0.5f, Vec2(-0.3f, 0.3f),  45.f * (b2_pi / 180));
        childs.back()->AddFixture_Box(0.1f, 0.5f, Vec2( 0.3f, 0.3f), -45.f * (b2_pi / 180));
        childs.back()->SetPosition(Vec2(0.f, 1.2f));

        b2RevoluteJointDef jointDef;
        jointDef.Initialize(m_body, childs.back()->GetBody(), b2Vec2(0.f, 1.2f));
        jointDef.enableMotor = true;
        jointDef.enableLimit = true;
        jointDef.lowerAngle = -60.f * (b2_pi / 180.f);
        jointDef.upperAngle = 0.f;
        jointDef.maxMotorTorque = 2000.0f;
        jointDef.motorSpeed = 0.f;

        turret = dynamic_cast<b2RevoluteJoint*>(scene->GetWorld().CreateJoint(&jointDef));
        #pragma endregion

        childs.push_back(make_shared<Entity>("Ball", scene, BodyType::dynamicBody));
        childs.back()->AddFixture_Circle(0.1f, Vec2(0.f, 1.5f));
        childs.push_back(make_shared<Entity>("Ball", scene, BodyType::dynamicBody));
        childs.back()->AddFixture_Circle(0.1f, Vec2(0.f, 1.5f));
        childs.push_back(make_shared<Entity>("Ball", scene, BodyType::dynamicBody));
        childs.back()->AddFixture_Circle(0.1f, Vec2(0.f, 1.5f));

        #pragma region Events        
        scene->GetEventSystem().subscribe("ACTIVATE_TURRET", [this] { ActiveTurret(-0.6f); });
        #pragma endregion
    }


    void Turret::ActiveTurret(float speed) {
        turret->SetMotorSpeed(speed);
        scene->GetEventSystem().trigger("SPAWN_PLATFORM");
    }
}