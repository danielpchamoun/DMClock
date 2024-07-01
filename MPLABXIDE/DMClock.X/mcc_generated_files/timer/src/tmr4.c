/**
 * TMR4 Generated Driver File
 *
 * @file tmr4.c
 * 
 * @ingroup  tmr4
 * 
 * @brief API implementations for the TMR4 module.
 *
 * @version TMR4 Driver Version 1.0.0
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
#include "../tmr4.h"

static void (*TMR4_OverflowCallback)(void);
static void TMR4_DefaultOverflowCallback(void);

/**
  Section: TMR4 APIs
*/

void TMR4_Initialize(void){

    // Set TMR4 to the options selected in the User Interface
    // PR 127; 
    PR4 = 0x7F;
    // TMR 0x0; 
    TMR4 = 0x0;

    // Clearing IF flag.
     PIR2bits.TMR4IF = 0;
    // TCKPS 1:64; TMRON on; TOUTPS 1:1; 
    T4CON = 0x7;

    // Set default overflow callback
    TMR4_OverflowCallbackRegister(TMR4_DefaultOverflowCallback);
}

void TMR4_Start(void)
{
    // Start the Timer by writing to TMRxON bit
    T4CONbits.TMR4ON = 1;
}

void TMR4_Stop(void)
{
    // Stop the Timer by writing to TMRxON bit
    T4CONbits.TMR4ON = 0;
}

uint8_t TMR4_Read(void)
{
    uint8_t readVal;
    readVal = TMR4;
    return readVal;
}

void TMR4_Write(uint8_t timerVal)
{
    // Write to the Timer4 register
    TMR4 = timerVal;;
}

void TMR4_PeriodCountSet(size_t periodVal)
{
   PR4 = (uint8_t) periodVal;
}

void TMR4_OverflowCallbackRegister(void (* InterruptHandler)(void)){
    TMR4_OverflowCallback = InterruptHandler;
}

static void TMR4_DefaultOverflowCallback(void){
    // add your TMR4 interrupt custom code
    // or set custom function using TMR4_OverflowCallbackRegister()
}

void TMR4_Tasks(void)
{
    if(PIR2bits.TMR4IF)
    {
        // Clearing IF flag.
        PIR2bits.TMR4IF = 0;
        TMR4_OverflowCallback();
    }
}

