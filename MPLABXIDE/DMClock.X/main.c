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

#define _XTAL_FREQ 32000000


//saved in non volatile eeprom
extern __eeprom uint8_t alarm = 0xff;





void main(void) {
    // Initialize PWM, I/O pins, and I2C modules
    SYSTEM_Initialize();

    //inputs
    TRISAbits.TRISA0 = 1; //input
    TRISAbits.TRISA1 = 1; //input
    TRISAbits.TRISA2 = 1; //input
    TRISBbits.TRISB5 = 1; //input
    TRISBbits.TRISB7 = 1; //input
    TRISCbits.TRISC4 = 1; //input
    TRISCbits.TRISC6 = 1; //input
    TRISCbits.TRISC7 = 1; //input
    
    //setting input bits to digital
    ANSELAbits.ANSA0 = 0;
    ANSELAbits.ANSA1 = 0;
    ANSELAbits.ANSA2 = 0;
    ANSELBbits.ANSB5 = 0;
    ANSELBbits.ANSB7 = 0;
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC6 = 0;
    ANSELCbits.ANSC7 = 0;

    
    //outputs
    TRISAbits.TRISA5 = 0; //output
    TRISCbits.TRISC0 = 0; //output    
    TRISCbits.TRISC1 = 0; //output    
    TRISCbits.TRISC2 = 0; //output       

    //setting output latches to 0
    LATAbits.LATA5 = 0;      
    LATCbits.LATC0 = 0;
    LATCbits.LATC1 = 0;
    LATCbits.LATC2 = 0;    
    
    //interrupt settings
    PIE0bits.IOCIE = 1; //enable I/O change interrupt flag
    PIR0bits.IOCIF = 0; //clearing I/O change interrupt flag program starts
    //PIR0bits.INTF = 0; //clearing interrupt flag before program starts
    
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
    }
    
    



    //song testing
    //PWM Period = [ (PR2) + 1 ] x 4 x Tosc x (TMR2 Prescale Value)
    // 1/264 Hz = [ (255) + 1 ] x 4 x (1/32000000) x (TMR2 Prescale Value)
    // PR2 = [1/(frequency x 4 x (1/32000000) x (64))] - 1 
    //https://www.youtube.com/watch?v=2vqa8UcFs9c
    //TMR2_PeriodCountSet();
    /**
     * @ingroup tmr2
     * @brief Loads the 8-bit value to the PR2 register.
     * @pre The TMR2 should be initialized with TMR2_Initialize() before calling this API.
     * @param periodVal - 8-bit value written to the PR2 register.
     * @return None.
     */
    //void TMR2_PeriodCountSet(size_t periodVal);
    // Note to Period Values
    // C, C#, D, D#, E, F, F#, G, G#, A, A#, B
    // 0  1   2  3   4  5  6   7  8   9  10  11
    size_t periodVal[] = {477,450,425,401,378,357,337,318,300,283,267,252};

    TMR2_PeriodCountSet(periodVal[0]);
    TMR2_Start();
    __delay_ms(1000);
    TMR2_Stop();
    
    __delay_ms(1000);
    
    TMR2_PeriodCountSet(periodVal[7]);
    TMR2_Start();
    __delay_ms(1000);
    TMR2_Stop();

    
    
    return;
}

//interrupt service routine
void __interrupt() ISR(){
    if(PIR0bits.IOCIF){
        if(IOCAPbits.IOCAP0){ //change to DM Mode
            PIR0bits.IOCIF = 0;
        }
        if(IOCAPbits.IOCAP1){ //change to Clock Mode (Alarm Off)
            PIR0bits.IOCIF = 0;
        }
        if(IOCAPbits.IOCAP2){ //change to Clock Mode (Alarm On)
            PIR0bits.IOCIF = 0;
        }
        
        if(PORTAbits.RA0 == 1){ //in DM Mode
             
            if(PORTCbits.RC4 == 1 && PORTCbits.RC6 == 1){ //both time and alarm are held down
                if(IOCBPbits.IOCBP5){ //
                    PIR0bits.IOCIF = 0;
                }
                if(IOCBPbits.IOCBP7){ //
                    PIR0bits.IOCIF = 0;
                }
            }
            if(PORTCbits.RC4 == 1){ //time button held down
                if(IOCBPbits.IOCBP5){ //increment worldline index
                    PIR0bits.IOCIF = 0;
                }
                if(IOCBPbits.IOCBP7){ //toggle time leap animation
                    PIR0bits.IOCIF = 0;
                }
            }
            if(PORTCbits.RC6 == 1){ //alarm button held down
                if(IOCBPbits.IOCBP5){ //cycle song track left
                    //future development: play a sample of the song while the alarm button is held down, stopping when letting go of the button
                    PIR0bits.IOCIF = 0;
                }
                if(IOCBPbits.IOCBP7){ //cycle song track right
                    //future development: play a sample of the song while the alarm button is held down, stopping when letting go of the button
                    PIR0bits.IOCIF = 0;
                }
            }
            
            if(IOCBPbits.IOCBP5){ //toggle song track
                PIR0bits.IOCIF = 0;
            }
            if(IOCBPbits.IOCBP7){ //toggle song track
                PIR0bits.IOCIF = 0;
            }
        }
        
        if(PORTAbits.RA1 == 1 || PORTAbits.RA2 == 1){//in Clock Mode 
            if(PORTCbits.RC4 == 1 && PORTCbits.RC6 == 1){
                if(IOCBPbits.IOCBP5){ //reset alarm to 12:00 (midnight)
                    PIR0bits.IOCIF = 0;
                }
                if(IOCBPbits.IOCBP7){ //increment song index that plays when alarm goes off?
                    PIR0bits.IOCIF = 0;
                    //future development: play a sample of the song while the alarm button is held down, stopping when letting go of the button
                }
            }
            if(PORTCbits.RC4 == 1){ //time button held down
                if(IOCBPbits.IOCBP5){ //increment minutes
                    PIR0bits.IOCIF = 0;
                }
                if(IOCBPbits.IOCBP7){ //increment hours
                    PIR0bits.IOCIF = 0;
                }
            }
            if(PORTCbits.RC6 == 1){ //alarm button held down
                if(IOCBPbits.IOCBP5){ //increment minutes
                    PIR0bits.IOCIF = 0;
                }
                if(IOCBPbits.IOCBP7){ //increment hours
                    PIR0bits.IOCIF = 0;
                }
            }
            
            if(IOCBPbits.IOCBP5){ //add feature here, only minutes button pressed
                PIR0bits.IOCIF = 0;
            }
            if(IOCBPbits.IOCBP7){ //add feature here, only hours button pressed
                PIR0bits.IOCIF = 0;
            }
        }   
    }
    //exit interrupt and set INT flag back to 0 to allow for additional interrupts
    //PIR0bits.INTF = 0;
    PIR0bits.IOCIF = 0;
}