#include "FSM.h"

State handleIDLE(Elevator* e)
{
    printf("idle\n");
    if (elevio_stopButton())
    {
        return STOP;
    }

    if (check_queue_empty(e)) 
    {
        printf("returned empty");
        return IDLE;
    }

    if (check_req_floor(e))
    {
        return DEST_REACHED;
    }
    else
    {
        return MOVING;
    }
}

State handleMOVING(Elevator* e) //needs some work
{
       if ((e->queue[e->current_floor][BUTTON_CAB].BT_state)) 
    {
        return DEST_REACHED;
    }

    if ((e->current_dir == DIRN_UP) && (e->queue[e->current_floor][BUTTON_HALL_UP].BT_state)) 
    {
        return DEST_REACHED;
    }

    if ((e->current_dir == DIRN_DOWN) && (e->queue[e->current_floor][BUTTON_HALL_DOWN].BT_state)) 
    {
        return DEST_REACHED;
    }

    if (e->current_dir == DIRN_STOP)
    {
        if (e->current_floor == -1) // if we have stopped between floors
        {
            return STOP;
        }
        else if (e->current_floor < check_requests(e)) // move up if req over
        {
            move_elevator(e, DIRN_UP);
        }
        else if (e->current_floor > check_requests(e)) // move down if req under
        {
            move_elevator(e, DIRN_DOWN);
        }
    }
    return MOVING;
}

State handleDEST_REACHED(Elevator* e)
{
    if (e->Stop)
    {
        return STOP;
    }

    delete_queue_ELM(e);
    move_elevator(e,DIRN_STOP);

    open_door(e);

    if (check_queue_empty(e))
    {
        e->current_dir = DIRN_STOP;
        return IDLE;
    }

    return MOVING;
}

State handleSTOP(Elevator* e)
{
    return STOP;
}