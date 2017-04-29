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
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
 
 
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
    static u8 u8ButtonScanf(void)
      {  
            u8 u8ButtonValue = 9;
              
             if(WasButtonPressed(BUTTON0))
             {
                ButtonAcknowledge(BUTTON0);
                u8ButtonValue = 1;
             }
             
             if(WasButtonPressed(BUTTON1))
             {
              ButtonAcknowledge(BUTTON1);
              u8ButtonValue = 2;
             }
             
             if(WasButtonPressed(BUTTON2))
             {
              ButtonAcknowledge(BUTTON2);
              u8ButtonValue = 3;
             }
             
             if(WasButtonPressed(BUTTON3))
             {
              ButtonAcknowledge(BUTTON3);
              u8ButtonValue = 4;
             }
             
             return u8ButtonValue;
      }

/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
   static u8 u8Count_Detection = 0;
   static u8 u8Count_Enter = 0;
   static u8 u8Password[6] = {2,2,3,3,4,4};
   static u8 u8Password_enter[6] = 0;
   static u8 u8ButtonValue = 0;
   static u32 u32Count_RED_Bright = 0;
   static u32 u32Count_End_Bright = 0;
   static bool bCount_End = 0;
   u8 u8Count_Right = 0;
   
   u8ButtonValue = u8ButtonScanf();
   u32Count_RED_Bright++;
   if(bCount_End)
   {
     u32Count_End_Bright++;
   }
   if(u32Count_End_Bright == 1000)
   {
      LedOff(PURPLE);
      LedOff(GREEN);
      u32Count_End_Bright = 0;
      bCount_End = 0;
   }
   if(u8ButtonValue != 9)
   {  
      LedOff(PURPLE);
      LedOff(GREEN);
      LedOn(RED);         
      u8Password_enter[u8Count_Enter] = u8ButtonValue;
       u8Count_Enter++;                 
   } 
    
      if(u32Count_RED_Bright > 300)
      {
        LedOff(RED);
        u32Count_RED_Bright = 0;
      }
  
   
  
   if(u8Count_Enter == 6)
   {
     for( ;u8Count_Detection < 6; u8Count_Detection++)
     {  
       u8Count_Right++;
       if(u8Password_enter[u8Count_Detection] != u8Password[u8Count_Detection])
       {
         u8Password_enter[6] = 0;
         LedOn(PURPLE);
         bCount_End = 1;
         break;
       }  
     }
     if(u8Count_Right == 6)
     {
        LedOn(GREEN);
        bCount_End = 1;
     }
       u8Count_Enter = 0;
       u8Count_Detection = 0;
   }
/* switch(u8ButtonValue)
 {
 case 1:
   LedToggle(WHITE);
   u8ButtonValue = 0;
   break;
 case 2:
   LedToggle(PURPLE);
   u8ButtonValue = 0;
   break;
 case 3:
   LedOn(BLUE);
   u8ButtonValue = 0;
   break;
 case 4:
   LedOff(WHITE);
   LedOff(PURPLE);
   LedOff(BLUE);
   u8ButtonValue = 0;
   break;
 default:
   break;
 }*/

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
