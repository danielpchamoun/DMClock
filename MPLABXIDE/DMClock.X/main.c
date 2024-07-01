/*
 * File:   main.c
 * Author: Daniel
 *
 * Created on June 11, 2024, 10:47 PM
 */


#include <xc.h>
#include "mcc_generated_files\system\system.h"

void main(void) {
    // Initialize PWM, I/O pins, and I2C modules
    SYSTEM_Initialize();
    
    
    
    //rtc driver
    //stored current time in 
    while(true){
        I2C1_ReadStart();        
        
    }
    return;
}
