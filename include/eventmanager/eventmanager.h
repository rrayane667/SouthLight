#pragma once
#include <unordered_map>
#include "event.h"
#include "utilite/dataStruct.h"
#include <functional>


// TO DO : propagation des events par ordre des couches

namespace EVENTS{

    struct Callback{
        int layer;
        std::function<bool (Event* event)> func;
        inline Callback(std::function<bool (Event*)> f, int l) : layer(l), func(std::move(f)) {}
        bool operator()(Event* event) const {
            if (func) return func(event);
            std::cout << "Callback function is not set!" << std::endl;
            return false;
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