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


/*! \file EF_TMR32.h
    \brief C header file for TMR32 APIs which contains the function prototypes 
    
*/
#ifndef EF_TMR32_H
#define EF_TMR32_H

/******************************************************************************
* Includes
******************************************************************************/
#include "EF_Driver_Common.h"


/******************************************************************************
* Macros and Constants
******************************************************************************/

#define EF_TMR32_CTRL_REG_TE_BIT	    (uint32_t)(0)
#define EF_TMR32_CTRL_REG_TE_MASK	    (uint32_t)(0x1)
#define EF_TMR32_CTRL_REG_TS_BIT	    (uint32_t)(1)
#define EF_TMR32_CTRL_REG_TS_MASK	    (uint32_t)(0x2)
#define EF_TMR32_CTRL_REG_P0E_BIT	    (uint32_t)(2)
#define EF_TMR32_CTRL_REG_P0E_MASK	    (uint32_t)(0x4)
#define EF_TMR32_CTRL_REG_P1E_BIT	    (uint32_t)(3)
#define EF_TMR32_CTRL_REG_P1E_MASK	    (uint32_t)(0x8)
#define EF_TMR32_CTRL_REG_DTE_BIT	    (uint32_t)(4)
#define EF_TMR32_CTRL_REG_DTE_MASK	    (uint32_t)(0x10)
#define EF_TMR32_CTRL_REG_PI0_BIT	    (uint32_t)(5)
#define EF_TMR32_CTRL_REG_PI0_MASK	    (uint32_t)(0x20)
#define EF_TMR32_CTRL_REG_PI1_BIT	    (uint32_t)(6)
#define EF_TMR32_CTRL_REG_PI1_MASK	    (uint32_t)(0x40)
#define EF_TMR32_CFG_REG_DIR_BIT	    (uint32_t)(0)
#define EF_TMR32_CFG_REG_DIR_MASK	    (uint32_t)(0x3)
#define EF_TMR32_CFG_REG_P_BIT	        (uint32_t)(2)
#define EF_TMR32_CFG_REG_P_MASK	        (uint32_t)(0x4)
#define EF_TMR32_PWM0CFG_REG_E0_BIT	    (uint32_t)(0)
#define EF_TMR32_PWM0CFG_REG_E0_MASK	(uint32_t)(0x3)
#define EF_TMR32_PWM0CFG_REG_E1_BIT	    (uint32_t)(2)
#define EF_TMR32_PWM0CFG_REG_E1_MASK	(uint32_t)(0xc)
#define EF_TMR32_PWM0CFG_REG_E2_BIT	    (uint32_t)(4)
#define EF_TMR32_PWM0CFG_REG_E2_MASK	(uint32_t)(0x30)
#define EF_TMR32_PWM0CFG_REG_E3_BIT	    (uint32_t)(6)
#define EF_TMR32_PWM0CFG_REG_E3_MASK	(uint32_t)(0xc0)
#define EF_TMR32_PWM0CFG_REG_E4_BIT	    (uint32_t)(8)
#define EF_TMR32_PWM0CFG_REG_E4_MASK	(uint32_t)(0x300)
#define EF_TMR32_PWM0CFG_REG_E5_BIT	    (uint32_t)(10)
#define EF_TMR32_PWM0CFG_REG_E5_MASK	(uint32_t)(0xc00)
#define EF_TMR32_PWM1CFG_REG_E0_BIT	    (uint32_t)(0)
#define EF_TMR32_PWM1CFG_REG_E0_MASK	(uint32_t)(0x3)
#define EF_TMR32_PWM1CFG_REG_E1_BIT	    (uint32_t)(2)
#define EF_TMR32_PWM1CFG_REG_E1_MASK	(uint32_t)(0xc)
#define EF_TMR32_PWM1CFG_REG_E2_BIT	    (uint32_t)(4)
#define EF_TMR32_PWM1CFG_REG_E2_MASK	(uint32_t)(0x30)
#define EF_TMR32_PWM1CFG_REG_E3_BIT	    (uint32_t)(6)
#define EF_TMR32_PWM1CFG_REG_E3_MASK	(uint32_t)(0xc0)
#define EF_TMR32_PWM1CFG_REG_E4_BIT	    (uint32_t)(8)
#define EF_TMR32_PWM1CFG_REG_E4_MASK	(uint32_t)(0x300)
#define EF_TMR32_PWM1CFG_REG_E5_BIT	    (uint32_t)(10)
#define EF_TMR32_PWM1CFG_REG_E5_MASK	(uint32_t)(0xc00)

