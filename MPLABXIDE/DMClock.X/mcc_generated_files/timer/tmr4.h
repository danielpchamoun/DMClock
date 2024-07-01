/**
 * TMR4 Generated Driver API Header File
 *
 * @file tmr4.h
 *  
 * @defgroup tmr4 TMR4
 *
 * @brief This file contains the API Prototypes and other data types for the TMR4 driver.
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

#ifndef TMR4_H
#define TMR4_H

#include <stdint.h>
#include <stdbool.h>

/**
  Section: Macro Declarations
*/

/**
  Section: TMR4 APIs
*/

/**
 * @ingroup tmr4
 * @brief Initializes the TMR4 module. This routine must be called before any other timer routines.
 * @param None.
 * @return None.
 */
 void TMR4_Initialize(void);

/**
 * @ingroup tmr4
 * @brief Starts TMR4.
 * @pre The TMR4 should be initialized with TMR4_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void TMR4_Start(void);

/**
 * @ingroup tmr4
 * @brief Stops TMR4.
 * @pre The TMR4 should be initialized with TMR4_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void TMR4_Stop(void);

/**
 * @ingroup tmr4
 * @brief Reads the 8-bit from the TMR4 register.
 * @pre The TMR4 should be initialized with TMR4_Initialize() before calling this API.
 * @param None.
 * @return 8-bit data from the TMR4 register.
 */
uint8_t TMR4_Read(void);

/**
 * @ingroup tmr4
 * @brief Writes the 8-bit value to the TMR4 register.
 * @pre The TMR4 should be initialized with TMR4_Initialize() before calling this API.
 * @param timerVal - 8-bit value written to the TMR4 register.
 * @return None.
 */
void TMR4_Write(uint8_t timerVal);

/**
 * @ingroup tmr4
 * @brief Loads the 8-bit value to the PR4 register.
 * @pre The TMR4 should be initialized with TMR4_Initialize() before calling this API.
 * @param periodVal - 8-bit value written to the PR4 register.
 * @return None.
 */
void TMR4_PeriodCountSet(size_t periodVal);

/**
 * @ingroup tmr4
 * @brief Setter function for the TMR4 overflow callback.
 * @param CallbackHandler - Pointer to the custom callback.
 * @return None.
 */
void TMR4_OverflowCallbackRegister(void (* InterruptHandler)(void));

/**
 * @ingroup tmr4
 * @brief Performs the tasks to be executed on timer overflow event.
 * @param None.
 * @return None.
 */
void TMR4_Tasks(void);

#endif // TMR4_H
/**
 End of File
*/