#ifndef STATE_EVENTS_HPP
#define STATE_EVENTS_HPP

#include "Urho3D/Core/Object.h"

enum state_event_task { PUSH, POP, EXCHANGE };

URHO3D_EVENT(E_STATE_CHANGE, state_change) {

    URHO3D_PARAM(P_TASK, task); // short
    URHO3D_PARAM(P_STATE, state); //string
}

#endif
