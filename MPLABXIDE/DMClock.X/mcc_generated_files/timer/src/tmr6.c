/**
 * TMR6 Generated Driver File
 *
 * @file tmr6.c
 * 
 * @ingroup  tmr6
 * 
 * @brief API implementations for the TMR6 module.
 *
 * @version TMR6 Driver Version 1.0.0
 */

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "../tmr6.h"

static void (*TMR6_OverflowCallback)(void);
static void TMR6_DefaultOverflowCallback(void);

/**
  Section: TMR6 APIs
*/

void TMR6_Initialize(void){

    // Set TMR6 to the options selected in the User Interface
    // PR 255; 
    PR6 = 0xFF;
    // TMR 0x0; 
    TMR6 = 0x0;

    // Clearing IF flag.
     PIR2bits.TMR6IF = 0;
    // TCKPS 1:1; TMRON on; TOUTPS 1:1; 
    T6CON = 0x4;

    // Set default overflow callback
    TMR6_OverflowCallbackRegister(TMR6_DefaultOverflowCallback);
}

void TMR6_Start(void)
{
    // Start the Timer by writing to TMRxON bit
    T6CONbits.TMR6ON = 1;
}

void TMR6_Stop(void)
{
    // Stop the Timer by writing to TMRxON bit
    T6CONbits.TMR6ON = 0;
}

uint8_t TMR6_Read(void)
{
    uint8_t readVal;
    readVal = TMR6;
    return readVal;
}

void TMR6_Write(uint8_t timerVal)
{
    // Write to the Timer6 register
    TMR6 = timerVal;;
}

void TMR6_PeriodCountSet(size_t periodVal)
{
   PR6 = (uint8_t) periodVal;
}

void TMR6_OverflowCallbackRegister(void (* InterruptHandler)(void)){
    TMR6_OverflowCallback = InterruptHandler;
}

static void TMR6_DefaultOverflowCallback(void){
    // add your TMR6 interrupt custom code
    // or set custom function using TMR6_OverflowCallbackRegister()
}

void TMR6_Tasks(void)
{
    if(PIR2bits.TMR6IF)
    {
        // Clearing IF flag.
        PIR2bits.TMR6IF = 0;
        TMR6_OverflowCallback();
    }
}

