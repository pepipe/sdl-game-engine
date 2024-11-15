#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <queue>
#include <iostream>
#include <variant>

namespace GameEngine::Utilities
{
    struct Event
    {
        std::string type;
        std::unordered_map<std::string, std::variant<int, float, std::string>> data;

        explicit Event(const std::string& eventType) : type(eventType) {}
    };

    using EventHandler = std::function<void(const Event&)>;

    class EventQueue
    {
    public:
        void AddEvent(const Event& event)
        {
            _events.push(event);
        }

        void RegisterListener(const std::string& eventType, const EventHandler& handler)
        {
            _listeners[eventType].push_back(handler);
        }

        void UnregisterListener(const std::string& eventType, const EventHandler& handler)
        {
            auto& listeners = _listeners[eventType];
            std::erase_if(listeners,
                          [&handler](const EventHandler& registeredHandler) {
                              return registeredHandler.target<void()>() == handler.target<void>();
                          });
        }
    
        void ProcessEvents()
        {
            while (!_events.empty())
            {
                Event event = _events.front();
                _events.pop();

                if (auto it = _listeners.find(event.type); it != _listeners.end())
                {
                    for (const auto& handler : it->second)
                    {
                        handler(event);
                    }
                }
            }
        }

    private:
        std::queue<Event> _events;
        std::unordered_map<std::string, std::vector<EventHandler>> _listeners;
    };
}