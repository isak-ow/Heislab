#include "elevator.h"
#include <unistd.h>

void update_queue(Elevator* e)
{
    for (int floor = 0; floor < 3; floor++)
    {
        for (int button = 0; button < 2; button++)
        {
            printf("inside loop\n");
            if (elevio_callButton(floor, e->queue[floor][button].BT_type))
            {   
                e->queue[floor][button].BT_state = 1;
                elevio_buttonLamp(floor, e->queue[floor][button].BT_type,1);
            }
        }
    }
}

void update_elevator(Elevator* e) //fix this
{
    printf("beforeeleviofloorsensor\n");
    e->current_floor = elevio_floorSensor();
    printf("beforeeleviostopbutton\n");
    e->Stop = elevio_stopButton();
    printf("beforeforloop\n");
    for (int floor = 0; floor < 3; floor++)
    {
        for (int button = 0; button < 2; button++)
        {
            printf("insideloop\n");
            e->queue[floor][button].BT_state = elevio_callButton(floor, button);
        }
    }
}

int check_queue_empty(Elevator* e)
{
    for (int floor = 0; floor < 3; floor++)
    {
        for (int button = 0; button < 2; button++)
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

void delete_queue_ELM(Elevator* e){
    e->queue[e->current_floor][e->current_dir].BT_state = 0;
    elevio_buttonLamp(e->current_floor,e->queue[e->current_floor][e->current_dir].BT_type, 0);
}


void open_door(Elevator* e)
{
    elevio_doorOpenLamp(1);
    sleep(3);
    while (elevio_obstruction())
    {
        continue;
    }
    elevio_doorOpenLamp(0);
}

int check_req_floor(Elevator* e)
{
    for (int i = 0; i < 3; i++)
    {
        if (e->queue[e->current_floor][i].BT_state)
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