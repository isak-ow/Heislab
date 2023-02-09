#include "FSM.h"

State handleIDLE()
{
    if elevatorqueue.empty() 
    {
        goto IDLE;
    }
    else if (check_queue() == current_floor)
    {
        goto DEST_REACHED;
    }
    else
    {
        goto MOVING;
    }
}

State handleMOVING()
{
    if (current_floor == dest_floor)
    {
        goto DEST_REACHED;
    }
    else if stop{
        elevio_stopButton();
    }
    
}

State handleDEST_REACHED()
{
    handleIDLE();
}

State handle_STOP()
{
    
}