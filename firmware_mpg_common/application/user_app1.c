/**********************************************************************************************************************
File: user_app1.c                                                                

Description:
Provides a Tera-Term driven system to display, read and write an LED command list.

Test1.
Test2 from Engenuics.
Test3.

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

extern  LedDisplayListHeadType UserApp2_sUserLedCommandList;

/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */

static bool bPrintHomepage=TRUE;
static u32 u32NumbersOfList=0;
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

/*----------------------------------------------------------------------------------------------------------------------
Function bCheck()

Description:
Enter commands as LED-ONTINE-OFFTIME.

Requires:
  - au8String[]

Promises:
  - Need the input
  - return TRUE if the input is right
  - return FALSE if the input is wrong

*/
static bool bCheck(u8 au8String[])
{
  bool bReturn=TRUE;
  bool bExist=FALSE;
  bool bLed=TRUE;
  bool bTime=TRUE;
  u8 u8Second;
  u8 u8Counter1;
  
  for(u8Counter1=2;u8Counter1<20;u8Counter1++)
  {
    if(au8String[u8Counter1]=='-')
    {
      u8Second=u8Counter1;
      bExist=TRUE;
      break;
    }
  }
  
  if(bExist&&au8String[1]=='-')
  {
    switch(au8String[0])
    {
    case 'W':break;
    case 'w':break;
    case 'P':break;
    case 'p':break;
    case 'B':break;
    case 'b':break;
    case 'C':break;
    case 'c':break;
    case 'G':break;
    case 'g':break;
    case 'Y':break;
    case 'y':break;
    case 'O':break;
    case 'o':break;
    case 'R':break;
    case 'r':break;
    default :bLed=FALSE;bReturn=FALSE;break;
    }
    
    if(bLed)
    {
      for(u8Counter1=2;u8Counter1<u8Second;u8Counter1++)
      {
        if(au8String[u8Counter1]<'0'||au8String[u8Counter1]>'9')
        {
          bReturn=FALSE;
          bTime=FALSE;
        }
      }
    }
    
    if(bTime)
    {
      for(u8Counter1=u8Second+1;au8String[u8Counter1]!='\r';u8Counter1++)
        {
          if(au8String[u8Counter1]<'0'||au8String[u8Counter1]>'9')
          {
            bReturn=FALSE;
            break;
          }
          
        }
    }
  } 
  else
  {
   bReturn=FALSE;
  }
  return bReturn; 
}

/*----------------------------------------------------------------------------------------------------------------------
Function Reset()

Description:
Clear the storage which store the input

Requires:
  - au8String2[]

Promises:
  - None

*/
static void Reset(u8 au8String2[])
{
  u8 u8Size=sizeof(au8String2);
  u8 u8Counter2=0;
  au8String2[u8Counter2]='0';
  
  for(u8Counter2=1;u8Counter2<u8Size;u8Counter2++)
  {
    au8String2[u8Counter2]='/0';
  }
}

/*----------------------------------------------------------------------------------------------------------------------
Function ReadLed()

Description:
make sure the kind of led colour

Requires:
  - au8String3[] 

Promises:
  - The list must be right
  - return the number which correspond the colour of led

*/
static u8 ReadLed(u8 au8String3[])
{
  u8 u8Led;
  
  switch(au8String3[0])
    {
    case 'W':u8Led=0;break;
    case 'w':u8Led=0;break;
    case 'P':u8Led=1;break;
    case 'p':u8Led=1;break;
    case 'B':u8Led=2;break;
    case 'b':u8Led=2;break;
    case 'C':u8Led=3;break;
    case 'c':u8Led=3;break;
    case 'G':u8Led=4;break;
    case 'g':u8Led=4;break;
    case 'Y':u8Led=5;break;
    case 'y':u8Led=5;break;
    case 'O':u8Led=6;break;
    case 'o':u8Led=6;break;
    case 'R':u8Led=7;break;
    case 'r':u8Led=7;break;
    default:break;
    }
  
  return u8Led;
}

