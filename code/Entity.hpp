/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <Box2D/Box2D.h>
#include <SFML\Graphics.hpp>

#include "Scene.hpp"
#include "Utils.hpp"

using namespace std;

namespace GameBox2D
{
    class Scene;

    enum BodyType
    {
        staticBody = 0,
        kinematicBody = 1,
        dynamicBody = 2,
    };

    class Entity 
    {
    protected:

        string   name   = "";
        b2Body*  m_body = nullptr;
        Scene*   scene = nullptr;

        vector<shared_ptr<Entity>> childs;

    public:
        
        Entity(string name, Scene* scene, BodyType bodyType);

        string  GetName() const { return name;   }
        b2Body* GetBody() const { return m_body; }

        void virtual Update(float deltaTime);
        void SetPosition(Vec2 pos);
        
        void AddFixture_Box   (float width, float height, Vec2 pos, float rotation);
        void AddFixture_Circle(float radius, Vec2 pos);
        void AddFixture_Edge  (Vec2 pos1, Vec2 pos2);
    };
    
}