#include "elevator.h"
#include "buttons.h"

Button check_requests(Elevator e)
{
    for (int floor = 0; floor < 3; floor++)
    {
        for (int button = 0; button < 2; button++)
        {
            if (e.queue[floor][button])
            {
                Button b = Button{button, floor, queue[floor][button]}; 
                return b;
            }
        }
    }
}