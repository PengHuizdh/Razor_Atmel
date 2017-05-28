/**********************************************************************************************************************
File: user_app1.c                                                                

Description:
Provides a Tera-Term driven system to display, read and write an LED command list.

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:
None.

Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */

extern u8 G_au8DebugScanfBuffer[DEBUG_SCANF_BUFFER_SIZE]; /* From debug.c */
extern u8 G_u8DebugScanfCharCount;                        /* From debug.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
  u8 au8UserApp1Start1[] = "LED program task started\n\r";
  
  /* Turn off the Debug task command processor and announce the task is ready */
  DebugSetPassthrough();
  DebugPrintf(au8UserApp1Start1);
  
    /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_FailedInit;
  }

} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/
static void Number_Commands(void)
{
  static u8* pu8Count;
  static u8 au8PrintCount[3] = "0";
  *pu8Count = 1;
  au8PrintCount[0] = *pu8Count;
  au8PrintCount[1] = '.';
  au8PrintCount[2] = ' ';
  DebugPrintf(au8PrintCount);
  *pu8Count++;
}

/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for input */
static void UserApp1SM_Idle(void)
{
  static bool bTwo_Choices = TRUE;
  static bool bPress_1 = FALSE;
  static bool bPress_2 = FALSE;
  static u32 u32CountScanf = 0;
  static u8 au8Scanf[100]= "0";
  static u8* pau8Scanf = au8Scanf;
  static u8 au8ScanfBuffer[1] = "0";
  static u8* pau8ScanfBuffer = au8ScanfBuffer;
  static u8 au8Two_Choices[] = "*******************************************\n\r LED Programming Interface\n\r Press 1 to program LED command sequnece\n\r Press 2 to show current USER progrom\n\r*******************************************\n\r";
  
  if(bTwo_Choices)
  {
   DebugPrintf(au8Two_Choices);
   bTwo_Choices = FALSE;
  }
  
  if(DebugScanf(au8ScanfBuffer))
  {
    au8Scanf[u32CountScanf] = *pau8ScanfBuffer;
    u32CountScanf++;
    pau8Scanf = (au8Scanf + u32CountScanf); 
    
    if(*pau8ScanfBuffer == '1')
    {
      bPress_1 = TRUE;
      u8 au8Example[] = "\n\n\rEnter Command as LED-ONTIME-OFFTIME and press Enter \n\rTime is in millisenconds \n\rLED colors: R, O, Y, G, C, B, P, W \n\rExample R-100-1000(Red on at 100ms and off at 1000ms \n\rPress Enter on Blank Line to end \n\r";
      DebugPrintf(au8Example);
      Number_Commands();
    }
    if(*pau8ScanfBuffer == '2')
    {
      bPress_2 = TRUE;
    }
  } 
  
  if(bPress_1)
  {
   
  }
  
  if(bPress_2)
  {
    
  }
  
} /* end UserApp1SM_Idle() */
                      
            
#if 0
/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */
#endif


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserApp1SM_FailedInit(void)          
{
    
} /* end UserApp1SM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
