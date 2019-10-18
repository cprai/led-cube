#include <stdint.h>
#include <stdlib.h>

#include <am335x/pru_cfg.h>
#include <am335x/pru_intc.h>
#include <am335x/pru_ctrl.h>
#include "resource_table_empty.h"
#include "led_pru.h"

#define LED_NUM 7
// volatile unsigned int LEDS[LED_NUM];


#define PRU0_DRAM 0x00000000
// #define PRU1_DRAM 0x00010000
// #define PRU_SHARED_RAM 0x00010000

// might need to correct the pointer
volatile unsigned int *LEDS = (volatile unsigned int*) (PRU0_DRAM);

// void init_leds(){
//     int i;
//     uint32_t var;
//     for(i=0;i<LED_NUM;i++){
//       // leds[i]=LEDS[i];
//       // var = LEDS[i]; 

//     }
// }

void update(){
    int i, j;
    for(j=0;j<LED_NUM;j++){
        for(i=23; i>=0; i--) {
            if((LEDS[j]&(0x1<<i))){
                send_one();
            }
        else{
            send_zero();
            }
        }
    }
}

void shutdown(){
    int i,j;
    for(j=0;j<LED_NUM;j++){
        for(i=0; i<24; i++) {
            send_zero();
        }
    }
    __R30 = __R30 & ~(0x1 << pin_8_11_bit); 
    __delay_cycles(reset);
}


int main(void)
{
    while(1){
        // wait for interrupt; 
        // bits 30/31 register interrupts; 
        
        // need to figure out how to extract corresponding sysevent;
        while((__R31 & (0x1<<30))==0){}
        // if sysEvt18 continue else break; 

        update();
        // send signal back to host(arm). 
        // Not needed if we go FFI route.
        // __R31 ^= 32 | 3;
    }
    shutdown();
    return 0;

}
