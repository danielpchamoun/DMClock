/**
 * TMR6 Generated Driver API Header File
 *
 * @file tmr6.h
 *  
 * @defgroup tmr6 TMR6
 *
 * @brief This file contains the API Prototypes and other data types for the TMR6 driver.
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

#ifndef TMR6_H
#define TMR6_H

#include <stdint.h>
#include <stdbool.h>

/**
  Section: Macro Declarations
*/

/**
  Section: TMR6 APIs
*/

/**
 * @ingroup tmr6
 * @brief Initializes the TMR6 module. This routine must be called before any other timer routines.
 * @param None.
 * @return None.
 */
 void TMR6_Initialize(void);

/**
 * @ingroup tmr6
 * @brief Starts TMR6.
 * @pre The TMR6 should be initialized with TMR6_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void TMR6_Start(void);

/**
 * @ingroup tmr6
 * @brief Stops TMR6.
 * @pre The TMR6 should be initialized with TMR6_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void TMR6_Stop(void);

/**
 * @ingroup tmr6
 * @brief Reads the 8-bit from the TMR6 register.
 * @pre The TMR6 should be initialized with TMR6_Initialize() before calling this API.
 * @param None.
 * @return 8-bit data from the TMR6 register.
 */
uint8_t TMR6_Read(void);

/**
 * @ingroup tmr6
 * @brief Writes the 8-bit value to the TMR6 register.
 * @pre The TMR6 should be initialized with TMR6_Initialize() before calling this API.
 * @param timerVal - 8-bit value written to the TMR6 register.
 * @return None.
 */
void TMR6_Write(uint8_t timerVal);

/**
 * @ingroup tmr6
 * @brief Loads the 8-bit value to the PR6 register.
 * @pre The TMR6 should be initialized with TMR6_Initialize() before calling this API.
 * @param periodVal - 8-bit value written to the PR6 register.
 * @return None.
 */
void TMR6_PeriodCountSet(size_t periodVal);

/**
 * @ingroup tmr6
 * @brief Setter function for the TMR6 overflow callback.
 * @param CallbackHandler - Pointer to the custom callback.
 * @return None.
 */
void TMR6_OverflowCallbackRegister(void (* InterruptHandler)(void));

/**
 * @ingroup tmr6
 * @brief Performs the tasks to be executed on timer overflow event.
 * @param None.
 * @return None.
 */
void TMR6_Tasks(void);

#endif // TMR6_H
/**
 End of File
*/