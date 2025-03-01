#pragma once
#include "system/system.h"

using namespace SYSTEMS;

namespace EVENTS{

    enum class EventType {
        EventA,
        EventB
    };

    struct Event{
        EventType type;
    };
}