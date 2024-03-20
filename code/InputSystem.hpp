/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "EventSystem.hpp"

using namespace sf;

namespace GameBox2D
{
    class EventSystem;

    class InputSystem
    {
    private:
        EventSystem& eventSystem;
        RenderWindow& window;

    public:

        InputSystem(EventSystem& eventSystem, RenderWindow& window) : eventSystem(eventSystem), window(window) {};
        void Update();
    };
}