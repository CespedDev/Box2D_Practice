/*
    Codigo de dominio p�blico
    Carlos Cabrera Fern�ndez - 2024
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