/**********************************************************************************************************************
File: user_app1.c                                                                
Peng Hui
----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */
extern u8 G_au8DebugScanfBuffer[];                    /* From debug.c */
extern u8 G_u8DebugScanfCharCount;
extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


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
static void PrintfName(u32 u32CountName)
{
  u8 au8PrintfBuffer[] = "0";
  u32 u32Number_Of_Bit = 0;
  u32 u32BufferCount = u32CountName;
  
  while(u32BufferCount)
  {
    u32BufferCount = u32BufferCount / 10;
    u32Number_Of_Bit++;
  }
  DebugLineFeed();
  
  u32 u32CountPrintf = u32Number_Of_Bit + 2;
  au8PrintfBuffer[u32CountPrintf + 1] = '\0';
  for(;u32CountPrintf > 0; u32CountPrintf--)
  {
    au8PrintfBuffer[(u32Number_Of_Bit + 2) - u32CountPrintf] = '*';
  }
  DebugPrintf(au8PrintfBuffer);
  
  DebugLineFeed();
  DebugPrintf("*");
  DebugPrintNumber(u32CountName);
  DebugPrintf("*");
  DebugLineFeed();
  
  u32CountPrintf = u32Number_Of_Bit + 2; 
  for(;u32CountPrintf > 0; u32CountPrintf--)
  {
    au8PrintfBuffer[(u32Number_Of_Bit + 2) - u32CountPrintf] = '*';
  }
  DebugPrintf(au8PrintfBuffer);
  DebugLineFeed();
}

/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
  static u8 au8Enter[10] = "0";
  static u8 au8EnterAdd[120] = "0";
  static u8 *pu8Enter = au8EnterAdd;
  static u8 au8MyName[] = {'i','u','h','g','n','e','p'};
  static u32 u32CountEnter = 0;
  static u32 u32CountEnterCycle = 0;
  static u32 u32CountName = 0;
  static u8 u8ForCycle = 0;
  static u8 u8Count_ConfirmName = 0;
  static u32 u32EnterBuffer;
  
  u32EnterBuffer = G_au8DebugScanfBuffer[0];
  
  /*if scanf then record and the pointer points to the next address*/
  if(DebugScanf(au8Enter) == 1)
  {
    u32CountEnter++;
    *pu8Enter = u32EnterBuffer;
    pu8Enter++;
    
    /*if enter 'i' then compared */
    if(u32EnterBuffer == 'i')
    {
      u32CountEnterCycle = u32CountEnter - 1;
      
      for(; u8ForCycle < 6; u8ForCycle++)
      {
        if(au8EnterAdd[u32CountEnterCycle] != au8MyName[u8ForCycle])
        {
          au8EnterAdd[100] = 0;
          pu8Enter = au8EnterAdd;
          u32CountEnter = 0;
          break;
        }
        else
        {
          u8Count_ConfirmName++;
          u32CountEnterCycle--;
          /*if all right then Count++*/
          if(u8Count_ConfirmName == 6)
          {
            u32CountName++;
            PrintfName(u32CountName);
            au8EnterAdd[100] = 0;
            pu8Enter = au8EnterAdd;
            u32CountEnter = 0;
          }
        }
      }
      
      u8ForCycle = 0;
      u8Count_ConfirmName = 0;
      u32CountEnterCycle = 0;
    }
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