/*----------------------------------------------------------------------------------------------------------------------
Function ReadOntime()

Description:
Read the start time from the list

Requires:
 - au8String4[]

Promises:
  - The list must be right
  - Return u32Ontime 

*/
static u32 ReadOntime(u8 au8String4[])
{
  u8 au8Ontime[]="0";
  u32 u32Ontime;
  u8 u8Counter3;
  
  for(u8Counter3=2;au8String4[u8Counter3]!='-';u8Counter3++)
  {
      au8Ontime[u8Counter3-2]=au8String4[u8Counter3];
  }
  
  u32Ontime=atoi(au8Ontime);
  return u32Ontime;
}

/*----------------------------------------------------------------------------------------------------------------------
Function ReadOfftime()

Description:
Read the end time from the list

Requires:
  - au8String5[]

Promises:
  - The list must be right
  - return u32Offtime 

*/
static u32 ReadOfftime(u8 au8String5[])
{
  u8 au8Offtime[]="0";
  u32 u32Offtime;
  u8 u8Counter4;
  u8 u8Second;
  
  for(u8Second=3;au8String5[u8Second]!='\0';u8Second++)
  {
    if(au8String5[u8Second]=='-')
       {
         break;
       }
  }
       
  for(u8Counter4=u8Second+1;au8String5[u8Counter4]!='\r';u8Counter4++)
  {
    au8Offtime[u8Counter4-u8Second]=au8String5[u8Counter4];
  }
       
  u32Offtime=atoi(au8Offtime);
  return u32Offtime;       
    
}
/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1SM_Idle 

Description:
Wait the user to choose the model 1 or 2
1 to program LED command sequence
2 to show current USER program

Requires:
  -

Promises:
  - The debug Intern is OK
  - UserApp1SM_StateMachine=UserApp1SM_CreatLedList when press 1
  - UserApp1SM_StateMachine=UserApp1SM_PrintLedList when press 2
*/
static void UserApp1SM_Idle(void)
{
  u8 u8Counter1_1;

  static u8 au8ChooseModel[1]="0";
  static u8 au8Homepage1[64];
  static u8 au8Homepage2[]="LED Programming Interface\n\r";
  static u8 au8Homepage3[]="Press 1 to program LED command sequence\n\r";
  static u8 au8Homepage4[]="Press 2 to show current USER program";
  
  /*Home page*/
  au8Homepage1[0]=au8Homepage1[62]='\n';
  au8Homepage1[1]=au8Homepage1[63]='\r';
  
  for(u8Counter1_1=2;u8Counter1_1<62;u8Counter1_1++)
  {
   au8Homepage1[u8Counter1_1]='*';
  }
  
  if(bPrintHomepage)
  {
    DebugSetPassthrough();
    DebugPrintf(au8Homepage1);
    DebugPrintf(au8Homepage2);
    DebugPrintf(au8Homepage3);
    DebugPrintf(au8Homepage4);
    DebugPrintf(au8Homepage1);
    
    bPrintHomepage=FALSE;
  }
  
/*Wait into 1 or 2*/
  if(G_u8DebugScanfCharCount==1)
  {
    DebugScanf(au8ChooseModel);
  
    if(au8ChooseModel[0]=='1')
    {
      UserApp1_StateMachine=UserApp1SM_CreatLedList;
      bPrintHomepage=TRUE;
    }
  
    else if(au8ChooseModel[0]=='2')
    {
      UserApp1_StateMachine=UserApp1SM_PrintLedList;
      bPrintHomepage=TRUE;
    }
  }

} /* end UserApp1SM_Idle() */
 
