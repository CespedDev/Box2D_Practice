/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#include "EventSystem.hpp"

using namespace std;

namespace GameBox2D
{
    void EventSystem::subscribe(const string& event, EventCallback callback) {
        m_events[event].push_back(callback);
    }

    void EventSystem::trigger(const string& event) {
        auto it = m_events.find(event);
        if (it != m_events.end())
        {
            for (const auto& callback : it->second)
            {
                callback();
            }
        }
    }
}