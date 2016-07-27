/**
  ******************************************************************************
  * @file    :Main.c
  * @author  :MG Team
  * @version :V1.0
  * @date    
  * @brief   
  ******************************************************************************
***/

/* Includes ------------------------------------------------------------------*/
#include "Includes.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//workmode:iBeacon & Eddyston & Remote
volatile uint8_t Work_Mode = Work_Mode_Help;

//fcunction
char *FunctionDisplay[11]={
	"---------------------------iBeacon-----------------------\r\n",
	"++  1--Enable iBeacon function ,  APP: Wechat          ++\r\n",
	"*********************************************************\r\n",
	"---------------------------Eddystone---------------------\r\n",
	"++  2--Enable Eddystone Uri,    APP: EddystoneValidator++\r\n",
	"++  3--Enable Eddystone Uid,    APP: EddystoneValidator++\r\n",
	"++  4--Enable Eddystone Tlm,    APP: EddystoneValidator++\r\n",
	"++  5--Enable Remote function, 1  key function         ++\r\n",
	"*********************************************************\r\n",
	"++  0--Display all command                             ++\r\n",
	"---------------------------------------------------------\r\n",
};


/* Private function prototypes -----------------------------------------------*/


/*******************************************************************************
* Function	 :		main																									 
* Parameter  :		void																						
* Returns	 :		void			
* Description:														
* Note: 	 :																													 
*******************************************************************************/
void main(void)
{
	uint8_t temp0=0;
	//init mcu system 
    Init_System();
    Rx_Buffer[Rx_Tx_Buffer_Cnt] = 0;
    Rx_Tx_Buffer_Cnt = 0;
    while(1)
    {
		//rx data . change work mode .  
		if((Rx_Tx_Buffer_Cnt == 1) && (Work_Mode == Work_Mode_Null))
		{
			Work_Mode = Rx_Buffer[0];
			Rx_Buffer[0] = 0;
			Rx_Tx_Buffer_Cnt = 0;
		}


		switch(Work_Mode) 
		{
			case Work_Mode_Null:
				
				break;
			case Work_Mode_Help:
				
				for(temp0=0;temp0<11;temp0++)
				{
					Uart_Send_String(FunctionDisplay[temp0]);
				}

				Uart_Send_String("\r\n");
				Uart_Send_String("\r\n");
				Uart_Send_String("\r\n");
				Uart_Send_String("\r\n");
				Uart_Send_String("\r\n");
				Uart_Send_String("\r\n");

				Work_Mode = Work_Mode_Null;

			break;
			case Work_Mode_iBeacon:
			case Work_Mode_Eddystone_Uri:
			case Work_Mode_Eddystone_Uid:
			case Work_Mode_Eddystone_Tlm:
			case Work_Mode_Remote:
				//BLE initnal
				BLE_Init();
				//send 
				BLE_Beacon();		
			break;

			default:
			break;	
		}
    }
}