/*-------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1SM_CreatLedList

Description:
Read the input and check the input right or wrong
Creat the user list

Requires:
  -

Promises:
  - When you end creat,it will go back to UserApp1SM_Idle(UserApp1SM_StateMachine=UserApp1SM_Idle)
*/
static void UserApp1SM_CreatLedList(void)
{
  static u32 u32StartTime;
  static u32 u32EndTime;
  static u8 u8ColourLed;
  
  static u8 u8Point=0;
  static u32 u32Number=1;
   
  
  static u8 au8ListString[30]="0";
  static u8 au8InputWord[1];
  static u8 au8CreatPage[]="\n\rEnter commands as LED-ONTINE-OFFTIME and press Enter\n\rTime is in milliseconds,max 100 commands\n\rLED colors:R,O,Y,G,C,B,P,W\n\rExample:R-100-200(Red on at 100ms and off at 200ms)\n\rPress Enter on blank line to end";
  static u8 au8List1[3]="\n\r\0";
  static u8 au8List2[2]=":\0";
  
  static bool bCreatList=FALSE;
  static bool bInput=TRUE;
  static bool bNumber=TRUE;
  static LedCommandType RegisterList;
/*Page*/  
  if(bPrintHomepage)
  {
    LedDisplayStartList();
    u32Number=1;
    
    DebugSetPassthrough();
    DebugPrintf(au8CreatPage);
    bPrintHomepage=FALSE;
  }
  
   if(bNumber)
    { 
      DebugSetPassthrough();  
      DebugPrintf(au8List1);
      DebugPrintNumber(u32Number);
      DebugPrintf(au8List2);
    
      bNumber=FALSE;
    }
 
/*Wait Input*/
  if(G_u8DebugScanfCharCount&&bInput)
  {    
    DebugScanf(au8InputWord);
    au8ListString[u8Point]=au8InputWord[0];
  
    if(au8ListString[0]!='\r')
    {
     if(au8ListString[u8Point]=='\b')
     {
       u8Point--;
     }
     else
     {
        if(au8ListString[u8Point]!='\r')
        {
          u8Point++;
        }
        else
        {
          u8Point=0;
          bInput=FALSE;
        }
     }
    }
    else
    {
      u32NumbersOfList=u32Number;
      UserApp1_StateMachine=UserApp1SM_Idle;
      
      bPrintHomepage=TRUE;
      
      bNumber=TRUE;
    }
  }
  
  

/*Creat*/ 
  if(!bInput)
  {
    bCreatList=bCheck(au8ListString);
    if(bCreatList)
    {
     u8ColourLed=ReadLed(au8ListString);
     u32StartTime=ReadOntime(au8ListString);
     u32EndTime=ReadOfftime(au8ListString);
     
     RegisterList.eLED=u8ColourLed;
     RegisterList.bOn=TRUE;
     RegisterList.u32Time=u32StartTime;
     
     LedDisplayAddCommand(USER_LIST,&RegisterList);
     
     RegisterList.bOn=FALSE;
     RegisterList.u32Time=u32EndTime;
     
     LedDisplayAddCommand(USER_LIST,&RegisterList);
     
     bInput=TRUE;
     bNumber=TRUE;
     u32Number=u32Number+1;
     }
    else
    {
      u8 au8String[]="\n\rInvalid command: incorrect format.Please use L-ONTIME-OFFTIME";
      DebugPrintf(au8String);
      bInput=TRUE;
      bNumber=TRUE;
    }
  }


  
  
  
}/* end UserApp1SM_CreatLedList()*/

/*-------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1SM_PrintLedList()

Description:
Print the uesr list


Requires:
  - 

Promises:
  - The user list can not be empty
*/
static void UserApp1SM_PrintLedList(void)
{
 static u8 u8Counter_2;
 static u8 au8Stting_2[]="\n\rLED  ON TIME   OFF TIME\n\r-----------------------\n\r";
 DebugPrintf(au8Stting_2);
 
 for(u8Counter_2=0;u8Counter_2<u32NumbersOfList;u8Counter_2++)
 {
  LedDisplayPrintListLine(u8Counter_2);
 }
 
 UserApp1_StateMachine=UserApp1SM_Idle;
 bPrintHomepage=TRUE;
}/* end UserApp1SM_PrintLedList()*/
            
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
