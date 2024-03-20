/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#pragma once

#include "Vehicle.hpp"

using namespace std;

namespace GameBox2D
{
    Vehicle::Vehicle(string name, Scene* scene) : Entity(name, scene, BodyType::dynamicBody)
    {
        //CREAR BODY
        AddFixture_Box(0.5f, 0.05f, Vec2(0.f,0.f), 0.f);

        #pragma region Wheels
        childs.push_back(make_shared<Entity>("Right_Wheel", scene, BodyType::dynamicBody));
        childs.back()->AddFixture_Circle(0.1f, Vec2(0.f, 0.f));
        childs.back()->SetPosition(Vec2(-0.4f, -0.2f));

        b2WheelJointDef wheelDef;
        wheelDef.Initialize(m_body, childs.back()->GetBody(), childs.back()->GetBody()->GetPosition(), b2Vec2(0.0f, 1.f));
        wheelDef.motorSpeed = 0.0f;
        wheelDef.maxMotorTorque = 20.0f;
        wheelDef.enableMotor = true;
        wheelDef.enableLimit = true;
        wheelDef.collideConnected = true;

        right_wheel = dynamic_cast<b2WheelJoint*>(scene->GetWorld().CreateJoint(&wheelDef));

        childs.push_back(make_shared<Entity>("Left_Wheel",  scene, BodyType::dynamicBody));
        childs.back()->AddFixture_Circle(0.1f, Vec2(0.f, 0.f));
        childs.back()->SetPosition(Vec2(0.4f, -0.2f));

        wheelDef.Initialize(m_body, childs.back()->GetBody(), childs.back()->GetBody()->GetPosition(), b2Vec2(0.0f, 1.f));
        wheelDef.motorSpeed = 0.0f;
        wheelDef.maxMotorTorque = 1000.0f;
        wheelDef.enableMotor = true;
        wheelDef.enableLimit = true;
        wheelDef.collideConnected = true;

        left_wheel = dynamic_cast<b2WheelJoint*>(scene->GetWorld().CreateJoint(&wheelDef));
        #pragma endregion
        
        #pragma region Basket
        childs.push_back(make_shared<Entity>("Basket", scene, BodyType::dynamicBody));
        childs.back()->AddFixture_Box(0.5f, 0.05f, Vec2( 0.f,  0.f), 0.f);
        childs.back()->AddFixture_Box(0.05f, 0.2f, Vec2(0.45f, 0.15f), 0.f);
        childs.back()->AddFixture_Box(0.05f, 0.2f, Vec2(-0.45f, 0.15f), 0.f);
        childs.back()->SetPosition(Vec2(0.f, 0.1f));

        b2RevoluteJointDef jointDef;
        jointDef.Initialize(m_body, childs.back()->GetBody(), b2Vec2(-0.45f, 0.05f));
        jointDef.enableMotor = true;
        jointDef.enableLimit = true;
        jointDef.lowerAngle = 0.f;
        jointDef.upperAngle = 120.f * (b2_pi / 180.f);
        jointDef.maxMotorTorque = 2000.0f;
        jointDef.motorSpeed = 0.f;

        basket = dynamic_cast<b2RevoluteJoint*>(scene->GetWorld().CreateJoint(&jointDef));
        #pragma endregion

        #pragma region Events
        scene->GetEventSystem().subscribe( "LEFT_KEY_PRESSED",  [this] { SetMovement( 60.f); });
        scene->GetEventSystem().subscribe("RIGHT_KEY_PRESSED",  [this] { SetMovement(-60.f); });
        scene->GetEventSystem().subscribe( "LEFT_KEY_RELEASED", [this] { SetMovement(  0.f); });
        scene->GetEventSystem().subscribe("RIGHT_KEY_RELEASED", [this] { SetMovement(  0.f); });

        scene->GetEventSystem().subscribe(  "UP_KEY_PRESSED",  [this] { ActiveBasket( 0.5f); });
        scene->GetEventSystem().subscribe("DOWN_KEY_PRESSED",  [this] { ActiveBasket(-0.5f); });
        scene->GetEventSystem().subscribe(  "UP_KEY_RELEASED", [this] { ActiveBasket(  0.f); });
        scene->GetEventSystem().subscribe("DOWN_KEY_RELEASED", [this] { ActiveBasket(  0.f); });
        
        scene->GetEventSystem().subscribe("PLAYER_DEAD", [this] { alive = false; });
        #pragma endregion
    }

    void Vehicle::Update(float deltaTime) {
        if (!alive)
        {
            SetPosition(Vec2(0.6f, 2.f));
            alive = true;
        }

    }

    void Vehicle::SetMovement(float speed) {
        right_wheel->SetMotorSpeed(speed);
        left_wheel ->SetMotorSpeed(speed);
    }

    void Vehicle::ActiveBasket(float speed) {
        basket->SetMotorSpeed(speed);
    }
}