#define EF_TMR32_TO_FLAG	            ((uint32_t)0x1)
#define EF_TMR32_MX_FLAG	            ((uint32_t)0x2)
#define EF_TMR32_MY_FLAG	            ((uint32_t)0x4)


#define EF_TMR32_ACTION_NONE    ((uint32_t)0)   //!< No action on match (do nothing)
#define EF_TMR32_ACTION_LOW     ((uint32_t)1)   //!< Set output to LOW when match occurs
#define EF_TMR32_ACTION_HIGH    ((uint32_t)2)   //!< Set output to HIGH when match occurs
#define EF_TMR32_ACTION_INVERT  ((uint32_t)3)   //!< Invert the output when match occurs

#define EF_TMR32_ACTION_MAX_VALUE  ((uint32_t)3)    //!< Maximum value for the action field

#define EF_TMR32_PWMDT_MAX_VALUE    ((uint32_t)0x000000FF)  //!< Maximum value for the deadtime register
#define EF_TMR32_PR_MAX_VALUE       ((uint32_t)0x0000FFFF)  //!< Maximum value for the PR register
#define EF_TMR32_IM_MAX_VALUE       ((uint32_t)7)           //!< Maximum value for the IM register
#define EF_TMR32_ICR_MAX_VALUE      ((uint32_t)7)           //!< Maximum value for the ICR register


/******************************************************************************
* Typedefs and Enums
******************************************************************************/
typedef struct _EF_TMR32_TYPE_ {
	__R 	TMR;
	__W 	RELOAD;
	__W 	PR;
	__W 	CMPX;
	__W 	CMPY;
	__W 	CTRL;
	__W 	CFG;
	__W 	PWM0CFG;
	__W 	PWM1CFG;
	__W 	PWMDT;
	__W 	PWMFC;
	__R 	reserved_0[16309];
	__RW	IM;
	__R 	MIS;
	__R 	RIS;
	__W 	IC;
	__W 	GCLK;
} EF_TMR32_TYPE;


typedef EF_TMR32_TYPE* EF_TMR32_TYPE_PTR;



/******************************************************************************
* Function Prototypes
******************************************************************************/

//! Sets the GCLK enable bit in the GCLK register to a certain value
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        \param [in] value The value of the GCLK enable bit
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setGclkEnable(EF_TMR32_TYPE_PTR tmr32, uint32_t value);

//! Enables timer by setting "TE" bit in the CTRL register to 1 
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_enable(EF_TMR32_TYPE_PTR tmr32);


//! Disables timer by setting "TE" bit in the CTRL register to 0 
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_disable(EF_TMR32_TYPE_PTR tmr32);


//! Enables timer re-start; used in the one-shot mode to restart the timer by setting the "TS" bit in the CTRL register to 1 and then to 0
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_restart(EF_TMR32_TYPE_PTR tmr32);

//! Enables PWM0 by setting "P0E" bit in the CTRL register to 1 
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_PWM0Enable(EF_TMR32_TYPE_PTR tmr32);

//! Enables PWM1 by setting "P1E" bit in the CTRL register to 1 
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_PWM1Enable(EF_TMR32_TYPE_PTR tmr32);

//! Enables PWM dead-time by setting the "DTE" (Dead-Time Enable) bit in the CTRL register to 1.
//! Dead-time is a critical feature in PWM signal generation used to ensure a safe period between switching the high and low states, 
//! preventing short circuits or other issues in systems with complementary outputs, such as H-bridge drivers.
//! When enabled, the "DTE" bit introduces a fixed delay between the switching of PWM channels to allow for this safety margin.
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_PWMDeadtimeEnable(EF_TMR32_TYPE_PTR tmr32);

//! Inverts PWM0 output by setting "P0I" bit in the CTRL register to 1 
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_PWM0Invert(EF_TMR32_TYPE_PTR tmr32);

//! Inverts PWM1 output by setting "P1I" bit in the CTRL register to 1 
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_PWM1Invert(EF_TMR32_TYPE_PTR tmr32);

//! Sets the timer direction to be up counting by setting the "DIR" field in the CTRL register to 0b10
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setUpCount(EF_TMR32_TYPE_PTR tmr32);

