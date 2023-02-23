#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "FSM.h"

int main()
{

    // elevio_init();
    State currentState = IDLE;
    Elevator elev;
    
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_STOP);
    printf("beforre\n");

    while (1)
    {
        update_elevator(&elev);
        switch (currentState)
        {
        case IDLE: {
            printf("beforehandleidle\n");
            currentState = handleIDLE(&elev);
            break;
}
        case MOVING: {
            currentState = handleMOVING(&elev);
            break;
}
        case DEST_REACHED:{
            currentState = handleDEST_REACHED(&elev);
            break;
}
        case STOP: {
            currentState = handleSTOP(&elev);
            break;
}
        default:
            continue;
        }

    }

    printf("while end\n");
    return 0;
}
