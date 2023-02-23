#pragma once
#include "driver/elevio.h"

typedef struct{
    ButtonType BT_type;
    int BT_floor;
    int BT_state;
}Button;

void setButtonLight(int on_off);
void saveButtonStates();
void turnOffAllLights();