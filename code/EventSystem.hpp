/*
    Codigo de dominio público
    Carlos Cabrera Fernández - 2024
*/

#pragma once

#include <map>
#include <functional>
#include <vector>
#include <string>

using namespace std;

namespace GameBox2D
{
    class EventSystem
    {
    public:
        using EventCallback = function<void()>;

        void subscribe(const string& event, EventCallback callback);
        void trigger  (const string& event);

    private:
        map<string, vector<EventCallback>> m_events;
    };
}