#pragma once
#include "buttons.h"

struct Elevator {
    int current_floor;
    MotorDirection current_dir;
    MotorDirection last_dir;
    int queue[][]; 
};