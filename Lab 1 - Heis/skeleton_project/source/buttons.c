#include "buttons.h"

void turnOffAllLights()
{
    for (int floor = 0; floor < 4; floor++)
    {
        for (ButtonType button = 0; button < 3; button++)
        {
            elevio_buttonLamp(floor, button, 0);
        }
    }
}