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
   static u8 u8Password[10] = {2,2,3,3,1,1,9,9,9,9};
   static u8 u8Password_enter[10] = 0;
   static u8 u8ButtonValue = 0;
   static u32 u32Count_Green = 0;
   static u32 u32Count_Red = 0;
   static u32 u32Count_Unhold = 0;
   static u32 u32Count_WHITE_Bright = 0;
   static u32 u32Count_Custom_Password = 0;
   static u32 u32Count_Initialize_Custom_Password = 0;
   static u32 u32Count_Delay_Initialization_Completed = 0;
   static bool bPress_the_button = 0;
   static bool bEnter_Right = 0;
   static bool bEnter_Error = 0;
   static bool bLocked = 1;
   static bool bInitialize_Custom_Password = 1;
   static bool bCustom_Password = 0;
   static bool bInitialization_Complete = 0;
   u8 u8Count_Right = 0;
   
   u8ButtonValue = u8ButtonScanf();
   /*打开板子，先给用户两秒钟判断要不要设置密码，如果要则长按3秒*/
     if(bInitialize_Custom_Password)
     {
       u32Count_Initialize_Custom_Password++;
       if(u32Count_Initialize_Custom_Password > 5000 && bCustom_Password == 0)
       {
          u32Count_Initialize_Custom_Password = 0;
          bInitialize_Custom_Password = 0;
       }
       else
       {
         /*按键3按下3秒进入设置密码程序*/
             if(IsButtonHeld(BUTTON3,3000))
             {
                bCustom_Password = 1;
             } 
       }
     /*进入自定义密码程序*/
       if(bCustom_Password)
       {
            u32Count_Custom_Password++; 
            if(u32Count_Custom_Password >= 500)
             {
                LedOn(GREEN);
                LedOn(RED);
             }
             else
             {
                LedOff(GREEN);
                LedOff(RED);
             }
             
             if(u32Count_Custom_Password == 1000)
             {
                u32Count_Custom_Password = 0;
             } 
            
            if(u8ButtonValue != 9)
            {
              u8Password[u8Count_Enter] = u8ButtonValue;
              u8Count_Enter++;
            }
            /*设置一个六位数的密码*/
            if(u8Count_Enter == 6)
            {
              u8Count_Enter = 0;
              LedOff(GREEN);
              LedOff(RED);
              bCustom_Password = 0;
              bInitialize_Custom_Password = 0;
            }
         }
      }
     /*用户自定义密码设置完成，延时0.5秒，防止设置密码的最后一位时进入输入密码程序*/
     if(!bInitialize_Custom_Password)
     {
        u32Count_Delay_Initialization_Completed++;
        if(u32Count_Delay_Initialization_Completed == 500)
        {
          bInitialization_Complete = 1;
        }
     }
   /*进入输入密码程序*/
     if(bInitialization_Complete)   
     {
         if(bLocked)
         {
            LedOn(RED);
         }
         
         if(u8ButtonValue != 9)
         {  
            bPress_the_button = 1;
            LedOn(WHITE);      
            u8Password_enter[u8Count_Enter] = u8ButtonValue;
             u8Count_Enter++;
         } 
         /*按下按键则白灯闪烁*/
           if(bPress_the_button)
           {
             u32Count_WHITE_Bright++;
           }
         
            if(u32Count_WHITE_Bright == 300)
           {
              LedOff(WHITE);
              u32Count_WHITE_Bright = 0;
              bPress_the_button = 0;
           }
         /*输入密码不足6位按下确认键时*/
          if(u8Count_Enter != 6 && IsButtonHeld(BUTTON3,1000))
         {
             bEnter_Error = 1;
             u8Password_enter[10] = 0;
             u8Count_Enter == 0;
         }
         /*输入密码超过10位时*/
          if(u8Count_Enter > 10 )
         {
             bEnter_Error = 1;
             u8Password_enter[10] = 0;
             u8Count_Enter == 0;
         }
         /*输入密码，并按下按键3确认时*/
         if(IsButtonHeld(BUTTON3,1000) && u8Count_Enter==6 )
         {
           for( ;u8Count_Detection < 6; u8Count_Detection++)
           {  
             u8Count_Right++;
             if(u8Password_enter[u8Count_Detection] != u8Password[u8Count_Detection])
             {
               u8Password_enter[6] = 0;
               bEnter_Error = 1;
               break;
             }  
           }
             if(u8Count_Right == 6)
             {
                bEnter_Right = 1;
                u8Password_enter[6] = 0;
             }
               u8Count_Detection = 0;
         }
         /*当输入密码正确*/
         if(bEnter_Right)
           {
             bLocked = 0;
             LedOff(RED);
             u32Count_Green++;
             if(u32Count_Green >= 500)
             {
                LedOn(GREEN);
                u8Count_Enter = 0; //当密码正确，给计数器清零，放在这是因为可以延时0.5秒清零，这样就不会进入if(bEnter_Error)里面了
             }
             else
             {
                LedOff(GREEN);
             }
             
             if(u32Count_Green == 1000)
             {
                u32Count_Green = 0;
             } 
           }
         /*当输入密码错误*/
         if(bEnter_Error)
           {
             bLocked = 0;
             u32Count_Red++;
             if(u32Count_Red >= 500)
             {
                LedOn(RED);   
             }
             else
             {
                LedOff(RED);
             }
             
             if(u32Count_Red == 1000)
             {
              u32Count_Red = 0;
             }
           }
         /*当完成密码输入10后重新锁住*/
         if(bLocked == 0)
         {
           u32Count_Unhold++;
           if(u32Count_Unhold == 10000)
           {
              u32Count_Unhold = 0;
              bEnter_Right = 0;
              bEnter_Error = 0;
              LedOff(GREEN);
              bLocked = 1;
           }
         }
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
