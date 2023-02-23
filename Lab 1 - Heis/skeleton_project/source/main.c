#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "FSM.h"

int main()
{
    elevio_init();
    reset_FSM();
    State currentState = IDLE;
    Elevator* elevptr = elevator_init();

    while (1)
    {
        update_elevator(elevptr, &currentState);

        switch (currentState)
        {
        case IDLE:
        {
            currentState = handleIDLE(elevptr);
        }
        break;

        case MOVING:
        {
            currentState = handleMOVING(elevptr);
        }
        break;

        case DEST_REACHED:
        {
            currentState = handleDEST_REACHED(elevptr);
        }
        break;

        case STOP:
        {
            currentState = handleSTOP(elevptr);
        }
        break;
        
    }

    return 0;
}