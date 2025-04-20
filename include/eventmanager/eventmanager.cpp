#include "eventmanager/eventmanager.h"


namespace EVENTS{
    void EventManager::subscribe(EventType type, Callback c) {
        subscribers[type].append(c);

    }

    void EventManager::publish(Event* event) {
        
       event_stack.append(event);
        
    }

    void EventManager::processEvents(){
        
        while(event_stack.len()){
            Event* event = event_stack[0];
            auto it = subscribers.find(event->type);
            if (it != subscribers.end()) {
                
                for (auto& callback : it->second) {
                    
                    callback(event);
                }
            }
            else{std::cout << "Event mal9inahch"<<std::endl;}
            event_stack.remove(0);
        }
    }
}