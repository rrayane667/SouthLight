#pragma once
#include <unordered_map>
#include "event.h"
#include "utilite/dataStruct.h"
#include <functional>


namespace EVENTS{

    class EventManager{
        using Callback = std::function<void(const Event& event)>;

        //std::unordered_map<EventType,DATASTRUCT::DynamicList<Callback>> file;
        public:
            void subscribe(EventType type, Callback c);
            void publish(const Event& event);

    };
}