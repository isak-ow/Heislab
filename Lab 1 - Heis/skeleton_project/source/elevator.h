#pragma once
#include "buttons.h"

typedef struct{
    int current_floor;
    MotorDirection current_dir;
    MotorDirection last_dir;
    int queue[][]; 
    bool Stop;
} Elevator;

Button check_requests();
int queue_empty();