//! Sets the timer direction to be down counting by setting the "DIR" field in the CTRL register to 0b01
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setDownCount(EF_TMR32_TYPE_PTR tmr32);

//! Sets the timer direction to be up/down counting by setting the "DIR" field in the CTRL register to 0b11
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setUpDownCount(EF_TMR32_TYPE_PTR tmr32);

//! Sets the timer to operate in periodic mode by setting the "P" bit in the CFG register to 1
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setPeriodic(EF_TMR32_TYPE_PTR tmr32);

//! Sets the timer to operate in one-shot mode by clearing the "P" bit in the CFG register to 0
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setOneShot(EF_TMR32_TYPE_PTR tmr32);

//! Configures the action of TMR0 PWM when the timer matches the Zero value.
//! This function allows the user to specify what happens to the PWM output signal when the timer counter reaches zero. 
//! The available actions are: no action, set the output to LOW, set the output to HIGH, or invert the current state of the output.
//! The action is configured in the PWM0 configuration register by modifying \ref EF_TMR32_PWM0CFG_REG_E0_BIT.
//! This is commonly used in PWM applications to define the output response when the counter reaches a particular value.
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        \param [in] action A uint32_t value specifying the action to take when the timer matches the Zero value. The possible values are:
        - \ref EF_TMR32_ACTION_NONE: No action (do nothing)
        - \ref EF_TMR32_ACTION_LOW: Set the PWM output to LOW
        - \ref EF_TMR32_ACTION_HIGH: Set the PWM output to HIGH
        - \ref EF_TMR32_ACTION_INVERT: Invert the current output state
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setPWM0MatchingZeroAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action);

//! Configures the action of TMR0 PWM when the timer matches the CMPX value while up counting.
//! This function allows the user to specify what happens to the PWM output signal when the timer counter matches the CMPX value while counting up.
//! The available actions are: no action, set the output to LOW, set the output to HIGH, or invert the current state of the output.
//! The action is configured in the PWM0 configuration register by modifying \ref EF_TMR32_PWM0CFG_REG_E1_BI.
//! This is commonly used in PWM applications to define the output response when the counter reaches a particular value.
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        \param [in] action A uint32_t value specifying the action to take when the timer matches the CMPX value while counting up. The possible values are:
        - \ref EF_TMR32_ACTION_NONE: No action (do nothing)
        - \ref EF_TMR32_ACTION_LOW: Set the PWM output to LOW
        - \ref EF_TMR32_ACTION_HIGH: Set the PWM output to HIGH
        - \ref EF_TMR32_ACTION_INVERT: Invert the current output state
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setPWM0MatchingCMPXUpCountAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action);

//! Configures the action of TMR0 PWM when the timer matches the CMPY value while up counting.
//! This function allows the user to specify what happens to the PWM output signal when the timer counter matches the CMPY value while counting up.
//! The available actions are: no action, set the output to LOW, set the output to HIGH, or invert the current state of the output.
//! The action is configured in the PWM0 configuration register by modifying \ref EF_TMR32_PWM0CFG_REG_E2_BI.
//! This is commonly used in PWM applications to define the output response when the counter reaches a particular value.
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        \param [in] action A uint32_t value specifying the action to take when the timer matches the CMPY value while counting up. The possible values are:
        - \ref EF_TMR32_ACTION_NONE: No action (do nothing)
        - \ref EF_TMR32_ACTION_LOW: Set the PWM output to LOW
        - \ref EF_TMR32_ACTION_HIGH: Set the PWM output to HIGH
        - \ref EF_TMR32_ACTION_INVERT: Invert the current output state
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setPWM0MatchingCMPYUpCountAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action);

//! Configures the action of TMR0 PWM when the timer matches the RELOAD value.
//! This function allows the user to specify what happens to the PWM output signal when the timer counter matches the RELOAD value.
//! The available actions are: no action, set the output to LOW, set the output to HIGH, or invert the current state of the output.
//! The action is configured in the PWM0 configuration register by modifying \ref EF_TMR32_PWM0CFG_REG_E3_BI.
//! This is commonly used in PWM applications to define the output response when the counter reaches a particular value.
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        \param [in] action A uint32_t value specifying the action to take when the timer matches the RELOAD value. The possible values are:
        - \ref EF_TMR32_ACTION_NONE: No action (do nothing)
        - \ref EF_TMR32_ACTION_LOW: Set the PWM output to LOW
        - \ref EF_TMR32_ACTION_HIGH: Set the PWM output to HIGH
        - \ref EF_TMR32_ACTION_INVERT: Invert the current output state
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setPWM0MatchingRELOADAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action);

