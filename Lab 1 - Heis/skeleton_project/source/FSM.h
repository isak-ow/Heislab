#pragma once
#include "elevator.h"

typedef enum State
{
    IDLE,
    MOVING,
    DEST_REACHED,
    STOP
} State;

void reset_FSM();
State handleIDLE(Elevator* e);
State handleMOVING(Elevator* e);
State handleDEST_REACHED(Elevator* e);
State handleSTOP(Elevator* e);

