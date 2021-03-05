/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
    LATA = 0x80;
    T0CON0 = 0x90;
    T0CON1 = 0x54;
    
} /* end UserAppInitialize() */


/*----------------------------------------------------------------------------------------------------------------------
@fn void TimeXus(INPUT_PARAMETER)
 * Sets Timer0 to count u16Microseconds_

@brief Creates a delay of INPUT_PARAMETER seconds

Requires:
- Timer0 configured such that each timer tick is 1 microsecond
- INPUT_PARAMETER_ is the value in microseconds to time from 1 to 65535

Promises:
- Pre-loads TMR0H:L to clock out desired period
- TMR0IF cleared
- Timer 0 enabled
*/

void TimeXus(u16 u16Input)
{
    /*Disable the timer during configuration*/
    T0CON0 &= 0x7F;
    
    /*Preload TMR0H and TMR0L based on u16TimeXus*/
    u16 u16TimeLeft = 0xFFFF - u16Input;
    TMR0H = u16TimeLeft >> 8;
    TMR0L = u16TimeLeft & 0x0F;
    
    /*Clear TMR0IF and enable TImer 0*/
    PIR3 &= 0x7F;
    T0CON0 += 0x80;
} /*end TimeXus()*/


/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- NONE

Promises:
- A 6-bit counter that will only use RA0-RA5

*/
void UserAppRun(void)
{
    static u16 u16counter = 0x0000; //counter to monitor time in microseconds passed, starts at 0
    u8 au8Pattern[8] = {0x20, 0x08, 0x02, 0x10, 0x04, 0x01, 0x2A, 0x15}; //light pattern
    static u8 u8counter = 0x00;     //counter to access various array elements, starts at 0
    if(u16counter < 0x01F4)         // 0x01F4 = 500
    {
        u16counter += 0x0001;       //increment u16counter by 1
    }
    else
    {
        LATA = au8Pattern[u8counter]; //turns on pins based on value of u8counter
        u8counter += 0x01;            //increment u8counter by 1
        if(u8counter == 0x08)         //once all array elements have been accessed, go back to beginning
        {
            u8counter = 0x00;         
        }
        u16counter = 0x0000;
    }
    
} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
