/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#include "InputSystem.hpp"

using namespace sf;

namespace GameBox2D
{
    void InputSystem::Update() {
        Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case Event::Closed: 
                {
                    eventSystem.trigger("STOP");
                    break;
                }

                case Event::KeyReleased:
                {
                    switch (event.key.code)
                    {
                        case Keyboard::Left:
                        {
                            eventSystem.trigger("LEFT_KEY_RELEASED");
                            break;
                        }
                        case Keyboard::Right:
                        {
                            eventSystem.trigger("RIGHT_KEY_RELEASED");
                            break;
                        }
                        case Keyboard::Up:
                        {
                            eventSystem.trigger("UP_KEY_RELEASED");
                            break;
                        }
                        case Keyboard::Down:
                        {
                            eventSystem.trigger("DOWN_KEY_RELEASED");
                            break;
                        }
                    }
                    break;
                }

                case Event::KeyPressed:
                {
                    switch (event.key.code)
                    {
                        case Keyboard::Left: 
                        {
                            eventSystem.trigger("LEFT_KEY_PRESSED");
                            break;
                        }
                        case Keyboard::Right:
                        {
                            eventSystem.trigger("RIGHT_KEY_PRESSED");
                            break;
                        }
                        case Keyboard::Up:
                        {
                            eventSystem.trigger("UP_KEY_PRESSED");
                            break;
                        }
                        case Keyboard::Down:
                        {
                            eventSystem.trigger("DOWN_KEY_PRESSED");
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
}