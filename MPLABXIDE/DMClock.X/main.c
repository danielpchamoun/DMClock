/*
 * File:   main.c
 * Author: Daniel
 *
 * Created on June 11, 2024, 10:47 PM
 */

#include <xc.h>
#include "mcc_generated_files\system\system.h"
#include "mcc_generated_files\i2c_host\i2c_host_types.h"
#include "mcc_generated_files\i2c_host\mssp1.h"


//saved in non volatile eeprom
__eeprom extern uint8_t alarm = 0xC;

void main(void) {
    // Initialize PWM, I/O pins, and I2C modules
    SYSTEM_Initialize();
        
    #define I2C_CLIENT_ADDR 0x00
    #define DATALENGTH 2

    const i2c_host_interface_t *I2C = &I2C1_Host;

    uint8_t dataWrite[2];
    uint8_t dataRead[2];
    
    //rtc driver example of writing
    //stored current time in 
        if (I2C->Write(I2C_CLIENT_ADDR, dataWrite, DATALENGTH))
    {
        while(I2C->IsBusy())
        {
            I2C->Tasks();
        }
        if (I2C->ErrorGet() != I2C_ERROR_NONE)
        {
            /* Write operation is successful */
        }
        else
        {
            /* Error handling */
        }
    }
    
    
    
    return;
}

