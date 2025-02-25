/*
	Copyright 2025 Efabless Corp.


	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	    www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.

*/


/*! \file EF_TMR32.c
    \brief C file for TMR32 APIs which contains the function implmentations 
    
*/

#ifndef EF_TMR32_C
#define EF_TMR32_C

/******************************************************************************
* Includes
******************************************************************************/
#include "EF_TMR32.h"

/******************************************************************************
* File-Specific Macros and Constants
******************************************************************************/



/******************************************************************************
* Static Variables
******************************************************************************/



/******************************************************************************
* Static Function Prototypes
******************************************************************************/



/******************************************************************************
* Function Definitions
******************************************************************************/

EF_DRIVER_STATUS EF_TMR32_setGclkEnable(EF_TMR32_TYPE_PTR tmr32, uint32_t value) {
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else if (value > (uint32_t)0x1) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if value is out of valid range
    } else {
        tmr32->GCLK = value; // Set the GCLK enable bit to the provided value
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_enable(EF_TMR32_TYPE_PTR tmr32) {
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else {
        tmr32->CTRL |= EF_TMR32_CTRL_REG_TE_MASK; // Set the enable bit to 1
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_disable(EF_TMR32_TYPE_PTR tmr32) {
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else {
        tmr32->CTRL &= ~EF_TMR32_CTRL_REG_TE_MASK; // Clear the enable bit
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_restart(EF_TMR32_TYPE_PTR tmr32) {
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else {
        tmr32->CTRL |= EF_TMR32_CTRL_REG_TS_MASK;  // Set the restart bit
        tmr32->CTRL &= ~EF_TMR32_CTRL_REG_TS_MASK; // Clear the restart bit
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_PWM0Enable(EF_TMR32_TYPE_PTR tmr32) {
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else {
        tmr32->CTRL |= EF_TMR32_CTRL_REG_P0E_MASK; // Enable PWM0
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_PWM1Enable(EF_TMR32_TYPE_PTR tmr32) {
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else {
        tmr32->CTRL |= EF_TMR32_CTRL_REG_P1E_MASK; // Enable PWM1
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_PWMDeadtimeEnable(EF_TMR32_TYPE_PTR tmr32) {
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else {
        tmr32->CTRL |= EF_TMR32_CTRL_REG_DTE_MASK; // Enable dead-time
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_PWM0Invert(EF_TMR32_TYPE_PTR tmr32){
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else {
        tmr32->CTRL |= EF_TMR32_CTRL_REG_PI0_MASK; // Invert PWM0 output
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_PWM1Invert(EF_TMR32_TYPE_PTR tmr32) {
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else {
        tmr32->CTRL |= EF_TMR32_CTRL_REG_PI1_MASK; // Invert PWM1 output
    }

    return status;
}



EF_DRIVER_STATUS EF_TMR32_setUpCount(EF_TMR32_TYPE_PTR tmr32) {
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else {
        tmr32->CFG &= ~EF_TMR32_CFG_REG_DIR_MASK; // Clear the direction field
        tmr32->CFG |= (((uint32_t)0b10 << EF_TMR32_CFG_REG_DIR_BIT) & EF_TMR32_CFG_REG_DIR_MASK); // Set up-count direction
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setDownCount(EF_TMR32_TYPE_PTR tmr32) {
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else {
        tmr32->CFG &= ~EF_TMR32_CFG_REG_DIR_MASK; // Clear the direction field
        tmr32->CFG |= (((uint32_t)0b01 << EF_TMR32_CFG_REG_DIR_BIT) & EF_TMR32_CFG_REG_DIR_MASK); // Set down-count mode
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setUpDownCount(EF_TMR32_TYPE_PTR tmr32) {
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else {
        tmr32->CFG &= ~EF_TMR32_CFG_REG_DIR_MASK; // Clear the direction field
        tmr32->CFG |= (((uint32_t)0b11 << EF_TMR32_CFG_REG_DIR_BIT) & EF_TMR32_CFG_REG_DIR_MASK); // Set up-down-count mode
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setPeriodic(EF_TMR32_TYPE_PTR tmr32) {
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else {
        tmr32->CFG |= EF_TMR32_CFG_REG_P_MASK; // Enable periodic mode
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setOneShot(EF_TMR32_TYPE_PTR tmr32) {
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else {
        tmr32->CFG &= ~EF_TMR32_CFG_REG_P_MASK; // Disable periodic mode to set one-shot mode
    }

    return status;
}



EF_DRIVER_STATUS EF_TMR32_setPWM0MatchingZeroAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action){

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else if ((action > EF_TMR32_ACTION_MAX_VALUE)) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if value is out of valid range
    } else {
        // Clear the field bits in the register using the defined mask
        tmr32->PWM0CFG &= ~EF_TMR32_PWM0CFG_REG_E0_MASK;

        // Set the bits with the given value at the defined offset
        tmr32->PWM0CFG |= ((action << EF_TMR32_PWM0CFG_REG_E0_BIT) & EF_TMR32_PWM0CFG_REG_E0_MASK);
    }
    return status;
}


EF_DRIVER_STATUS EF_TMR32_setPWM0MatchingCMPXUpCountAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action) {

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else if ((action > EF_TMR32_ACTION_MAX_VALUE)) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if value is out of valid range
    } else {
        // Clear the field bits in the register using the defined mask
        tmr32->PWM0CFG &= ~EF_TMR32_PWM0CFG_REG_E1_MASK;

        // Set the bits with the given value at the defined offset
        tmr32->PWM0CFG |= ((action << EF_TMR32_PWM0CFG_REG_E1_BIT) & EF_TMR32_PWM0CFG_REG_E1_MASK);
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setPWM0MatchingCMPYUpCountAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action) {

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else if ((action > EF_TMR32_ACTION_MAX_VALUE)) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if value is out of valid range
    } else {
        // Clear the field bits in the register using the defined mask
        tmr32->PWM0CFG &= ~EF_TMR32_PWM0CFG_REG_E2_MASK;

        // Set the bits with the given value at the defined offset
        tmr32->PWM0CFG |= ((action << EF_TMR32_PWM0CFG_REG_E2_BIT) & EF_TMR32_PWM0CFG_REG_E2_MASK);
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setPWM0MatchingRELOADAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action) {

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else if ((action > EF_TMR32_ACTION_MAX_VALUE)) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if value is out of valid range
    } else {
        // Clear the field bits in the register using the defined mask
        tmr32->PWM0CFG &= ~EF_TMR32_PWM0CFG_REG_E3_MASK;

        // Set the bits with the given value at the defined offset
        tmr32->PWM0CFG |= ((action << EF_TMR32_PWM0CFG_REG_E3_BIT) & EF_TMR32_PWM0CFG_REG_E3_MASK);
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setPWM0MatchingCMPYDownCountAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action) {

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else if ((action > EF_TMR32_ACTION_MAX_VALUE)) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if value is out of valid range
    } else {
        // Clear the field bits in the register using the defined mask
        tmr32->PWM0CFG &= ~EF_TMR32_PWM0CFG_REG_E4_MASK;

        // Set the bits with the given value at the defined offset
        tmr32->PWM0CFG |= ((action << EF_TMR32_PWM0CFG_REG_E4_BIT) & EF_TMR32_PWM0CFG_REG_E4_MASK);
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setPWM0MatchingCMPXDownCountAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action) {

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else if ((action > EF_TMR32_ACTION_MAX_VALUE)) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if value is out of valid range
    } else {
        // Clear the field bits in the register using the defined mask
        tmr32->PWM0CFG &= ~EF_TMR32_PWM0CFG_REG_E5_MASK;

        // Set the bits with the given value at the defined offset
        tmr32->PWM0CFG |= ((action << EF_TMR32_PWM0CFG_REG_E5_BIT) & EF_TMR32_PWM0CFG_REG_E5_MASK);
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setPWM1MatchingZeroAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action) {

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else if ((action > EF_TMR32_ACTION_MAX_VALUE)) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if value is out of valid range
    } else {
        // Clear the field bits in the register using the defined mask
        tmr32->PWM1CFG &= ~EF_TMR32_PWM1CFG_REG_E0_MASK;

        // Set the bits with the given value at the defined offset
        tmr32->PWM1CFG |= ((action << EF_TMR32_PWM1CFG_REG_E0_BIT) & EF_TMR32_PWM1CFG_REG_E0_MASK);
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setPWM1MatchingCMPXUpCountingAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action) {

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else if ((action > EF_TMR32_ACTION_MAX_VALUE)) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if value is out of valid range
    } else {
        // Clear the field bits in the register using the defined mask
        tmr32->PWM1CFG &= ~EF_TMR32_PWM1CFG_REG_E1_MASK;

        // Set the bits with the given value at the defined offset
        tmr32->PWM1CFG |= ((action << EF_TMR32_PWM1CFG_REG_E1_BIT) & EF_TMR32_PWM1CFG_REG_E1_MASK);
    }

    return status;
}



EF_DRIVER_STATUS EF_TMR32_setPWM1MatchingCMPYUpCountingAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action) {

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else if ((action > EF_TMR32_ACTION_MAX_VALUE)) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if value is out of valid range
    } else {
        // Clear the field bits in the register using the defined mask
        tmr32->PWM1CFG &= ~EF_TMR32_PWM1CFG_REG_E2_MASK;

        // Set the bits with the given value at the defined offset
        tmr32->PWM1CFG |= ((action << EF_TMR32_PWM1CFG_REG_E2_BIT) & EF_TMR32_PWM1CFG_REG_E2_MASK);
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setPWM1MatchingRELOADAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action) {

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else if ((action > EF_TMR32_ACTION_MAX_VALUE)) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if value is out of valid range
    } else {
        // Clear the field bits in the register using the defined mask
        tmr32->PWM1CFG &= ~EF_TMR32_PWM1CFG_REG_E3_MASK;

        // Set the bits with the given value at the defined offset
        tmr32->PWM1CFG |= ((action << EF_TMR32_PWM1CFG_REG_E3_BIT) & EF_TMR32_PWM1CFG_REG_E3_MASK);
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setPWM1MatchingCMPYDownCountAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action) {

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else if ((action > EF_TMR32_ACTION_MAX_VALUE)) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if value is out of valid range
    } else {
        // Clear the field bits in the register using the defined mask
        tmr32->PWM1CFG &= ~EF_TMR32_PWM1CFG_REG_E4_MASK;

        // Set the bits with the given value at the defined offset
        tmr32->PWM1CFG |= ((action << EF_TMR32_PWM1CFG_REG_E4_BIT) & EF_TMR32_PWM1CFG_REG_E4_MASK);
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setPWM1MatchingCMPXDownCountAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action) {

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
    } else if ((action > EF_TMR32_ACTION_MAX_VALUE)) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if value is out of valid range
    } else {
        // Clear the field bits in the register using the defined mask
        tmr32->PWM1CFG &= ~EF_TMR32_PWM1CFG_REG_E5_MASK;

        // Set the bits with the given value at the defined offset
        tmr32->PWM1CFG |= ((action << EF_TMR32_PWM1CFG_REG_E5_BIT) & EF_TMR32_PWM1CFG_REG_E5_MASK);
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setRELOAD (EF_TMR32_TYPE_PTR tmr32, uint32_t value){

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL    
    } else {

        tmr32->RELOAD = value;
    }
    return status;

}



EF_DRIVER_STATUS EF_TMR32_setCMPX (EF_TMR32_TYPE_PTR tmr32, uint32_t value){

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL    
    } else {

        tmr32->CMPX = value;
    }

    return status;
}

EF_DRIVER_STATUS EF_TMR32_getCMPX (EF_TMR32_TYPE_PTR tmr32, uint32_t *value){

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL    
    } else if (value == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL    
    } else {
        *value = tmr32->CMPX;
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_getCMPY (EF_TMR32_TYPE_PTR tmr32, uint32_t *value){

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL    
    } else if (value == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL    
    } else {
        *value = tmr32->CMPY;
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setCMPY (EF_TMR32_TYPE_PTR tmr32, uint32_t value){

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL    
    } else {

        tmr32->CMPY = value;
    }

    return status;
}



EF_DRIVER_STATUS EF_TMR32_getTMR (EF_TMR32_TYPE_PTR tmr32, uint32_t* tmr_value){

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL    
    } else if (tmr_value == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer value pointer is NULL
    }else{
        *tmr_value = tmr32->TMR;
    }
    return status;

}


EF_DRIVER_STATUS EF_TMR32_setPWMDeadtime (EF_TMR32_TYPE_PTR tmr32, uint32_t value){

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL    
    } else if (value > EF_TMR32_PWMDT_MAX_VALUE) {

        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL   

    }else {
                tmr32->PWMDT = value;
    }
    return status;
}


EF_DRIVER_STATUS EF_TMR32_setPR(EF_TMR32_TYPE_PTR tmr32, uint32_t value){

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL    
    } else if (value > EF_TMR32_PR_MAX_VALUE) {

        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
        
    }else{
        tmr32->PR = value;
    }
 
    return status;
}


EF_DRIVER_STATUS EF_TMR32_getRIS(EF_TMR32_TYPE_PTR tmr32, uint32_t* RIS_value){
    
    EF_DRIVER_STATUS status = EF_DRIVER_OK; 

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;                // Return EF_DRIVER_ERROR_PARAMETER if tmr32 is NULL
    } else if (RIS_value == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;                // Return EF_DRIVER_ERROR_PARAMETER if RIS_value is NULL, 
                                                        // i.e. there is no memory location to store the value
    } else {
        *RIS_value = tmr32->RIS;
        
    }
    return status;
}

EF_DRIVER_STATUS EF_TMR32_getMIS(EF_TMR32_TYPE_PTR tmr32, uint32_t* MIS_value){
    
    EF_DRIVER_STATUS status = EF_DRIVER_OK; 

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;                // Return EF_DRIVER_ERROR_PARAMETER if tmr32 is NULL
    } else if (MIS_value == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;                // Return EF_DRIVER_ERROR_PARAMETER if MIS_value is NULL, 
                                                        // i.e. there is no memory location to store the value
    } else {
        *MIS_value = tmr32->MIS;
        
    }
    return status;
}

EF_DRIVER_STATUS EF_TMR32_setIM(EF_TMR32_TYPE_PTR tmr32, uint32_t mask){

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL    
    } else if (mask > EF_TMR32_IM_MAX_VALUE) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL   
    }else{
        tmr32->IM = mask;
    }
    return status;
}


EF_DRIVER_STATUS EF_TMR32_getIM(EF_TMR32_TYPE_PTR tmr32, uint32_t* IM_value){
    
    EF_DRIVER_STATUS status = EF_DRIVER_OK; 

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;                // Return EF_DRIVER_ERROR_PARAMETER if tmr32 is NULL
    } else if (IM_value == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;                // Return EF_DRIVER_ERROR_PARAMETER if IM_value is NULL, 
                                                        // i.e. there is no memory location to store the value
    } else {
        *IM_value = tmr32->IM;
        
    }
    return status;
}

EF_DRIVER_STATUS EF_TMR32_setICR(EF_TMR32_TYPE_PTR tmr32, uint32_t mask){

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL    
    } else if (mask > EF_TMR32_ICR_MAX_VALUE) {

        status = EF_DRIVER_ERROR_PARAMETER; // Return error if the timer pointer is NULL
        
    }else{
        tmr32->IC = mask;
    }
    return status;
}

EF_DRIVER_STATUS EF_TMR32_isTimout(EF_TMR32_TYPE_PTR tmr32, bool* timeout_status){
    
    EF_DRIVER_STATUS status = EF_DRIVER_OK; 

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;                // Return EF_DRIVER_ERROR_PARAMETER if tmr32 is NULL
    } else if (timeout_status == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;                // Return EF_DRIVER_ERROR_PARAMETER if timeout_status is NULL, 
                                                        // i.e. there is no memory location to store the value
    } else {
        uint32_t ris_value;
        status = EF_TMR32_getRIS(tmr32, &ris_value);
        if (status == EF_DRIVER_OK) {
            *timeout_status = (ris_value & EF_TMR32_TO_FLAG) ? true : false;
        }else{}
    }
    return status;
}

EF_DRIVER_STATUS EF_TMR32_isCMPXMatch(EF_TMR32_TYPE_PTR tmr32, bool* match_status){
    
    EF_DRIVER_STATUS status = EF_DRIVER_OK; 

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;                // Return EF_DRIVER_ERROR_PARAMETER if tmr32 is NULL
    } else if (match_status == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;                // Return EF_DRIVER_ERROR_PARAMETER if match_status is NULL, 
                                                        // i.e. there is no memory location to store the value
    } else {
        uint32_t ris_value;
        status = EF_TMR32_getRIS(tmr32, &ris_value);
        if (status == EF_DRIVER_OK) {
            *match_status = (ris_value & EF_TMR32_MX_FLAG) ? true : false;
        }else{}
    }
    return status;
}

EF_DRIVER_STATUS EF_TMR32_isCMPYMatch(EF_TMR32_TYPE_PTR tmr32, bool* match_status){

    EF_DRIVER_STATUS status = EF_DRIVER_OK; 

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;                // Return EF_DRIVER_ERROR_PARAMETER if tmr32 is NULL
    } else if (match_status == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;                // Return EF_DRIVER_ERROR_PARAMETER if match_status is NULL, 
                                                        // i.e. there is no memory location to store the value
    } else {
        uint32_t ris_value;
        status = EF_TMR32_getRIS(tmr32, &ris_value);
        if (status == EF_DRIVER_OK) {
            *match_status = (ris_value & EF_TMR32_MY_FLAG) ? true : false;
        }else{}
    }
    return status;
}


EF_DRIVER_STATUS EF_TMR32_clearTimoutFlag(EF_TMR32_TYPE_PTR tmr32){
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;
    } else {
        tmr32->IC |= EF_TMR32_TO_FLAG;
    }

    return status;
}

EF_DRIVER_STATUS EF_TMR32_clearCMPXMatchFlag(EF_TMR32_TYPE_PTR tmr32){
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;
    } else {
        tmr32->IC |= EF_TMR32_MX_FLAG;
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_clearCMPYMatchFlag(EF_TMR32_TYPE_PTR tmr32){
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;
    } else {
        tmr32->IC |= EF_TMR32_MY_FLAG;
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setPWM0EdgeAlignmentMode(EF_TMR32_TYPE_PTR tmr32, uint32_t reload_value, uint32_t duty_cycle){
    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;
    }else if (duty_cycle > 100) {
        status = EF_DRIVER_ERROR_PARAMETER;

    } else{

        // set the timer to up-count mode
        // set the timer to periodic mode
        // set the zero action to high
        // only use one compare register
        // set the action of the X Compare register up count to low
        // set the action of the Y Compare register up count to no change
        // calculate the X compare register value given the duty cycle
        // set the reload value
        // set X compare register value
        // set the top action to no change

        //  |
        //  |       /|      /|
        //  |_____/__|____/  |
        //  |   / |  |  / |  |
        //  |_/___|__|/___|__|____
        //        |       |
        //        V       V
        //    ____    ____    ___   ___
        //        |__|    |__|   |__|
        //    duty    duty
        //    cycle   cycle


        status = EF_TMR32_setUpCount(tmr32);
        
        if (status == EF_DRIVER_OK) {
            uint32_t cmpY;
            status = EF_TMR32_getCMPY(tmr32, &cmpY);
            if (cmpY == (uint32_t)0) {
                status = EF_TMR32_setCMPY(tmr32, (uint32_t)10); // Set CMPX to a dummy value to prevent the timer from firing two concurrent interrupts
            } else {}
        }else{}

        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPeriodic(tmr32);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPWM0MatchingZeroAction(tmr32, EF_TMR32_ACTION_HIGH);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPWM0MatchingCMPXUpCountAction(tmr32, EF_TMR32_ACTION_LOW);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPWM0MatchingCMPYUpCountAction(tmr32, EF_TMR32_ACTION_NONE);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPWM0MatchingRELOADAction(tmr32, EF_TMR32_ACTION_NONE);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setRELOAD(tmr32, reload_value);}else{}

        if (status == EF_DRIVER_OK){
            uint32_t compare_value = (duty_cycle * reload_value) / 100;
            status = EF_TMR32_setCMPX(tmr32, compare_value);  
        }else{}
        
    }
    return status;
}

EF_DRIVER_STATUS EF_TMR32_setPWM1EdgeAlignmentMode(EF_TMR32_TYPE_PTR tmr32, uint32_t reload_value,uint32_t duty_cycle){

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;
    } else if (duty_cycle > 100) {
        status = EF_DRIVER_ERROR_PARAMETER;

    } else {

        // set the timer to up-count mode
        // set the timer to periodic mode
        // set the zero action to high
        // only use one compare register
        // set the action of the Y Compare register up count to low
        // set the action of the X Compare register up count to no change
        // calculate the Y compare register value given the duty cycle
        // set the reload value
        // set the Y compare register value
        // set the top action to no change

        //  |
        //  |       /|      /|
        //  |_____/__|____/  |
        //  |   / |  |  / |  |
        //  |_/___|__|/___|__|____
        //        |       |
        //        V       V
        //    ____    ____    ___   ___
        //        |__|    |__|   |__|
        //    duty    duty
        //    cycle   cycle

        status = EF_TMR32_setUpCount(tmr32);

        if (status == EF_DRIVER_OK) {
            uint32_t cmpX;
            status = EF_TMR32_getCMPX(tmr32, &cmpX);
            if (cmpX == (uint32_t)0) {
                status = EF_TMR32_setCMPX(tmr32, (uint32_t)10); // Set CMPX to a dummy value to prevent the timer from firing two concurrent interrupts
            } else {}
        }else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPeriodic(tmr32);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPWM1MatchingZeroAction(tmr32, EF_TMR32_ACTION_HIGH);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPWM1MatchingCMPYUpCountingAction(tmr32, EF_TMR32_ACTION_LOW);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPWM1MatchingCMPXUpCountingAction(tmr32, EF_TMR32_ACTION_NONE);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPWM1MatchingRELOADAction(tmr32, EF_TMR32_ACTION_NONE);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setRELOAD(tmr32, reload_value);}else{}

        if (status == EF_DRIVER_OK){
            uint32_t compare_value = (duty_cycle * reload_value) / 100;
            status = EF_TMR32_setCMPY(tmr32, compare_value);  
        }else{}
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setPWM0CenterAlignedMode(EF_TMR32_TYPE_PTR tmr32, uint32_t reload_value, uint32_t cmpX_value){

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;
    }else if (reload_value < cmpX_value){
        status = EF_DRIVER_ERROR_PARAMETER;
    } else {

        // set the timer to up-down-count mode
        // set the timer to periodic mode
        // set the zero action to high
        // set the action of the X Compare register up count to low
        // set the action of the Y Compare register up count to no change
        // set the action of the X Compare register down count to high
        // set the action of the Y Compare register down count to no change
        // set the top action to no change
        // set the reload value
        // set the X compare value


        //  |
        //  |       /|\
        //  |_____/__|__\
        //  |   / |  |  | \
        //  |_/___|__|__|___\__
        //        |     |
        //        V     V
        //    ____       ____ 
        //        |_____|    

        status = EF_TMR32_setUpDownCount(tmr32);

        if (status == EF_DRIVER_OK) {
            uint32_t cmpY;
            status = EF_TMR32_getCMPY(tmr32, &cmpY);
            if (cmpY == (uint32_t)0) {
                status = EF_TMR32_setCMPY(tmr32, (uint32_t)10); // Set CMPX to a dummy value to prevent the timer from firing two concurrent interrupts
            } else {}
        }else{}

        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPeriodic(tmr32);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPWM0MatchingZeroAction(tmr32, EF_TMR32_ACTION_HIGH);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPWM0MatchingCMPXUpCountAction(tmr32, EF_TMR32_ACTION_LOW);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPWM0MatchingCMPYUpCountAction(tmr32, EF_TMR32_ACTION_NONE);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPWM0MatchingCMPXDownCountAction(tmr32, EF_TMR32_ACTION_HIGH);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPWM0MatchingCMPYDownCountAction(tmr32, EF_TMR32_ACTION_NONE);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setPWM0MatchingRELOADAction(tmr32, EF_TMR32_ACTION_NONE);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setRELOAD(tmr32, reload_value);}else{}
        if (status == EF_DRIVER_OK){ status = EF_TMR32_setCMPX(tmr32, cmpX_value);}else{}
        
    }

    return status;
}


EF_DRIVER_STATUS EF_TMR32_setPWM1CenterAlignedMode(EF_TMR32_TYPE_PTR tmr32, uint32_t reload_value, uint32_t cmpY_value){

    EF_DRIVER_STATUS status = EF_DRIVER_OK;

    if (tmr32 == NULL) {
        status = EF_DRIVER_ERROR_PARAMETER;
    } else {
        // set the timer to up-down-count mode
        // set the timer to periodic mode
        // set the zero action to high
        // set the action of the Y Compare register up count to low
        // set the action of the X Compare register up count to no change
        // set the action of the Y Compare register down count to high
        // set the action of the X Compare register down count to no change
        // set the top action to no change
        // set the reload value
        // set the Y compare value

        //  |
        //  |       /|\
        //  |_____/__|__\
        //  |   / |  |  | \
        //  |_/___|__|__|___\__
        //        |     |
        //        V     V
        //    ____       ____ 
        //        |_____|

        status = EF_TMR32_setUpDownCount(tmr32);

        if (status == EF_DRIVER_OK) {
            uint32_t cmpX;
            status = EF_TMR32_getCMPX(tmr32, &cmpX);
            if (cmpX == (uint32_t)0) {
                status = EF_TMR32_setCMPX(tmr32, (uint32_t)10); // Set CMPX to a dummy value to prevent the timer from firing two concurrent interrupts
            } else {}
        }else{}
        if (status == EF_DRIVER_OK) {status = EF_TMR32_setPeriodic(tmr32);}else{}
        if (status == EF_DRIVER_OK) {status = EF_TMR32_setPWM1MatchingZeroAction(tmr32, EF_TMR32_ACTION_HIGH);}else{}
        if (status == EF_DRIVER_OK) {status = EF_TMR32_setPWM1MatchingCMPYUpCountingAction(tmr32, EF_TMR32_ACTION_LOW);}else{}
        if (status == EF_DRIVER_OK) {status = EF_TMR32_setPWM1MatchingCMPXUpCountingAction(tmr32, EF_TMR32_ACTION_NONE);}else{}
        if (status == EF_DRIVER_OK) {status = EF_TMR32_setPWM1MatchingCMPYDownCountAction(tmr32, EF_TMR32_ACTION_HIGH);}else{}
        if (status == EF_DRIVER_OK) {status = EF_TMR32_setPWM1MatchingCMPXDownCountAction(tmr32, EF_TMR32_ACTION_NONE);}else{}
        if (status == EF_DRIVER_OK) {status = EF_TMR32_setPWM1MatchingRELOADAction(tmr32, EF_TMR32_ACTION_NONE);}else{}
        if (status == EF_DRIVER_OK) {status = EF_TMR32_setRELOAD(tmr32, reload_value);}else{}
        if (status == EF_DRIVER_OK) {status = EF_TMR32_setCMPY(tmr32, cmpY_value);}else{}


    }
    return status;
}



/******************************************************************************
* Static Function Definitions
******************************************************************************/


#endif // EF_TMR32_C

/******************************************************************************
* End of File
******************************************************************************/
