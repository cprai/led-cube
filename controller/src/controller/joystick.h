enum JSEvent { AXIS, BUTTON };
enum JSAxes { L_STICK_X, L_STICK_Y, L_TRIGGER, R_STICK_X, 
                R_STICK_Y, R_TRIGGER, DPAD_X, DPAD_Y };
enum JSButtons { A, B, X, Y ,L_BUMPER, R_BUMPER, SELECT, 
                START, HOME, L_STICK, R_STICK };

extern void Joystick_init(void);
extern void Joystick_cleanUp(void);

extern int Joystick_getState(int, int);

extern void Joystick_stop(void);