//! Configures the action of TMR0 PWM when the timer matches the CMPY value while down counting.
//! This function allows the user to specify what happens to the PWM output signal when the timer counter matches the CMPY value while counting down.
//! The available actions are: no action, set the output to LOW, set the output to HIGH, or invert the current state of the output.
//! The action is configured in the PWM0 configuration register by modifying \ref EF_TMR32_PWM0CFG_REG_E4_BI.
//! This is commonly used in PWM applications to define the output response when the counter reaches a particular
//! value.
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        \param [in] action A uint32_t value specifying the action to take when the timer matches the CMPY value while counting down. The possible values are:
        - \ref EF_TMR32_ACTION_NONE: No action (do nothing)
        - \ref EF_TMR32_ACTION_LOW: Set the PWM output to LOW
        - \ref EF_TMR32_ACTION_HIGH: Set the PWM output to HIGH
        - \ref EF_TMR32_ACTION_INVERT: Invert the current output state
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setPWM0MatchingCMPYDownCountAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action);

//! Configures the action of TMR0 PWM when the timer matches the CMPX value while down counting.
//! This function allows the user to specify what happens to the PWM output signal when the timer counter matches the CMPX value while counting down.
//! The available actions are: no action, set the output to LOW, set the output to HIGH, or invert the current state of the output.
//! The action is configured in the PWM0 configuration register by modifying \ref EF_TMR32_PWM0CFG_REG_E5_BI.
//! This is commonly used in PWM applications to define the output response when the counter reaches a particular value.
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        \param [in] action A uint32_t value specifying the action to take when the timer matches the CMPX value while counting down. The possible values are:
        - \ref EF_TMR32_ACTION_NONE: No action (do nothing)
        - \ref EF_TMR32_ACTION_LOW: Set the PWM output to LOW
        - \ref EF_TMR32_ACTION_HIGH: Set the PWM output to HIGH
        - \ref EF_TMR32_ACTION_INVERT: Invert the current output state
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setPWM0MatchingCMPXDownCountAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action);

//! Configures the action of TMR1 PWM when the timer matches the Zero value.
//! This function allows the user to specify what happens to the PWM output signal when the timer counter reaches zero.
//! The available actions are: no action, set the output to LOW, set the output to HIGH, or invert the current state of the output.
//! The action is configured in the PWM1 configuration register by modifying \ref EF_TMR32_PWM1CFG_REG_E0_BIT.
//! This is commonly used in PWM applications to define the output response when the counter reaches a particular value.
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        \param [in] action A uint32_t value specifying the action to take when the timer matches the Zero value. The possible values are:
        - \ref EF_TMR32_ACTION_NONE: No action (do nothing)
        - \ref EF_TMR32_ACTION_LOW: Set the PWM output to LOW
        - \ref EF_TMR32_ACTION_HIGH: Set the PWM output to HIGH
        - \ref EF_TMR32_ACTION_INVERT: Invert the current output state
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setPWM1MatchingZeroAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action);

//! Configures the action of TMR1 PWM when the timer matches the CMPX value while up counting.
//! This function allows the user to specify what happens to the PWM output signal when the timer counter matches the CMPX value while counting up.
//! The available actions are: no action, set the output to LOW, set the output to HIGH, or invert the current state of the output.
//! The action is configured in the PWM1 configuration register by modifying \ref EF_TMR32_PWM1CFG_REG_E1_BI.
//! This is commonly used in PWM applications to define the output response when the counter reaches a particular value.
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        \param [in] action A uint32_t value specifying the action to take when the timer matches the CMPX value while counting up. The possible values are:
        - \ref EF_TMR32_ACTION_NONE: No action (do nothing)
        - \ref EF_TMR32_ACTION_LOW: Set the PWM output to LOW
        - \ref EF_TMR32_ACTION_HIGH: Set the PWM output to HIGH
        - \ref EF_TMR32_ACTION_INVERT: Invert the current output state
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setPWM1MatchingCMPXUpCountingAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action);

