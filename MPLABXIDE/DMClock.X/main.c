/*
 * File:   main.c
 * Author: Daniel
 *
 * Created on June 11, 2024, 10:47 PM
 */


#include <xc.h>

void main(void) {
    
    SYSTEM_Initialize();
    
    // Initialize SPI and I2C modules
    I2C1_Initialize();
    
    return;
}
