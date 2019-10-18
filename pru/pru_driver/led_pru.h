// Header. 
// part of the code was borrowed from  
// https://markayoder.github.io/PRUCookbook/05blocks/blocks.html

#include <stdint.h>
#include <stdlib.h>

#include <am335x/pru_cfg.h>
#include <am335x/pru_intc.h>
#include <am335x/pru_ctrl.h>
#include "resource_table_empty.h"

#define one_on     700/5   // Stay on 700ns
#define one_off    800/5
#define zero_on    350/5
#define zero_off   600/5
#define reset     60000/5 // Must be at least 50u, use 60u

#define pin_8_11_bit 15
#define pin_8_12_bit 14

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void send_zero(){
  __R30 |= pin_8_11_bit;
  __delay_cycles(zero_on-1);
  __R30 &= pin_8_11_bit;
  __delay_cycles(zero_off-2);
}

void send_one(){
  __R30 |= pin_8_11_bit;
  __delay_cycles(one_on-1);
  __R30 &= pin_8_11_bit;
  __delay_cycles(one_off-2);
}

void debug(int num_blinks){
  int i;
  for(i = 0; i<num_blinks;i++){
    __R30 |= 0x1<<pin_8_12_bit;
    __delay_cycles(500000000);
    __R30 &= ~(0x1<<pin_8_12_bit);
    __delay_cycles(500000000); 
  };
}
