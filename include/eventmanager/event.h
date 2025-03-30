#pragma once
#include "system/system.h"


namespace EVENTS{

    enum class EventType {
        EventA,
        EventB
    };

    struct Event{
        EventType type;
    };
}