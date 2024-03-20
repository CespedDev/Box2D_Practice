/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#pragma once

#include "Entity.hpp"

using namespace std;

namespace GameBox2D
{
    Entity::Entity(string name, Scene* scene, BodyType bodyType) : name(name), scene(scene)
    {
        
        b2BodyDef body_def;
        body_def.type = static_cast<b2BodyType>(bodyType);
        body_def.position.Set(0,0);

        m_body = scene->GetWorld().CreateBody(&body_def);
    }

    void Entity::Update(float deltaTime) {

    }

    void Entity::SetPosition(Vec2 pos) {
        
        for each (shared_ptr<Entity> child in childs)
        {
            Vec2 childPos(
                child->GetBody()->GetPosition().x + (pos.x - m_body->GetPosition().x),
                child->GetBody()->GetPosition().y + (pos.y - m_body->GetPosition().y)
            );

            child->SetPosition(childPos);
        }

        m_body->SetTransform(b2Vec2(pos.x, pos.y), 0);
    }

    #pragma region CreateFixtures

    void Entity::AddFixture_Box(float width, float height, Vec2 pos, float rotation) {
        
        b2FixtureDef   body_fixture;

        b2PolygonShape fix_shape;
        fix_shape.SetAsBox(width, height, b2Vec2(pos.x, pos.y), rotation);

        body_fixture.shape       = &fix_shape; 
        body_fixture.density     = 5.00f; 
        body_fixture.restitution = 0.05f; 
        body_fixture.friction    = 0.5f; 

        m_body->CreateFixture(&body_fixture);
    }

    void Entity::AddFixture_Circle(float radius, Vec2 pos) {

        b2FixtureDef   body_fixture;

        b2CircleShape fix_shape;
        fix_shape.m_radius = radius;
        fix_shape.m_p      = b2Vec2(pos.x, pos.y);

        body_fixture.shape = &fix_shape;
        body_fixture.density = 5.00f;
        body_fixture.restitution = 0.05f;
        body_fixture.friction = 0.5f;

        m_body->CreateFixture(&body_fixture);
    }

    void Entity::AddFixture_Edge(Vec2 pos1, Vec2 pos2) {
        b2FixtureDef body_fixture;
        b2EdgeShape fix_shape;

        fix_shape.SetTwoSided(b2Vec2(pos1.x, pos1.y), b2Vec2(pos2.x, pos2.y));

        body_fixture.shape = &fix_shape;
        body_fixture.density = 5.00f;
        body_fixture.restitution = 0.05f;
        body_fixture.friction = 0.5f;

        m_body->CreateFixture(&body_fixture);
    }

    #pragma endregion

    
}