//! Configures the action of TMR1 PWM when the timer matches the CMPY value while up counting.
//! This function allows the user to specify what happens to the PWM output signal when the timer counter matches the CMPY value while counting up.
//! The available actions are: no action, set the output to LOW, set the output to HIGH, or invert the current state of the output.
//! The action is configured in the PWM1 configuration register by modifying \ref EF_TMR32_PWM1CFG_REG_E2_BI.
//! This is commonly used in PWM applications to define the output response when the counter reaches a particular value.
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        \param [in] action A uint32_t value specifying the action to take when the timer matches the CMPY value while counting up. The possible values are:
        - \ref EF_TMR32_ACTION_NONE: No action (do nothing)
        - \ref EF_TMR32_ACTION_LOW: Set the PWM output to LOW
        - \ref EF_TMR32_ACTION_HIGH: Set the PWM output to HIGH
        - \ref EF_TMR32_ACTION_INVERT: Invert the current output state
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setPWM1MatchingCMPYUpCountingAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action);

//! Configures the action of TMR1 PWM when the timer matches the RELOAD value.
//! This function allows the user to specify what happens to the PWM output signal when the timer counter matches the RELOAD value.
//! The available actions are: no action, set the output to LOW, set the output to HIGH, or invert the current state of the output.
//! The action is configured in the PWM1 configuration register by modifying \ref EF_TMR32_PWM1CFG_REG_E3_BI.
//! This is commonly used in PWM applications to define the output response when the counter reaches a particular value.
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        \param [in] action A uint32_t value specifying the action to take when the timer matches the RELOAD value. The possible values are:
        - \ref EF_TMR32_ACTION_NONE: No action (do nothing)
        - \ref EF_TMR32_ACTION_LOW: Set the PWM output to LOW
        - \ref EF_TMR32_ACTION_HIGH: Set the PWM output to HIGH
        - \ref EF_TMR32_ACTION_INVERT: Invert the current output state
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setPWM1MatchingRELOADAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action);

//! Configures the action of TMR1 PWM when the timer matches the CMPY value while down counting.
//! This function allows the user to specify what happens to the PWM output signal when the timer counter matches the CMPY value while counting down.
//! The available actions are: no action, set the output to LOW, set the output to HIGH, or invert the current state of the output.
//! The action is configured in the PWM1 configuration register by modifying \ref EF_TMR32_PWM1CFG_REG_E4_BI.
//! This is commonly used in PWM applications to define the output response when the counter reaches a particular value.
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        \param [in] action A uint32_t value specifying the action to take when the timer matches the CMPY value while counting down. The possible values are:
        - \ref EF_TMR32_ACTION_NONE: No action (do nothing)
        - \ref EF_TMR32_ACTION_LOW: Set the PWM output to LOW
        - \ref EF_TMR32_ACTION_HIGH: Set the PWM output to HIGH
        - \ref EF_TMR32_ACTION_INVERT: Invert the current output state
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setPWM1MatchingCMPYDownCountAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action);

//! Configures the action of TMR1 PWM when the timer matches the CMPX value while down counting.
//! This function allows the user to specify what happens to the PWM output signal when the timer counter matches the CMPX value while counting down.
//! The available actions are: no action, set the output to LOW, set the output to HIGH, or invert the current state of the output.
//! The action is configured in the PWM1 configuration register by modifying \ref EF_TMR32_PWM1CFG_REG_E5_BI.
//! This is commonly used in PWM applications to define the output response when the counter reaches a particular value.
    /*!
        \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR , which points to the base memory address of TMR32 registers. \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
        \param [in] action A uint32_t value specifying the action to take when the timer matches the CMPX value while counting down. The possible values are:
        - \ref EF_TMR32_ACTION_NONE: No action (do nothing)
        - \ref EF_TMR32_ACTION_LOW: Set the PWM output to LOW
        - \ref EF_TMR32_ACTION_HIGH: Set the PWM output to HIGH
        - \ref EF_TMR32_ACTION_INVERT: Invert the current output state
        
        \return status A value of type \ref EF_DRIVER_STATUS : returns a success or error code 
    */
EF_DRIVER_STATUS EF_TMR32_setPWM1MatchingCMPXDownCountAction(EF_TMR32_TYPE_PTR tmr32, uint32_t action);

