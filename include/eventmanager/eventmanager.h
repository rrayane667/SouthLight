#pragma once
#include <unordered_map>
#include "event.h"
#include "utilite/dataStruct.h"
#include <functional>


// TO DO : propagation des events par ordre des couches

namespace EVENTS{

    struct Callback{
        std::function<void(Event* event)> func;
        inline Callback(std::function<void(Event*)> f) : func(std::move(f)) {}
        void operator()(Event* event) const {
            if (func) func(event);
        }

        friend std::ostream& operator<<(std::ostream& o, const Callback& f) {
            o<<"function pointer";
            return o;
        }
    };

    class EventManager{
        


        std::unordered_map<EventType,DATASTRUCT::DynamicList<Callback>> subscribers;
        DATASTRUCT::DynamicList<Event*> event_stack;
        public:
            //inline EventManager() : event_stack() {}
            void subscribe(EventType type, Callback c);
            void publish(Event* event);
            void processEvents();

    };
}