#pragma once
#include "driver/elevio.h"
#include "buttons.h"

typedef struct{
    int current_floor;
    MotorDirection current_dir;
    Button queue[4][3]; 
    int Stop;
} Elevator;

int check_queue_empty(Elevator* e);
void update_elevator(Elevator* e);
void update_queue(Elevator* e);
void move_elevator(Elevator* e, MotorDirection Dir);
void open_door();
void delete_queue_ELM(Elevator* e);
int check_req_floor(Elevator* e);
int check_requests(Elevator* e);