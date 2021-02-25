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

    
} /* end UserAppInitialize() */

  
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
    static u32 u32Counter = 0;  //a 32-bit counter variable
    u8 u8ButtonLastState = RB5; //
    u8 u8Button;
    while(1)
    { 
        u8Button = RB5;
        if(u8Button == 0x00 && u8ButtonLastState == 0x01)
        {
            u32Counter ++;
            if((0x01 & u32Counter) != 0x00)
            {
                LATA0 = 0x01;
            }
            else
            {
                LATA0 = 0x00;
            }
            if((0x02 & u32Counter) != 0x00)
            {
                LATA1 = 0x01;
            }
            else
            {
                LATA1 = 0x00;
            }
            if((0x04 & u32Counter) != 0x00)
            {
                LATA2 = 0x01;
            }
            else
            {
                LATA2 = 0x00;
            }
            if((0x08 & u32Counter) != 0x00)
            {
                LATA3 = 0x01;
            }
            else
            {
                LATA3 = 0x00;
            }
            if((0x10 & u32Counter) != 0x00)
            {
                LATA4 = 0x01;
            }
            else
            {
                LATA4 = 0x00;
            }
            if((0x20 & u32Counter) != 0x00)
            {
                LATA5 = 0x01;
            }
            else
            {
                LATA5 = 0x00;
            }   
        }
        u8ButtonLastState = u8Button;
    }
} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
