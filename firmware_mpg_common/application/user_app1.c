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
static void PrintName(u32 u32DelayPrintName)
{
  if(u32DelayPrintName == 1)
  {
    LCDCommand(LCD_CLEAR_CMD);
  }
 
  if(u32DelayPrintName == 500)
  {
    PWMAudioOn(BUZZER1) ;
    PWMAudioSetFrequency(BUZZER1, 300);
    LCDMessage(LINE1_START_ADDR, "i");
    LedOn(WHITE);
  }
  
  if(u32DelayPrintName == 1500)
  {
    PWMAudioSetFrequency(BUZZER1, 350);
    LCDCommand(LCD_CLEAR_CMD);
    LCDMessage(LINE2_START_ADDR + 1, "i");
    LCDMessage(LINE1_START_ADDR, "u");
    LedOn(PURPLE); 
  }
  
  if(u32DelayPrintName == 2500)
  {
    PWMAudioSetFrequency(BUZZER1, 400);
    LCDCommand(LCD_CLEAR_CMD);
    LCDMessage(LINE1_START_ADDR + 2, "i");
    LCDMessage(LINE2_START_ADDR + 1, "u");
    LCDMessage(LINE1_START_ADDR, "H");
    LedOn(BLUE);
  }
  
  if(u32DelayPrintName == 3500)
  {
    PWMAudioSetFrequency(BUZZER1, 450);
    LCDCommand(LCD_CLEAR_CMD);
    LCDMessage(LINE2_START_ADDR + 3, "i");
    LCDMessage(LINE1_START_ADDR + 2, "u");
    LCDMessage(LINE2_START_ADDR + 1, "H");
    LCDMessage(LINE1_START_ADDR, "g");
    LedOn(CYAN);
  }
  
  if(u32DelayPrintName == 4500)
  {
    PWMAudioSetFrequency(BUZZER1, 500);
    LCDCommand(LCD_CLEAR_CMD);
    LCDMessage(LINE1_START_ADDR + 4, "i");
    LCDMessage(LINE2_START_ADDR + 3, "u");
    LCDMessage(LINE1_START_ADDR + 2, "H");
    LCDMessage(LINE2_START_ADDR + 1, "g");
    LCDMessage(LINE1_START_ADDR, "n");
    LedOn(GREEN);
  }
  
  if(u32DelayPrintName == 5500)
  {
    PWMAudioSetFrequency(BUZZER1, 550);
    LCDCommand(LCD_CLEAR_CMD);
    LCDMessage(LINE2_START_ADDR + 5, "i");
    LCDMessage(LINE1_START_ADDR + 4, "u");
    LCDMessage(LINE2_START_ADDR + 3, "H");
    LCDMessage(LINE1_START_ADDR + 2, "g");
    LCDMessage(LINE2_START_ADDR + 1, "n");
    LCDMessage(LINE1_START_ADDR, "e");
    LedOn(YELLOW);
  }
  
  if(u32DelayPrintName == 6500)
  {
    PWMAudioSetFrequency(BUZZER1, 600);
    LCDCommand(LCD_CLEAR_CMD);
    LCDMessage(LINE1_START_ADDR + 6, "i");
    LCDMessage(LINE2_START_ADDR + 5, "u");
    LCDMessage(LINE1_START_ADDR + 4, "H");
    LCDMessage(LINE2_START_ADDR + 3, "g");
    LCDMessage(LINE1_START_ADDR + 2, "n");
    LCDMessage(LINE2_START_ADDR + 1, "e");
    LCDMessage(LINE1_START_ADDR, "P");
    LedOn(ORANGE);
  }
  
  if(u32DelayPrintName == 7500)
  {
    PWMAudioOff(BUZZER1);
    LCDCommand(LCD_CLEAR_CMD);
    LCDMessage(LINE1_START_ADDR, "PengHui");
    LedOff(WHITE);
    LedOff(PURPLE);
    LedOff(BLUE);
    LedOff(CYAN);
    LedOff(GREEN);
    LedOff(YELLOW);
    LedOff(ORANGE); 
  }
}

static void CycleName(void)
{
  static u8 u8CountCycleLine1 = LINE1_START_ADDR;
  static u8 u8CountCycleLine2 = (LINE2_START_ADDR + 20);
  
  if(u8CountCycleLine1 <=  19)
  {
    LCDCommand(LCD_CLEAR_CMD);
    LCDMessage(u8CountCycleLine1, "PengHui");
    u8CountCycleLine1++;
  }
  else if(u8CountCycleLine2 >= 64)
  {
    LCDCommand(LCD_CLEAR_CMD);
    LCDMessage(u8CountCycleLine2, "PengHui");
    u8CountCycleLine2--;
  }
  else
  {
    u8CountCycleLine1 = LINE1_START_ADDR;
    u8CountCycleLine2 = (LINE2_START_ADDR + 20);
  } 
}

