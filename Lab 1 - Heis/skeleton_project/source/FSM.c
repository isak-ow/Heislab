#include "FSM.h"

void reset_FSM()
{
    elevio_doorOpenLamp(0);
    turnOffAllLights();
    while (elevio_floorSensor() == -1)
    {
        elevio_motorDirection(DIRN_DOWN); // assume elevator starts at floor 1 or above
    }
    elevio_motorDirection(DIRN_STOP);
}

State handleIDLE(Elevator *e)
{
    if (check_req_floor(e))
    {
        return DEST_REACHED;
    }

    else if (check_queue_empty(e))
    {
        printf("no new requests");
        return IDLE;
    }

    else
    {
        return MOVING;
    }
}

State handleMOVING(Elevator *e) // needs some work
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

State handleDEST_REACHED(Elevator *e)
{
    elevio_motorDirection(DIRN_STOP);

    if (e->current_dir == DIRN_UP)
    {
        delete_queue_ELM(e, e->current_floor, BUTTON_HALL_UP);
    }

    else if (e->current_dir == DIRN_DOWN)
    {
        delete_queue_ELM(e, e->current_floor, BUTTON_HALL_DOWN);
    }

    open_door(e);

    if (check_queue_empty(e))
    {
        return IDLE;
    }

    return MOVING;
}

State handleSTOP(Elevator *e)
{
    return STOP;
}