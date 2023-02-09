#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator.h"
#include "FSM.h"

int main()
{

    elevio_init();
    State currentState = IDLE;

    while (1)
    {   
        switch (currentState)
        {
        case IDLE:
            currentState = handleIDLE();
            break;

        case MOVING:
            handleMOVING();
            break;

        case DEST_REACHED:
            handleDEST_REACHED();
            break;

        case STOP:
            handleSTOP();
            break;
        }
    }

    return 0;
}
