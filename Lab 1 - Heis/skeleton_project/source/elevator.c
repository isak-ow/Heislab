#include "elevator.h"
#include <unistd.h>

Elevator* elevator_init()
{
    Elevator e;
    e.current_dir = DIRN_STOP;
    e.current_floor = elevio_floorSensor();
    e.Stop = 0;

    for (int floor = 0; floor < 4; floor++) //initializing queue
    {
        for (int button = BUTTON_HALL_UP; button <= BUTTON_CAB; button++) //hope this works
        {
            e.queue[floor][button].BT_state = 0;
            e.queue[floor][button].BT_floor = floor+1;
            e.queue[floor][button].BT_type = button;
        }
    }

    return &e;
}

void update_elevator(Elevator* e, State* state)
{
    e->current_floor = elevio_floorSensor();

    e->Stop = elevio_stopButton();
    if (elevio_stopButton())
    {*state = STOP;}

    for (int floor = 0; floor < 4; floor++)
    {
        for (int button = 0; button < 3; button++)
        {
            if(elevio_callButton(floor+1,e->queue[floor][button].BT_type))
            e->queue[floor][button].BT_state = elevio_callButton(floor+1, e->queue[floor][button].BT_type);
        }
    }
}

int check_queue_empty(Elevator* e)
{
    for (int floor = 0; floor < 4; floor++)
    {
        for (int button = 0; button < 3; button++)
        {
            if (e->queue[floor][button].BT_state == 1)
            {  
                return 0;
            }
        }
    }
    return 1;
}

void move_elevator(Elevator* e, MotorDirection Dir)
{
    e->current_dir = Dir;
    elevio_motorDirection(Dir);
}

void delete_queue_ELM(Elevator* e, int floor, int button){
    e->queue[floor][button].BT_state = 0;
    elevio_buttonLamp(floor,e->queue[floor][button].BT_type,0);
}


void open_door(Elevator* e)
{
    elevio_doorOpenLamp(1);
    sleep(3);
    while (elevio_obstruction())
    {
        //maybe call update_elevator so you can press while door is open
        continue;
    }
    elevio_doorOpenLamp(0);
}

int check_req_floor(Elevator* e)
{
    for (int i = 0; i < 3; i++)
    {
        if (e->queue[e->current_floor-1][i].BT_state)
        {
            return 1;
        }
    }

    return 0;
}
int check_requests(Elevator* e)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (e->queue[i][j].BT_state)
            {
                return e->queue[i][j].BT_floor;
            }
        }
    }
    return 0;
}