//! Sets the reload value of a 32-bit timer by writing to the RELOAD register.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [in] value The reload value to set in the RELOAD register.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_setRELOAD (EF_TMR32_TYPE_PTR tmr32, uint32_t value);


//! Sets the compare value of a 32-bit timer by writing to the CMPX register.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [in] value The compare value to set in the CMPX register.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_setCMPX (EF_TMR32_TYPE_PTR tmr32, uint32_t value);


//! Retrieves the compare value X of a 32-bit timer by reading the CMPX register.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [out] value A pointer to a uint32_t where the compare value will be stored.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_getCMPX (EF_TMR32_TYPE_PTR tmr32, uint32_t *value);


//! Retrieves the compare value Y of a 32-bit timer by reading the CMPY register.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [out] value A pointer to a uint32_t where the compare value will be stored.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_getCMPY (EF_TMR32_TYPE_PTR tmr32, uint32_t *value);

//! Sets the compare value Y of a 32-bit timer by writing to the CMPY register.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [in] value The compare value to set in the CMPY register.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_setCMPY (EF_TMR32_TYPE_PTR tmr32, uint32_t value);


//! Retrieves the current timer value by reading the TMR register.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [out] tmr_value A pointer to a uint32_t where the timer value will be stored.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_getTMR (EF_TMR32_TYPE_PTR tmr32, uint32_t* tmr_value);

//! Sets the PWM dead time value of the PWM by writing to the PWMDT register.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [in] value The dead time value to set in the PWMDT register. 
                      Must not exceed \ref EF_TMR32_PWMDT_MAX_VALUE.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_setPWMDeadtime (EF_TMR32_TYPE_PTR tmr32, uint32_t value);

//! Sets the prescaler value of the timer by writing to the PR register.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [in] value The prescaler value to set in the PR register. 
                      Must not exceed \ref EF_TMR32_PR_MAX_VALUE.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_setPR(EF_TMR32_TYPE_PTR tmr32, uint32_t value);


//! Retrieves the raw interrupt status by reading the RIS register.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [out] RIS_value A pointer to a uint32_t where the raw interrupt status value will be stored.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_getRIS(EF_TMR32_TYPE_PTR tmr32, uint32_t* RIS_value);


//! Retrieves the masked interrupt status by reading the MIS register.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [out] MIS_value A pointer to a uint32_t where the masked interrupt status value will be stored.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_getMIS(EF_TMR32_TYPE_PTR tmr32, uint32_t* MIS_value);

//! Sets the interrupt mask of the timer by writing to the IM register.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [in] mask The interrupt mask value to set in the IM register. 
                     Must not exceed \ref EF_TMR32_IM_MAX_VALUE.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_setIM(EF_TMR32_TYPE_PTR tmr32, uint32_t mask);



//! Retrieves the interrupt clear register by reading the ICR register.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [out] IM_value A pointer to a uint32_t where the interrupt clear value will be stored.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_getIM(EF_TMR32_TYPE_PTR tmr32, uint32_t* IM_value);


//! Sets the interrupt clear register of the timer by writing to the ICR register.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [in] mask The interrupt clear mask value to set in the ICR register. 
                     Must not exceed \ref EF_TMR32_ICR_MAX_VALUE.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_setICR(EF_TMR32_TYPE_PTR tmr32, uint32_t mask);

//! Checks if the timer has reached the RELOAD value if up counting or zero if down counting by reading the RIS register and checking the RT flag.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [out] timeout_status A pointer to a uint32_t where the timeout status will be stored.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_isTimout(EF_TMR32_TYPE_PTR tmr32, bool* timeout_status);

//! Checks if the timer has reached the CMPX value by reading the RIS register and checking the MX flag.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [out] match_status A pointer to a uint32_t where the match status will be stored.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_isCMPXMatch(EF_TMR32_TYPE_PTR tmr32, bool* match_status);


//! Checks if the timer has reached the CMPY value by reading the RIS register and checking the MY flag.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [out] match_status A pointer to a uint32_t where the match status will be stored.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_isCMPYMatch(EF_TMR32_TYPE_PTR tmr32, bool* match_status);

//! Clears the timeout flag by writing to the ICR register and setting the TO bit.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_clearTimoutFlag(EF_TMR32_TYPE_PTR tmr32);


//! Clears the CMPX match flag by writing to the ICR register and setting the MX bit.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_clearCMPXMatchFlag(EF_TMR32_TYPE_PTR tmr32);

