#include "eventmanager/eventmanager.h"


namespace EVENTS{
    void EventManager::subscribe(EventType type, Callback c) {
        int i = 0;
        if(!subscribers[type].len()){
            subscribers[type].append(c);
            return;
        }
        for(auto& callback : subscribers[type]) {
            if (c.layer < callback.layer) {
                subscribers[type].insert(i, c);
                return;
            } else {
                i++;
            }
        }

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
 
                    if(callback(event)) break;

                }
            }
            else{std::cout << "Event mal9inahch"<<std::endl;}
            event_stack.remove(0);
        }
    }
}