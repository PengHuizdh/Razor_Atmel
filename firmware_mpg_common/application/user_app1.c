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

extern void LedDisplayStartList(void);                    /*Frome user_app2*/
extern bool LedDisplayAddCommand(LedDisplayListNameType eListName_, LedCommandType* pCommandInfo_); /*Frome user_app2*/
extern bool LedDisplayPrintListLine(u8 u8ListItem_);      /*Frome user_app2*/



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
  static u8 u8CountOnes_place = 49;
  static u8 u8CountTens_place = 48;
  static u8 au8PrintCount[3] = "0";

  au8PrintCount[0] = u8CountTens_place;
  au8PrintCount[1] = u8CountOnes_place;;
  au8PrintCount[2] = '.';
  DebugPrintf(au8PrintCount);
  u8CountOnes_place++;
  
  if(u8CountOnes_place == 58)
  {
    u8CountTens_place++;
    u8CountOnes_place = 48;
  }
}

static bool User_Command(u8* au8Scanf_, u32 u32CountScanf_)
{
  static bool bInitialize = TRUE;
  static u8* pau8Scanf_Funtion;
  static u8* pLed;
  static bool bLed = TRUE;
  static bool bError = FALSE;
  static u8 u8CounterRecord = 0;
  static u8 u8CounterBuffer = 0;
  static u8 u8CountOnTime = 0;
  static u8 u8CountOffTime = 0;
  static u8 u8Count_ = 0;
  static u32 u32OnTime = 0;
  static u32 u32OffTime = 0;
  static u8 au8OnTime[5] = "0";
  static u8 au8OffTime[5] = "0";
  static LedCommandType UserCommand;
  
  if(bInitialize)
  {
    pau8Scanf_Funtion = au8Scanf_ ;
    bInitialize = FALSE;
  }
  
   if((*pau8Scanf_Funtion != '\r') && (*(pau8Scanf_Funtion - 1) != '\r'))
  { 
      pau8Scanf_Funtion++;
      u8CounterRecord++;
      if(*pau8Scanf_Funtion == '-')
      {
        pau8Scanf_Funtion++;
        u8CounterRecord++;
        u8Count_++;
      } 
      
      if((u8Count_ == 1) && (bLed))
      {
        u8CounterBuffer = (u8CounterRecord - 1);
        pLed = (au8Scanf_ + u8CounterBuffer - 1 );
        
        switch(*pLed)
        {
        case 'W': UserCommand.eLED = 0; break;
        case 'w': UserCommand.eLED = 0; break;
        case 'P': UserCommand.eLED = 1; break;
        case 'p': UserCommand.eLED = 1; break;
        case 'B': UserCommand.eLED = 2; break;
        case 'b': UserCommand.eLED = 2; break;
        case 'C': UserCommand.eLED = 3; break;
        case 'c': UserCommand.eLED = 3; break;
        case 'G': UserCommand.eLED = 4; break;
        case 'g': UserCommand.eLED = 4; break;
        case 'Y': UserCommand.eLED = 5; break;
        case 'y': UserCommand.eLED = 5; break;
        case 'O': UserCommand.eLED = 6; break;
        case 'o': UserCommand.eLED = 6; break;
        case 'R': UserCommand.eLED = 7; break;
        case 'r': UserCommand.eLED = 7; break;
        default: DebugPrintf("Please enter the correct color\n\r"); Number_Commands(); bError = TRUE; break;
        }
        u8CounterBuffer = 0;
        bLed = FALSE;
      }
      
      if((u8Count_ >= 1) && (u8Count_ < 2) && (!bLed))
      {
        au8OnTime[u8CountOnTime] = *pau8Scanf_Funtion ;
        u8CountOnTime++;
        u32OnTime = atoi(au8OnTime);
        
        if((*pau8Scanf_Funtion < 48) || (*pau8Scanf_Funtion > 57))
        {
          DebugPrintf("Please enter the correct OnTime\n\r");
          Number_Commands();
          bError = TRUE;
        }
      }
      
      if((u8Count_ >= 2) && (*pau8Scanf_Funtion != '\r'))
      {
        au8OffTime[u8CountOffTime] = *pau8Scanf_Funtion ;
        u8CountOffTime++;
        u32OffTime = atoi(au8OffTime);
        
        if((*pau8Scanf_Funtion < 48) || (*pau8Scanf_Funtion > 57))
        {
          DebugPrintf("Please enter the correct OffTime\n\r");
          Number_Commands();
          bError = TRUE;
        }
      }
      
      if(*pau8Scanf_Funtion == '\r')
      {      
        for(u8 u8j = 1; u8j < u8CountOnTime; u8j++)
        {
          au8OnTime[u8j] = '\0';
        }
        for(u8 u8k = 1; u8k < u8CountOffTime; u8k++)
        {
          au8OffTime[u8k] = '\0';
        }
        
        pau8Scanf_Funtion = au8Scanf_ ;
        u8CounterRecord = 0;
        u8Count_ = 0;
        u8CountOnTime = 0;
        u8CountOffTime = 0; 
        bLed = TRUE;
        
        if(bError)
        {
          bError = FALSE;
          return FALSE;
        }
        
        UserCommand.bOn = TRUE;
        UserCommand.u32Time = u32OnTime;
        LedDisplayAddCommand(USER_LIST,&UserCommand);
        UserCommand.bOn = FALSE;
        UserCommand.u32Time = u32OffTime;
        LedDisplayAddCommand(USER_LIST,&UserCommand);       
        return FALSE;            
      }    
   }
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
  static bool bEnd = TRUE;
  static u32 u32CountScanf = 0;
  static u8 u8Count_Enter = 0;
  static u8 au8Scanf[100]= "0";
  static u8* pau8Scanf = au8Scanf;
  static u8 au8ScanfBuffer[1] = "0";
  static u8* pau8ScanfBuffer = au8ScanfBuffer;
  static u8 au8Two_Choices[] = "*******************************************\n\r LED Programming Interface\n\r Press 1 to program LED command sequnece\n\r Press 2 to show current USER progrom\n\r*******************************************\n\r";
  static u8 au8Press_2[] = "\n\rLED On_Time  Off_Time\n\r----------------------\n\r";
  static u8 au8End[] = "----------------------\n\r"; 
  
  if(bTwo_Choices)
  {
   DebugPrintf(au8Two_Choices);
   bTwo_Choices = FALSE;
  }
  
  if(DebugScanf(au8ScanfBuffer))
  {
    au8Scanf[u32CountScanf] = *pau8ScanfBuffer;
    u32CountScanf++;
    pau8Scanf = (au8Scanf + u32CountScanf - 1); 
    
    if((*pau8ScanfBuffer == '1') && (!bPress_1))
    {
      bPress_1 = TRUE;
      u8 au8Example[] = "\n\n\rEnter Command as LED-ONTIME-OFFTIME and press Enter \n\rTime is in millisenconds \n\rLED colors: R, O, Y, G, C, B, P, W \n\rExample R-100-1000(Red on at 100ms and off at 1000ms \n\rPress Enter on Blank Line to end \n\r";
      DebugPrintf(au8Example);
      Number_Commands();
    }
    
    if((*pau8ScanfBuffer == '2') && (bPress_2))
    {
      DebugPrintf("\n\n\rUser progrom is :\n\r");
      DebugPrintf(au8Press_2);
      
      for(u8 u8j = 0; u8j < u8Count_Enter; u8j++)
      {
        LedDisplayPrintListLine(u8j);
      }
      
      DebugPrintf(au8End);
      LedDisplayStartList();
      bPress_2 = FALSE;
    }
    
    if((bPress_1) && (*pau8Scanf == '\r') && (u32CountScanf < 2))
    {     
      DebugPrintf("\n\n\rThe input is complete\n\r");
      DebugPrintf(au8Press_2);
      
      for(u8 u8i = 0; u8i < u8Count_Enter; u8i++)
      {
        LedDisplayPrintListLine(u8i);
      }
      
      DebugPrintf(au8End);
      bPress_1 = FALSE;
      bPress_2 = TRUE;
      bEnd = FALSE;
    }
    
    if(*pau8Scanf == '\b')
    {
      u32CountScanf = u32CountScanf - 2;
    }
    
    if((*pau8Scanf == '\r') && (bEnd))
    {
      u8Count_Enter++;
      DebugPrintf("\n");
      Number_Commands();
    }
  }  
  
  if((*pau8Scanf == '\r') && (u32CountScanf > 2))
  {
    if(!User_Command(au8Scanf, u32CountScanf))
    {  
      for(u8 u8i = 1; u8i < u32CountScanf; u8i++)
      {
        au8Scanf[u8i] = '\0';
      }
      u32CountScanf = 0;
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
