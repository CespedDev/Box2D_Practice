/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#pragma once
#include <iostream>

namespace GameBox2D
{
    struct Vec2
    {
        float x;
        float y;

        Vec2(float x, float y) : x(x), y(y) {};
    };
}