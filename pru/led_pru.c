#include <stdint.h>
#include <stdlib.h>

#include <am335x/pru_cfg.h>
#include <am335x/pru_intc.h>
#include <am335x/pru_ctrl.h>
// #include "resource_table_empty.h"
#include "led_pru.h"

#define one_on     700/5   // Stay on 700ns
#define one_off    800/5
#define zero_on    350/5
#define zero_off   600/5
#define reset     60000/5 // Must be at least 50u, use 60u

#define pin_8_11_bit 15
#define pin_8_12_bit 14

volatile register uint32_t __R30;
volatile register uint32_t __R31;

// #define PRU_DMEM0 far attribute((cregister("PRU_DMEM",  near)))

#define LED_NUM 7

#define PRU0_DRAM 0x00000000

#define WAIT_BLINK_INTERVAL 4000000
#define TEST_BLINK_INTERVAL 3000000

#pragma DATA_SECTION(LEDS,".led_data")
#pragma RETAIN(LEDS)



// might need to correct the pointer
volatile near uint32_t LEDS[LED_NUM];

void light_leds(){
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
    __R30 &= ~(0x1 << pin_8_11_bit); 
    __delay_cycles(reset); 
}

void wait_for_host_interrupt(){
    while((__R31 & (0x1<<30))==0){

    }
}

void test(){
    int i, j;
    for(j=0;j<LED_NUM;j++){
        if(LEDS[j]==0){
            __R30 |= 0x1<<pin_8_11_bit;
            __delay_cycles(TEST_BLINK_INTERVAL);
            __R30 &= ~(0x1<<pin_8_11_bit);
            __delay_cycles(TEST_BLINK_INTERVAL); 
        }
        else{
            __R30 |= 0x1<<pin_8_12_bit;
            __delay_cycles(TEST_BLINK_INTERVAL);
            __R30 &= ~(0x1<<pin_8_12_bit);
            __delay_cycles(TEST_BLINK_INTERVAL); 
        }
    }
}

int main(void)
{
    CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

    // flash green led at the beginning
    // __R30 |= 0x1<<pin_8_12_bit;
    // __delay_cycles(100000000);
    // __R30 &= ~(0x1<<pin_8_12_bit);
    // __delay_cycles(100000000);

    while(1){
        wait_for_host_interrupt();
        CT_INTC.SICR = 18;
        __delay_cycles(TEST_BLINK_INTERVAL); 
        light_leds();
        __delay_cycles(TEST_BLINK_INTERVAL); 
        // test();
        __R31 |= 32 | 3;
    }
    __halt();
}