static void Print_LCD(u8* pu8EnterBuffer, u8 u8CountPrintf)
{
  static u8 u8CountNumber = 0;
  static u8 u8CountPrint_40 = 0;
  static u16 u16Delay = 0;
  static u8 au8Buffer[255] = "0";
  static u8* pu8Buffer = au8Buffer;
  static u8* pu8Transfer;
  static u8 au8PrintfLine1[20] = "0";
  static u8 au8PrintfLine2[20] = "0";
  static bool bInitialize = TRUE;
  
  if(bInitialize)
    {
      u8CountNumber = u8CountPrintf;
      pu8Transfer = pu8EnterBuffer;
      bInitialize = FALSE;
    }
  
  if(u8CountPrintf < 20)
  {
    pu8Buffer = ((pu8EnterBuffer + 2) - u8CountPrintf);
    
    for(u8 u8i=0; u8i<u8CountPrintf; u8i++)
    {
      au8PrintfLine1[u8i] = *pu8Buffer;
      pu8Buffer++;
    }
    
    LCDCommand(LCD_CLEAR_CMD);
    LCDMessage(LINE1_START_ADDR , au8PrintfLine1);
  }
  
  else if((u8CountPrintf >=20) && (u8CountPrintf < 40))
  {
    pu8Buffer = ((pu8EnterBuffer + 2) - u8CountPrintf);
    
    for(u8 u8j=0; u8j<20; u8j++)
    {
      au8PrintfLine1[u8j] = *pu8Buffer;
      pu8Buffer++;
    }
    
    for(u8 u8j=0; u8j<(u8CountPrintf-20); u8j++)
    {
      au8PrintfLine2[u8j] = *pu8Buffer;
      pu8Buffer++;
    }
    
    LCDCommand(LCD_CLEAR_CMD);
    LCDMessage(LINE1_START_ADDR , au8PrintfLine1);
    LCDMessage(LINE2_START_ADDR , au8PrintfLine2);
  }
  
  else if(u8CountNumber >= 40)
  {
    u16Delay++;
    if(u16Delay == 800)
    {
      u8CountPrint_40++;
                  
       if(u8CountPrint_40 < 20)
        {
          pu8Buffer = ((pu8EnterBuffer + 2) - u8CountPrintf);
          for(u8 u8i=0; u8i<u8CountPrint_40; u8i++)
          {
            au8PrintfLine1[u8i] = *pu8Buffer;
            pu8Buffer++;
          }
          
          LCDCommand(LCD_CLEAR_CMD);
          LCDMessage(LINE1_START_ADDR , au8PrintfLine1);
          u16Delay = 0; 
        }
       
        else if((u8CountPrint_40 >=20) && (u8CountPrint_40 < 40))
        {
          pu8Buffer = ((pu8EnterBuffer + 2) - u8CountPrintf);
          
          for(u8 u8j=0; u8j<20; u8j++)
          {
            au8PrintfLine1[u8j] = *pu8Buffer;
            pu8Buffer++;
          }
          
          for(u8 u8j=0; u8j<(u8CountPrint_40-19); u8j++)
          {
            au8PrintfLine2[u8j] = *pu8Buffer;
            pu8Buffer++;
          }
          
          LCDCommand(LCD_CLEAR_CMD);
          LCDMessage(LINE1_START_ADDR , au8PrintfLine1);
          LCDMessage(LINE2_START_ADDR , au8PrintfLine2);
          u16Delay = 0;                 
        }
       
       else if(u8CountPrint_40++ >= 40)
        {
          u8CountPrint_40 = 41;
          u8CountNumber--;
          pu8Buffer = ((pu8Transfer + 2) - u8CountPrintf);
          
          for(u8 u8j=0; u8j<20; u8j++)
           {
             au8PrintfLine1[u8j] = *pu8Buffer;
             pu8Buffer++;
           }
          
           for(u8 u8j=0; u8j<20; u8j++)
           {
             au8PrintfLine2[u8j] = *pu8Buffer;
             pu8Buffer++;
           }
          
           LCDCommand(LCD_CLEAR_CMD);
           LCDMessage(LINE1_START_ADDR , au8PrintfLine1);
           LCDMessage(LINE2_START_ADDR , au8PrintfLine2);
           u16Delay = 0; 
           pu8Transfer++;
        }
     }
   }  
}

/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
   static u32 u32DelayPrintName = 0;
   static u32 u32DelayCycleName = 0;
   static u32 u32CountBuffer = 0;
   static u8 u8CountPrintf = 0;
   static u32 u32EnterBuffer = 0;
   static u8 au8Enter[] = "0";
   static u8 au8EnterBuffer[255]= "0";
   static u8* pu8EnterBuffer = au8EnterBuffer;
   static bool bPrintName = TRUE;
   static bool bCycleName = FALSE;
   static bool bEnterDebug = FALSE;
   static bool bPrintf = FALSE;
   static bool bPrintfCycle = FALSE;
   
 
   if(bPrintName)
   {
     u32DelayPrintName++;
     PrintName(u32DelayPrintName);
     if(u32DelayPrintName == 7500)
     {
       u32DelayPrintName = 0;
       bPrintName = FALSE;
       bCycleName = TRUE;
     }
   }
   
   if(bCycleName)
   {
     u32DelayCycleName++;
     if(u32DelayCycleName == 500)
     {
       CycleName();
       u32DelayCycleName = 0;
     }
   }
   
   if(WasButtonPressed(BUTTON3))
     {
       ButtonAcknowledge(BUTTON3);
       LCDCommand(LCD_CLEAR_CMD);
       bCycleName = FALSE;
       bEnterDebug = TRUE;
     }
   
   if(bEnterDebug)
   {
     u32EnterBuffer = G_au8DebugScanfBuffer[0];  
      if(DebugScanf(au8Enter) == 1)
      { 
        *pu8EnterBuffer = u32EnterBuffer;
        u8CountPrintf++;
        if(u32EnterBuffer == '\r')
         {
           bPrintf = TRUE;
           if(u8CountPrintf >= 40)
           {
             bPrintfCycle = TRUE;
           }
         }
         if(bPrintf)
         { 
           Print_LCD((pu8EnterBuffer-1),u8CountPrintf);
         }
        u32CountBuffer++;
        pu8EnterBuffer++;
      }
        if(bPrintfCycle)
          { 
           Print_LCD((pu8EnterBuffer-2),u8CountPrintf);
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
