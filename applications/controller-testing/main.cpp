#include <iostream>

extern "C" {
#include "controller/joystick.h"
}

int main() {
    Joystick_init();

    /*  Possible states to print out:
            AXIS:   L_STICK_X, L_STICK_Y, L_TRIGGER, R_STICK_X, 
                    R_STICK_Y, R_TRIGGER, DPAD_X, DPAD_Y

            BUTTON: A, B, X, Y ,L_BUMPER, R_BUMPER, SELECT, 
                    START, HOME, L_STICK, R_STICK
    */
    while (1)
    {
        if (Joystick_getState(BUTTON, HOME) == 1) {
            printf("\nHOME pressed, stopping..\n");
            Joystick_stop();
            break;
        }
        else {
            printf("LS_X: %6d  LS_Y: %6d  \r", 
                    Joystick_getState(AXIS, L_STICK_X), 
                    Joystick_getState(AXIS, L_STICK_Y));
            fflush(stdout);
        }
    }

    Joystick_cleanUp();
}
