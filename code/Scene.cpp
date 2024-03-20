/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#pragma once
#include "Scene.hpp"
#include "Entity.hpp"
#include "Vehicle.hpp"
#include "Turret.hpp"
#include "Platform.hpp"


using namespace std;

namespace GameBox2D
{
    Scene::Scene(Vec2 gravity, float scale) : physics_to_graphics_scale(scale) {
        world.reset(new b2World(b2Vec2(gravity.x, gravity.y)));

        eventSystem->subscribe("STOP", [&] { running = false; });
        world->SetContactListener(contatcListener.get());
    }

    void Scene::Start() {
        shared_ptr<Entity> entity;

        #pragma region Terrain
        entity = AddEntity("Terrain", BodyType::staticBody);
        entity->AddFixture_Edge(Vec2(0.00f, 1.50f), Vec2(1.25f, 1.50f));
        entity->AddFixture_Edge(Vec2(1.25f, 1.50f), Vec2(1.55f, 1.30f));
        entity->AddFixture_Edge(Vec2(1.55f, 1.30f), Vec2(2.30f, 0.75f));
        entity->AddFixture_Edge(Vec2(2.30f, 0.75f), Vec2(2.50f, 0.65f));
        entity->AddFixture_Edge(Vec2(2.50f, 0.65f), Vec2(3.00f, 0.50f));
        entity->AddFixture_Edge(Vec2(3.00f, 0.50f), Vec2(3.50f, 0.45f));
        entity->AddFixture_Edge(Vec2(3.50f, 0.45f), Vec2(4.00f, 0.40f));
        entity->AddFixture_Edge(Vec2(4.00f, 0.40f), Vec2(4.50f, 0.45f));
        entity->AddFixture_Edge(Vec2(4.50f, 0.45f), Vec2(5.00f, 0.50f));
        entity->AddFixture_Edge(Vec2(5.00f, 0.50f), Vec2(5.50f, 0.60f));
        entity->AddFixture_Edge(Vec2(5.50f, 0.60f), Vec2(6.00f, 0.80f));
        entity->AddFixture_Edge(Vec2(6.00f, 0.80f), Vec2(6.50f, 0.90f));
        entity->AddFixture_Edge(Vec2(6.50f, 0.90f), Vec2(6.50f, 0.00f));
        entity->AddFixture_Edge(Vec2(9.00f, 0.00f), Vec2(9.00f, 0.30f));
        entity->AddFixture_Edge(Vec2(9.00f, 0.30f), Vec2(15.0f, 1.00f));
        entity->AddFixture_Edge(Vec2(15.0f, 1.00f), Vec2(15.0f, 5.40f));
        entity->AddFixture_Edge(Vec2(15.0f, 5.40f), Vec2(0.00f, 5.40f));
        entity->AddFixture_Edge(Vec2(0.01f, 5.40f), Vec2(0.01f, 1.50f));

        entity->AddFixture_Box(0.6f,  0.1f, Vec2(4.0f, 3.f), -45.f * b2_pi / 180.0f);
        entity->AddFixture_Box(0.6f,  0.1f, Vec2(4.7f, 3.f),  45.f * b2_pi / 180.0f);
        entity->AddFixture_Box(0.72f, 0.1f, Vec2(5.78f, 3.4f),  0.f);
        #pragma endregion

        AddVehicle("Player")->SetPosition(Vec2(0.6f, 2.f));

        entity = AddTurret("Turret");
        entity->SetPosition(Vec2(12.f, 1.9f));

        entity = AddEntity("TurretSensor", BodyType::staticBody);
        entity->AddFixture_Box(1.1f, 1.2f, Vec2(0, 0), 7 * (b2_pi / 180));
        entity->GetBody()->GetFixtureList()[0].SetSensor(true);
        entity->SetPosition(Vec2(14,0));

        entity = AddEntity("DeadSensor", BodyType::staticBody);
        entity->AddFixture_Box(1.2f, 0.1f, Vec2(0, 0), 0);
        entity->GetBody()->GetFixtureList()[0].SetSensor(true);
        entity->SetPosition(Vec2(7.75f, -.5f));

        AddPlatform("Platform")->SetPosition(Vec2(7.75f, -1.f));
    }

    shared_ptr<Entity> Scene::GetEntity(string name) {
        for each (shared_ptr<Entity> entity in entities)
        {
            if (entity->GetName() == name)
            {
                return entity;
            }
        }

        return nullptr;
    }
    
    shared_ptr<Entity> Scene::GetEntity(b2Body* body) {
        for each (shared_ptr<Entity> entity in entities)
        {
            if (entity->GetBody() == body)
            {
                return entity;
            }
        }

        return nullptr;
    }

    void Scene::Update(float deltaTime) {
        world->Step(deltaTime, 8, 4);

        for each (shared_ptr<Entity> entity in entities)
        {
            entity->Update(deltaTime);
        }
    }

    shared_ptr<Entity> Scene::AddEntity(string name, BodyType type){
        entities.push_back(make_shared<Entity>(name, this, type));
        return entities.back();
    }

    shared_ptr<Entity> Scene::AddVehicle(string name) {
        entities.push_back(make_shared<Vehicle>(name, this));
        return entities.back();
    }

    shared_ptr<Entity> Scene::AddTurret(string name) {
        entities.push_back(make_shared<Turret>(name, this));
        return entities.back();
    }

    shared_ptr<Entity> Scene::AddPlatform(string name) {
        entities.push_back(make_shared<Platform>(name, this));
        return entities.back();
    }
}