#pragma once
#include "driver/elevio.h"
#include "buttons.h"
#include "FSM.h"

typedef struct Elevator{
    int current_floor;
    MotorDirection current_dir;
    int Stop;
    Button queue[4][3];
} Elevator;

Elevator* elevator_init();

void update_elevator(Elevator* e, State* state);


void move_elevator(Elevator* e, MotorDirection Dir);
void open_door(Elevator* e);
int check_queue_empty(Elevator* e);
void delete_queue_ELM(Elevator* e, int floor, int button);
int check_req_floor(Elevator* e);
int check_requests(Elevator* e);