//! Clears the CMPY match flag by writing to the ICR register and setting the MY bit.
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    
    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
*/
EF_DRIVER_STATUS EF_TMR32_clearCMPYMatchFlag(EF_TMR32_TYPE_PTR tmr32);


//! Sets the PWM0 edge alignment mode 
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [in] reload_value The reload value to set in the PWM0CFG register. This determines the period of the PWM signal.
    \param [in] duty_cycle The duty cycle value to set in the PWM0CFG register, representing the high time as a percentage 
                           of the period (0 to 100).

    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
                   - \ref EF_DRIVER_OK: Configuration was successful.
                   - \ref EF_DRIVER_ERROR_PARAMETER: Invalid input parameters, such as `tmr32` being NULL or `duty_cycle` > 100.

    This function configures the specified 32-bit timer (`tmr32`) to generate a PWM signal with edge alignment. 
    It sets the timer to up-count and periodic modes, configures the zero action to high, and uses the X compare register 
    to control the output signal. The duty cycle and reload values are used to compute the compare register value.

    Internal configurations performed by the function:
    - Sets the timer to up-count mode.
    - Configures the timer for periodic operation.
    - Sets the zero action to drive the PWM output high.
    - Configures the X compare register to drive the PWM output low on up-count.
    - Configures the Y compare register to maintain the current output state.
    - Calculates the X compare value based on the duty cycle and reload value.
    - Sets the reload value and compare register.
    - Ensures no change in output on the top action.

    Example PWM waveform:
    ```
      |       /|      /|
      |_____/__|____/  |
      |   / |  |  / |  |
      |_/___|__|/___|__|____
            |       |
            V       V
        ____    ____    ___   ___
            |__|    |__|   |__|
        duty    duty
        cycle   cycle
    ```

    \note Ensure the timer instance (`tmr32`) is correctly initialized before calling this function. 
          The reload value and compare value must align with the timer's capabilities and clock settings.
    \note for more information, check https://www.linkedin.com/pulse/center-aligned-pwm-vs-edge-aligned-neobionics-tn/
*/
EF_DRIVER_STATUS EF_TMR32_setPWM0EdgeAlignmentMode(EF_TMR32_TYPE_PTR tmr32, uint32_t reload_value, uint32_t duty_cycle);


//! Sets the PWM1 edge alignment mode 
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [in] reload_value The reload value to set in the PWM1CFG register. This determines the period of the PWM signal.
    \param [in] duty_cycle The duty cycle value to set in the PWM1CFG register, representing the high time as a percentage 
                           of the period (0 to 100).

    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
                   - \ref EF_DRIVER_OK: Configuration was successful.
                   - \ref EF_DRIVER_ERROR_PARAMETER: Invalid input parameters, such as `tmr32` being NULL or `duty_cycle` > 100.

    This function configures the specified 32-bit timer (`tmr32`) to generate a PWM signal with edge alignment on PWM1. 
    It sets the timer to up-count and periodic modes, configures the zero action to high, and uses the Y compare register 
    to control the output signal. The duty cycle and reload values are used to compute the compare register value.

    Internal configurations performed by the function:
    - Sets the timer to up-count mode.
    - Configures the timer for periodic operation.
    - Sets the zero action to drive the PWM output high.
    - Configures the Y compare register to drive the PWM output low on up-count.
    - Configures the X compare register to maintain the current output state.
    - Calculates the Y compare value based on the duty cycle and reload value.
    - Sets the reload value and compare register.
    - Ensures no change in output on the top action.

    Example PWM waveform:
    ```
      |       /|      /|
      |_____/__|____/  |
      |   / |  |  / |  |
      |_/___|__|/___|__|____
            |       |
            V       V
        ____    ____    ___   ___
            |__|    |__|   |__|
        duty    duty
        cycle   cycle
    ```

    \note Ensure the timer instance (`tmr32`) is correctly initialized before calling this function. 
          The reload value and compare value must align with the timer's capabilities and clock settings.
    \note for more information, check https://www.linkedin.com/pulse/center-aligned-pwm-vs-edge-aligned-neobionics-tn/
*/
EF_DRIVER_STATUS EF_TMR32_setPWM1EdgeAlignmentMode(EF_TMR32_TYPE_PTR tmr32, uint32_t reload_value, uint32_t duty_cycle);





