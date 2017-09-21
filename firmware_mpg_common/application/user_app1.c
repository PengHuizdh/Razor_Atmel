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

extern u8 G_au8DebugScanfBuffer[];
extern u8 G_u8DebugScanfCharCount;
/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */
static bool bOnce=TRUE;
static u32 u32Time=0;
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

  CloseAllLED();
  G_u8DebugScanfCharCount=0;
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_state1;
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

/*----------------------------------------------------------------------------------------------------------------------
Function CloseALLLED()

Description:Close all the LEDs and LCD.

Requires:
  - 
Promises:
  - 
*/
void CloseAllLED(void)
{
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  LedOff(LCD_RED);
  LedOff(LCD_GREEN);
  LedOff(LCD_BLUE);
}/* end  CloseAllLED */

/*----------------------------------------------------------------------------------------------------------------------
Function LCD_orange()

Description:Making the color of LCD is orange.

Requires:
  - 
Promises:
  - 
*/
void LCD_orange(void)
{
  LedPWM(LCD_RED, LED_PWM_100);
  LedPWM(LCD_GREEN, LED_PWM_0);
  LedPWM(LCD_BLUE, LED_PWM_100); 
}/* end  LCD_orange */

/*----------------------------------------------------------------------------------------------------------------------
Function LCD_purple()

Description:Making the color of LCD is purple.

Requires:
  - 
Promises:
  - 
*/
void LCD_purple(void)
{
  LedPWM(LCD_RED, LED_PWM_100);
  LedPWM(LCD_GREEN, LED_PWM_20);
  LedPWM(LCD_BLUE, LED_PWM_5);   
}/* end  LCD_purple */

/*----------------------------------------------------------------------------------------------------------------------
Function Changestate()

Description:Choose state1 or state2

Requires:
  - 
Promises:
  - 
*/
void ChangeState(void)
{
  u8 au8CHAR[]="\0";
  u8 u8NewNumber;
  
  u8NewNumber=G_u8DebugScanfCharCount;
  strcpy(au8CHAR,G_au8DebugScanfBuffer);
  
  if(au8CHAR[u8NewNumber-1]=='\r')
  {  
    CLEARDebug();
    if((au8CHAR[0]=='1'||au8CHAR[0]=='2')&&u8NewNumber<3)
    {
      if(au8CHAR[0]=='1')
      {
        UserApp1_StateMachine = UserApp1SM_state1;
        bOnce=TRUE;
      }
      if(au8CHAR[0]=='2')
      {
        UserApp1_StateMachine = UserApp1SM_state2;
        bOnce=TRUE;
      }
    }
     else
    {
      DebugPrintf("\r\nPlease input 1<CR>or2<CR>.\r\n"); 
    }
  }
  
  if(WasButtonPressed(BUTTON1))
  {
    ButtonAcknowledge(BUTTON1);
    UserApp1_StateMachine = UserApp1SM_state1;
    bOnce=TRUE;
  }
  
  if(WasButtonPressed(BUTTON2))
  {
    ButtonAcknowledge(BUTTON2);
    UserApp1_StateMachine = UserApp1SM_state2;
    u32Time=0;
    bOnce=TRUE;
  }
}/* end  Changestate */

/*----------------------------------------------------------------------------------------------------------------------
Function CLEARDebug()

Description:Clear the G_u8DebugScanfCharCount and G_au8DebugScanfBuffer[].

Requires:
  - 
Promises:
  - 
*/
void CLEARDebug(void)
{
  for(u8 i = 0; i < G_u8DebugScanfCharCount; i++)
  {
    G_au8DebugScanfBuffer[i] = '\0';
  }
  
  G_u8DebugScanfCharCount = 0;
}/* end CLEARDebug  */
  
/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* state1*/
static void UserApp1SM_state1(void)
{
  /*Initialize the state1*/
  if(bOnce)
  {
    CloseAllLED();
    LCD_orange();
    LedOn(WHITE);
    LedOn(PURPLE);
    LedOn(BLUE);
    LedOn(CYAN);
    
    DebugPrintf("\r\nEntering state 1\r\n");
    
    LCDCommand(LCD_CLEAR_CMD);
    LCDMessage(LINE1_START_ADDR,"STATE 1                    ");
    
    PWMAudioOff(BUZZER1);
    
    bOnce=FALSE;
  }
  
  /* Wait  state  change */
  ChangeState();
  
} /* end UserApp1SM_state1() */

/*-------------------------------------------------------------------------------------------------------------------*/
/*state2*/
static void UserApp1SM_state2(void)
{
  static u32 u32time1ms=0;
 
  /*Initialize the state2*/
  if(bOnce)
  {
    CloseAllLED();
    LCD_purple(); 
    LedBlink(GREEN,LED_1HZ);
    LedBlink(YELLOW,LED_2HZ);
    LedBlink(ORANGE,LED_4HZ);
    LedBlink(RED,LED_8HZ);
    
    DebugPrintf("\r\nEntering state 2\r\n");
    
    LCDCommand(LCD_CLEAR_CMD);
    LCDMessage(LINE1_START_ADDR,"STATE 2             ");
 
    PWMAudioOn(BUZZER1);
    PWMAudioSetFrequency(BUZZER1,200);
    u32time1ms=G_u32SystemTime1ms;
    bOnce=FALSE;  
  }
  /* Make the Buzzer1 work 100ms every second */
  if((G_u32SystemTime1ms-u32time1ms)==1)
  {
    u32time1ms=G_u32SystemTime1ms;
    u32Time++;
  }
  
  if(u32Time>1000)
  {
    u32Time=0;
  }
  
  if(u32Time>0&&u32Time<100)
  {
    PWMAudioOn(BUZZER1); 
  }
  else
  {
    PWMAudioOff(BUZZER1);
  }
  
   /* Wait  state  change */
  ChangeState();
 
} /* end UserApp1SM_state2() */

    
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
