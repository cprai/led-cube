#include "joystick.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <pthread.h>

#define JS_DEV "/dev/input/js0" 
#define NAME_LEN 128

static int js_fd, js_axes = 0, js_buttons = 0, *axis = NULL; 
static char js_name[NAME_LEN], *button = NULL;
static _Bool do_loop = true;
static struct js_event event;
static pthread_t js_tid;

static void *updateState(void *args)
{
    while (do_loop) {
        // read joystick state
        read(js_fd, &event, sizeof(struct js_event));
                
        // handle joystick event
        switch (event.type) { //& ~JS_EVENT_INIT) {    // use this to get init state
            case JS_EVENT_AXIS:
                axis[event.number] = event.value;
                break;
            case JS_EVENT_BUTTON:
                button[event.number] = event.value;
                break;
        }
    }
    return args;
}

void Joystick_init()
{
    // open joystick output file
    if ((js_fd = open(JS_DEV, O_RDONLY)) == -1) {
        printf("Couldn't open joystick.\n");
        exit(-1);
    }

    // get joystick information
    ioctl(js_fd, JSIOCGNAME(NAME_LEN), &js_name);
    ioctl(js_fd, JSIOCGAXES, &js_axes);
    ioctl(js_fd, JSIOCGBUTTONS, &js_buttons);

    printf("Joystick detected:\n\t%s\n\t%d axes\n\t%d buttons\n\n", 
            js_name, js_axes, js_buttons );

    axis = (int *) calloc(js_axes, sizeof(int));
    button = (char *) calloc(js_buttons, sizeof(char));  

    pthread_create(&js_tid, NULL, &updateState, NULL);
}

void Joystick_cleanUp()
{
    //do_loop = false;

    free(axis);
    free(button);
    close(js_fd);

    pthread_join(js_tid, NULL);
}

int Joystick_getState(int event, int input) 
{
    int value = 0;

    switch (event) {
        case AXIS:
            value = axis[input];
            break;
        
        case BUTTON:
            value = button[input];
            break;
    }

    return value;
}

void Joystick_stop()
{
    do_loop = false;
}