//! Sets the PWM0 center-aligned mode
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [in] reload_value The reload value to set in the PWM0CFG register. This determines the period of the PWM signal.
    \param [in] cmpX_value The value to set in the CMPX register. This value controls the point at which the PWM signal transitions 
                           from high to low (or vice versa) in the center-aligned mode.

    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
                   - \ref EF_DRIVER_OK: Configuration was successful.
                   - \ref EF_DRIVER_ERROR_PARAMETER: Invalid input parameters, such as `tmr32` being NULL.

    This function configures the specified 32-bit timer (`tmr32`) to generate a PWM signal with center-alignment on PWM0. 
    It sets the timer to up-down counting mode and periodic mode, configures the zero and compare actions, and sets the reload 
    and compare values as specified.

    Internal configurations performed by the function:
    - Sets the timer to up-down counting mode.
    - Configures the timer for periodic operation.
    - Sets the zero action to drive the PWM output high.
    - Configures the X compare register to drive the PWM output low on up-count.
    - Configures the X compare register to drive the PWM output high on down-count.
    - Configures the Y compare register to maintain the current output state on both up and down counts.
    - Sets the reload value to define the PWM signal period.
    - Sets the X compare register value to define the transition point.

    Example PWM waveform:
    ```
      |       /|\
      |_____/__|__\
      |   / |  |  | \
      |_/___|__|__|___\__
            |     |
            V     V
        ____       ____
            |_____|    
    ```

    \note Ensure the timer instance (`tmr32`) is correctly initialized before calling this function. 
          The reload value and compare value must align with the timer's capabilities and clock settings.
    \note for more information, check https://www.linkedin.com/pulse/center-aligned-pwm-vs-edge-aligned-neobionics-tn/
*/
EF_DRIVER_STATUS EF_TMR32_setPWM0CenterAlignedMode(EF_TMR32_TYPE_PTR tmr32, uint32_t reload_value, uint32_t cmpX_value);





//! Sets the PWM1 center-aligned mode
/*!
    \param [in] tmr32 An \ref EF_TMR32_TYPE_PTR, which points to the base memory address of TMR32 registers. 
                      \ref EF_TMR32_TYPE is a structure that contains the TMR32 registers.
    \param [in] reload_value The reload value to set in the PWM1CFG register. This determines the period of the PWM signal.
    \param [in] cmpY_value The value to set in the CMPX register. This value controls the point at which the PWM signal transitions 
                           from high to low (or vice versa) in the center-aligned mode.

    \return status A value of type \ref EF_DRIVER_STATUS: returns a success or error code.
                   - \ref EF_DRIVER_OK: Configuration was successful.
                   - \ref EF_DRIVER_ERROR_PARAMETER: Invalid input parameters, such as `tmr32` being NULL.

    This function configures the specified 32-bit timer (`tmr32`) to generate a PWM signal with center-alignment on PWM1. 
    It sets the timer to up-down counting mode and periodic mode, configures the zero and compare actions, and sets the reload 
    and compare values as specified.

    Internal configurations performed by the function:
    - Sets the timer to up-down counting mode.
    - Configures the timer for periodic operation.
    - Sets the zero action to drive the PWM output high.
    - Configures the Y compare register to drive the PWM output low on up-count.
    - Configures the Y compare register to drive the PWM output high on down-count.
    - Configures the X compare register to maintain the current output state on both up and down counts.
    - Sets the reload value to define the PWM signal period.
    - Sets the X compare register value to define the transition point.

    Example PWM waveform:
    ```
      |       /|\
      |_____/__|__\
      |   / |  |  | \
      |_/___|__|__|___\__
            |     |
            V     V
        ____       ____ 
            |_____|    
    ```

    \note Ensure the timer instance (`tmr32`) is correctly initialized before calling this function. 
          The reload value and compare value must align with the timer's capabilities and clock settings.
    \note for more information, check https://www.linkedin.com/pulse/center-aligned-pwm-vs-edge-aligned-neobionics-tn/
*/
EF_DRIVER_STATUS EF_TMR32_setPWM1CenterAlignedMode(EF_TMR32_TYPE_PTR tmr32, uint32_t reload_value, uint32_t cmpY_value);

/******************************************************************************
* External Variables
******************************************************************************/


#endif  //EF_TMR32_H


/******************************************************************************
* End of File
******************************************************************************/
