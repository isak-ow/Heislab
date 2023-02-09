#include "elevator.h"

int check_requests()
{
    for (int floor = 0; floor < 3; floor++)
    {
        for (int button = 0; button < 2; button++)
        {
            if (queue[floor][button])
            {
                return floor,button ;
            }
        }
    }
}