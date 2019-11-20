#ifndef JOYSTICK_H_
#define JOYSTICK_H_

enum JSEvent { AXIS, BUTTON } joystick_event;
enum JSAxes { L_STICK_X, L_STICK_Y, L_TRIGGER, R_STICK_X, 
                R_STICK_Y, R_TRIGGER, DPAD_X, DPAD_Y } Joystick_axis;
enum JSButtons { A, B, X, Y ,L_BUMPER, R_BUMPER, SELECT, 
                START, HOME, L_STICK, R_STICK } Joystick_button;

extern void Joystick_init(void);
extern void Joystick_cleanUp(void);

extern int Joystick_getState(int, int);

extern void Joystick_stop(void);

#endif
