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

//static unsigned char adv_data[18] = {2,1,4, 0x0a,0x09,0x4d,0x41,0x43,0x52,0x4f,0x47,0x49,0x47,0x41,0x03,0xff,0x00,0x09};
//BLE ADV_data .
//static uint8_t adv_data[30] = {0x02,0x01,0x04, 0x1a,0xff,0x4c,0x00,2,0x15, 0xfd,0xa5,0x06,0x93,0xa4,0xe2,0x4f,0xb1,0xaf,0xcf,0xc6,0xeb,0x07,0x64,0x78,0x25, 0x27,0x32,0x52,0xa9, 0xB6};
//static uint8_t adv_data[30] = {0x02,0x01,0x04, 0x1a,0xff,0x4c,0x00,2,0x15, 0xfd,0xa5,0x06,0x93,0xa4,0xe2,0x4f,0xb1,0xaf,0xcf,0xc6,0xeb,0x07,0x64,0x78,0x25, 0x27,0x38,0x9d,0x85, 0xB6};

static uint8_t adv_data[30] = {0};

//iBeacon data format
static uint8_t iBeacon_adv_data[] = 
{
	/*
	02 # Number of bytes that follow in first AD structure
	01 # Flags AD type
	04 # Flags value
	1A # Number of bytes that follow in second (and last) AD structure
	FF # Manufacturer specific data AD type
	4C 00 # Company identifier code (0x004C == Apple)
	02 # Byte 0 of iBeacon advertisement indicator
	15 # Byte 1 of iBeacon advertisement indicator
	*/
	//{
	0x02,															/* length 0x02*/
	BLE_GAP_AD_TYPE_FLAGS,											/* AD type = 01 */
	GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED|GAP_ADTYPE_FLAGS_GENERAL, 	/* LE Mode = 0x06 */
	//}
	

	0x1a,															/* length 0x1a*/
	BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA,						/* AD type = 0xFF Manufacturer Specific Data */
	/*CompanyID (AppleID 0x004C)https://www.bluetooth.com/specifications/assigned-numbers/company-Identifiers*/
	0x4c,0x00,														/* CompanyID = 0x004C */									
	0x02,															/* iBeacon flag = 0x02 */
	0x15, 															/* length 0x15 length :0x15 21byte  (16B UUID+ 2B major, 2B minor, 1B Txpower)*/
	/*UUID */
	0xfd,0xa5,0x06,0x93,0xa4,0xe2,0x4f,0xb1,0xaf,0xcf,0xc6,0xeb,0x07,0x64,0x78,0x25, 
	/***************User set***********************/
	0x27,0x38,														/*Major*/
	0x9d,0x85,														/*Minjo*/
	0xB6															/*Txpower*/
	/***************User End***********************/				

};

//Beacon remote data format
static uint8_t Beacon_Key_Press_adv_data[] = 
{
	0x02,															/* length 0x02*/
	BLE_GAP_AD_TYPE_FLAGS,											/* AD type = 01 */
	GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED|GAP_ADTYPE_FLAGS_GENERAL, 	/* LE Mode = 0x06 */


	0x0a,															/* length 0x1a*/
	BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME,							/* AD type = 0x09*/
	'K','e','y','-','P','r','e','s', 's',							/* use Ascii */
	

	0x03,															/* length 0x03*/
	BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA,						/* AD type = 0xFF */
	/***************User set***********************/
	0x20,0x0b,														
	/***************User End***********************/
};

//Beacon remote data format
static uint8_t Beacon_Key_uP_adv_data[] = 
{
	0x02,															/* length 0x02*/
	BLE_GAP_AD_TYPE_FLAGS,											/* AD type = 01 */
	GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED|GAP_ADTYPE_FLAGS_GENERAL, 	/* LE Mode = 0x06 */

	0x0a,															/* length 0x1a*/
	BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME,							/* AD type = 0x09*/
	'K','e','y','-','-','-','-','U', 'p', 

	0x03,															/* length 0x03*/
	BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA,						/* AD type = 0xFF */
	/***************User set***********************/
	0x10,0x0b,
	/***************User End***********************/
};

//Eddystone data format
static uint8_t Eddystone_Uri_adv_data[]=
{
	/***************User End***********************/
	/*Service Data - 16-bit UUID. */
	//BLE_GAP_AD_TYPE_SERVICE_DATA,
	/*Google 16bit UUID */
	//0xAA,0xFE,
	//{
    0x02, 															/* length 0x02*/
    BLE_GAP_AD_TYPE_FLAGS, 											/* AD type = 01 */
    GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED|GAP_ADTYPE_FLAGS_GENERAL, 	/* LE Mode = 0x06 */
	//}

	//{
    /* Eddystone(https://github.com/google/eddystone/blob/master/protocol-specification.md) */
    0x03, 															/* length 0x03 */
    BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_COMPLETE, 					/* AD type = Complete list of 16-bit UUIDs available */
    0xAA,															/* Eddystone service FEAA */
    0xFE,
	//}

	//{
    0x0b, 															/* length 12byte*/
    BLE_GAP_AD_TYPE_SERVICE_DATA, 									/* AD type = Service Data type value */
    0xAA, 															/* Eddystone service FEAA */
    0xFE,
  
    /* Eddystone-URL(https://github.com/google/eddystone/tree/master/eddystone-url) */
    0x10,                   										/* Frame Type: URL */
    0xb6,                   										/* Ranging Data */
    0x00,                   										/* URL Scheme: https:// */
    'j','b','5','1',//'s','z','o','k','l','e', 
    0x0a,
	//}
};

/*- INDICATION data -*/
uint8_t Eddystone_Uid_adv_data[] = {
	/*Service Data - 16-bit UUID. */
	//BLE_GAP_AD_TYPE_SERVICE_DATA,
	/*Google 16bit UUID */
	//0xAA,0xFE,
	//{
    0x02, 															/* length 0x02*/
    BLE_GAP_AD_TYPE_FLAGS, 											/* AD type = 01 */
    GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED|GAP_ADTYPE_FLAGS_GENERAL, 	/* LE Mode = 0x06 */
	//}


	//{
    /* Eddystone(https://github.com/google/eddystone/blob/master/protocol-specification.md) */
    0x03, 															/* length 0x03 */
    BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_COMPLETE, 					/* AD type = Complete list of 16-bit UUIDs available */
    0xAA,															/* Eddystone service FEAA */
    0xFE,
	//}

	
	//{
    0x17, 															/* length 12byte*/
    BLE_GAP_AD_TYPE_SERVICE_DATA, 									/* AD type = Service Data type value */
    0xAA, 															/* Eddystone service FEAA */
    0xFE,

	
    0x00,               											/* Frame Type: UID */
    0xE7,              	 											/* Ranging Data */
    0x16, 0xF7, 0x42, 0xf6, 0xA8, 0x8C, 0x57, 0x5B, 0x53, 0x24,		/* Namespace:MSB 10Bytes*/
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01,                             /* Instance */
    0x00,               											/* Reserved */
    0x00,               											/* Reserved */
	//}
};



uint8_t Eddystone_Tlm_adv_data[] = {
	/*Service Data - 16-bit UUID. */
	//BLE_GAP_AD_TYPE_SERVICE_DATA,
	/*Google 16bit UUID */
	//0xAA,0xFE,
	//{
    0x02, 															/* length 0x02*/
    BLE_GAP_AD_TYPE_FLAGS, 											/* AD type = 01 */
    GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED|GAP_ADTYPE_FLAGS_GENERAL, 	/* LE Mode = 0x06 */
	//}


	//{
    /* Eddystone(https://github.com/google/eddystone/blob/master/protocol-specification.md) */
    0x03, 															/* length 0x03 */
    BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_COMPLETE, 					/* AD type = Complete list of 16-bit UUIDs available */
    0xAA,															/* Eddystone service FEAA */
    0xFE,
	//}


	//{
    0x11, 															/* length 12byte*/
    BLE_GAP_AD_TYPE_SERVICE_DATA, 									/* AD type = Service Data type value */
    0xAA, 															/* Eddystone service FEAA */
    0xFE,
  
    /* Eddystone-TLM(https://github.com/google/eddystone/tree/master/eddystone-tlm) */
    0x20,                   										/* Frame Type: TLM */
    0x00,                   										/* TLM Version */
    0x0b, 0x54,             										/* Battery voltage 2900[mV] */
    0x0b, 0x54,             										/* Beacon Temperature */
    0x00, 0x00, 0x10, 0x00, 										/* Advertising PDU count */
    0x01, 0x00, 0x00, 0x00, 										/* Time since power-on or reboot */
    //}

};





/* Private function prototypes -----------------------------------------------*/



/*******************************************************************************
* Function   :     	BLE_Mode_Sleep	                                                                                                     
* Parameter  :     	void                       
* Returns    :     	void            
* Description:      
* Note:      : 		BLE enter sleep mode. current: 3ua
*******************************************************************************/
void BLE_Mode_Sleep(void)
{
	uint8_t	temp0[4];
       
    temp0[0] = 0x02;
    temp0[1] = 0xff; 
    temp0[2] = 0xff;
    temp0[3] = 0xff;

	SPI_Write_Buffer(SLEEP_WAKEUP,temp0,4);
}
/*******************************************************************************
* Function   :     	BLE_Mode_Wakeup	                                                                                                     
* Parameter  :     	void                       
* Returns    :     	void            
* Description:      
* Note:      : 		BLE reg:0x00--0x1f. write operation must or 0x20
*******************************************************************************/
void BLE_Mode_Wakeup(void)
{
    SPI_Write_Reg(SLEEP_WAKEUP|0x20, 0x01);
}

/*******************************************************************************
* Function   :     	BLE_Set_StartTime	                                                                                                     
* Parameter  :     	uint32_t                     
* Returns    :     	void            
* Description:      
* Note:      : 
*******************************************************************************/
void BLE_Set_StartTime(uint32_t htime)
{
	uint8_t temp0[3];
	uint32_t temp1 = htime;
	
    temp0[0] = temp1 & 0xFF;
    temp0[1] = (temp1>>8) & 0xFF;
    temp0[2] = (temp1>>16) & 0xFF;
	
	SPI_Write_Buffer(START_TIME,temp0,3);  
}
/*******************************************************************************
* Function   :     	BLE_GetClock	                                                                                                     
* Parameter  :     	uint32_t *lfclk, uint32_t *hfclk                     
* Returns    :     	void            
* Description:      
* Note:      : 
*******************************************************************************/
void BLE_Get_Clock(uint32_t *lfclk, uint32_t *hfclk)
{
	uint8_t temp0[6];
	//uint16_t temp1=0;
	

	BLE_CSN_CLR();
	
	SPI_Write_Byte(CLK_CNT);
	temp0[0]=SPI_Read_Byte();
	temp0[1]=SPI_Read_Byte();
	temp0[2]=SPI_Read_Byte();
	temp0[3]=SPI_Read_Byte();
	temp0[4]=SPI_Read_Byte();
	temp0[5]=SPI_Read_Byte(); 
	BLE_CSN_SET();
	
    *lfclk = ((uint32_t)temp0[5] << 16) + ((uint32_t)temp0[4] << 8) + temp0[3];
    *hfclk = ((uint32_t)temp0[2] << 16) + ((uint32_t)temp0[1] << 8) + temp0[0]; 
	
}	

/*******************************************************************************
* Function   :     	BLE_Set_GenericTimer	                                                                                                     
* Parameter  :     	uint32_t lfclk                    
* Returns    :     	void            
* Description:      
* Note:      : 
*******************************************************************************/
void BLE_Set_GenericTimer(uint32_t lfclk)
{
	uint8_t temp0[6];
    temp0[0] = 0x04;  
    temp0[1] = lfclk & 0xFF;
    temp0[2] = (lfclk >> 8) & 0xFF;
    temp0[3] = (lfclk >> 16) & 0xFF;
    temp0[4] = 0x00;
    temp0[5] = 0x00;

	SPI_Write_Buffer(SLEEP_WAKEUP,temp0,6);  
}

/*******************************************************************************
* Function   :     	BLE_Set_TimeOut	                                                                                                     
* Parameter  :     	uint32_t data_us                   
* Returns    :     	void            
* Description:      TX/RX timeout .unit:us
* Note:      : 
*******************************************************************************/
void BLE_Set_TimeOut(uint32_t data_us)
{
	uint8_t temp0[3];

	if(data_us < 10000)
	{
        temp0[0] = data_us & 0xff;
        temp0[1] = (data_us >> 8) & 0xff;
        temp0[2] = 0;
        SPI_Write_Buffer(TIMEOUT, temp0, 3);

	}
	else
	{
		SPI_Read_Buffer(TIMEOUT,temp0,3);
		if(temp0[2] == 0)
		{
			temp0[2] = 1;
			SPI_Write_Buffer(TIMEOUT, temp0, 3);
		}
	}
}

/*******************************************************************************
* Function   :     	void BLE_send(void)	                                                                                                     
* Parameter  :     	void                    
* Returns    :     	void            
* Description:      configure reg data. ready ble send data.
* Note:      : 
*******************************************************************************/
void BLE_send(void)
{
	uint8_t temp0[4];
	
    SPI_Write_Reg(0x20, 0x00);
    SPI_Write_Reg(0x50, 0x53);
	SPI_Write_Reg(0x33,0x01);
	SPI_Write_Reg(0x35,0x01);

	//Calibration frequency .
	temp0[0] = 0xcf;//bf; 
	temp0[1] = 0x00;  
	SPI_Write_Buffer(0x14,temp0,2);
	
	temp0[0] = 0x10;
	temp0[1] = 0x08;
	SPI_Write_Buffer(0x1e,temp0,2);
	temp0[0] = 0x80;
	temp0[1] = 0x00;
	temp0[2] = 0x01;
	SPI_Write_Buffer(0x12,temp0,3);
	temp0[0] = 0x01;
	temp0[1] = 0x02;
	SPI_Write_Buffer(0x13,temp0,2);
	
	temp0[0] = 0x00;
	temp0[1] = 0x80;
	temp0[2] = 0x01;
	temp0[3] = 0x00;
	SPI_Write_Buffer(0x10,temp0,4);

    SPI_Write_Reg(0x2f, 0x01);
    
	temp0[0] = 0x00;
	temp0[1] = 0x6e;
	SPI_Write_Buffer(0x11,temp0,2); 
	SPI_Write_Reg(0x3d,0x00);
	SPI_Write_Reg(0x3d,0x02);

	
	Delay_us(10);
		
	SPI_Write_Reg(0x3d,0x03);
	
	Delay_us(40);
	
	SPI_Write_Reg(0x3d,0x01);
	
	Delay_us(120);

	//set BLE TX Power
	temp0[0] = 0x01;
	temp0[1] = BLE_TX_POWER; 
	SPI_Write_Buffer(0x0f,temp0,2);
		
	temp0[0] = 0x88;
	temp0[1] = 0x80;
	SPI_Write_Buffer(0x12,temp0,2);
	temp0[0] = 0x00;
	temp0[1] = 0x2e;
	temp0[2] = 0x08;
	temp0[3] = 0x0f;
	SPI_Write_Buffer(0x11,temp0,4);

	temp0[0] = 0x01;
	temp0[1] = 0x00;
	SPI_Write_Buffer(0x13,temp0,2);
	
	temp0[0] = 0x00;
	temp0[1] = 0x80;
	temp0[2] = 0x01;
	temp0[3] = 0x10;
	SPI_Write_Buffer(0x10,temp0,4);
		
	SPI_Write_Reg(0x50, 0x56);
	SPI_Write_Reg(0x20,0x01);
}

/*******************************************************************************
* Function   :     	void BLE_Send_done(void)	                                                                                                     
* Parameter  :     	void               
* Returns    :     	void            
* Description:      BLE send data finish . need configure reg data.
* Note:      : 
*******************************************************************************/
void BLE_Send_done(void)
{
	uint8_t temp0[3];

    SPI_Write_Reg(0x50, 0x53);
    SPI_Write_Reg(0x31,0x24);	
    temp0[0] = 0x02;
    temp0[1] = 0x00;
    SPI_Write_Buffer(0x0f, temp0, 2);
    
    SPI_Write_Reg(0x3e,0x20);
    temp0[0] = 0x00;
    temp0[1] = 0x00;
    temp0[2] = 0x81;
    SPI_Write_Buffer(0x12, temp0, 3);
    temp0[0] = 0x81;
    temp0[1] = 0x00;
    SPI_Write_Buffer(0x13, temp0, 2);
    
    Delay_us(100);
    
	SPI_Write_Reg(0x33,0x01);
    SPI_Write_Reg(0x35,0x00);
        
    SPI_Write_Reg(0x50, 0x56);
}

/*******************************************************************************
* Function   :     	BLE_Init                                                                                                     
* Parameter  :     	void                  
* Returns    :     	void            
* Description:      power on .BLE must initnal reg .
* Note:      : 		delay 30ms .
*******************************************************************************/
void BLE_Init(void)
{
	uint8_t status;
	uint8_t data_buf[3];
	uint8_t ble_Addr[6];
	
	//Delay_ms(30);

	Uart_Send_String("BLE init \r\n");

    SPI_Write_Reg(0x50, 0x51);
	SPI_Write_Reg(0x50, 0x53);
    SPI_Write_Reg(0x35, 0x00);  
    
    do{   
        data_buf[0] = 0;
        data_buf[1] = 0;
        data_buf[2] = 1;
        SPI_Write_Buffer(0x00, data_buf, 3);

        SPI_Write_Reg(0x36, 0x8e);  
        SPI_Write_Reg(0x37, 0x8e);  
        SPI_Write_Reg(0x38, 0x88);  
        SPI_Write_Reg(0x39, 0x8e);  

        SPI_Write_Reg(0x50, 0x51);
       
        SPI_Read_Reg(0x1e);
        
        status = SPI_Read_Reg(CHIP_OK);
    }while(status != 0x80);
	
	//read chip version
   	status = SPI_Read_Reg(0x1e);
	Uart_Send_String("chip version=");
	Uart_Send_Byte(status);
	Uart_Send_String("\r\n");

	//power down,tx  //add this for hot reset
	SPI_Write_Reg(0X20, 0x08); 
	//1Mbps
	SPI_Write_Reg(0X26, 0x06);
	//power up
    SPI_Write_Reg(0X20, 0x0a); 
	//xtal off for v16w1
    SPI_Write_Reg(0x3d, 0x18); 
    SPI_Write_Reg(0x50, 0x56); 

    BLE_Mode_Sleep();
    
	//read BLE address. BLE MAC Address
    SPI_Read_Buffer(0x08, ble_Addr, 6);
	
	Uart_Send_String("BleAddr=");
	Uart_Send_Byte(ble_Addr[5]);
	Uart_Send_Byte(ble_Addr[4]);
	Uart_Send_Byte(ble_Addr[3]);
	Uart_Send_Byte(ble_Addr[2]);
	Uart_Send_Byte(ble_Addr[1]);
	Uart_Send_Byte(ble_Addr[0]);
	Uart_Send_String("\r\n");
	
}

/*******************************************************************************
* Function   :     	BLE_Beacon                                                                                                    
* Parameter  :     	void                  
* Returns    :     	void            
* Description:      Beacon data .process .
* Note:      : 
*******************************************************************************/
void BLE_Beacon(void)
{
	uint8_t bank_buf[6];
	uint8_t ch = 37;
	uint8_t status;
	uint32_t lfclk,tx_start,wakeup_time, hfclk;
	uint8_t temp0=0;

	//Workmode change .ready ble data
	if(Work_Mode == Work_Mode_iBeacon)
	{
		for(temp0=0;temp0<(sizeof(iBeacon_adv_data)/sizeof(uint8_t));temp0++)
		{
			adv_data[temp0] = iBeacon_adv_data[temp0];
		}
	}
	
	else if(Work_Mode == Work_Mode_Eddystone_Uri)
	{
		for(temp0=0;temp0<(sizeof(Eddystone_Uri_adv_data)/sizeof(uint8_t));temp0++)
		{
			adv_data[temp0] = Eddystone_Uri_adv_data[temp0];
		}
	}
	
	else if(Work_Mode == Work_Mode_Eddystone_Uid)
	{
		for(temp0=0;temp0<(sizeof(Eddystone_Uid_adv_data)/sizeof(uint8_t));temp0++)
		{
			adv_data[temp0] = Eddystone_Uid_adv_data[temp0];
		}
	}

	else if(Work_Mode == Work_Mode_Eddystone_Tlm)
	{
		for(temp0=0;temp0<(sizeof(Eddystone_Tlm_adv_data)/sizeof(uint8_t));temp0++)
		{
			adv_data[temp0] = Eddystone_Tlm_adv_data[temp0];
		}
	}

	else if(Work_Mode == Work_Mode_Remote)
	{
		if(KEY_GET() != RESET)
		{
			for(temp0=0;temp0<(sizeof(Beacon_Key_Press_adv_data)/sizeof(uint8_t));temp0++)
			{
				adv_data[temp0] = Beacon_Key_Press_adv_data[temp0];
			}
		}
		else
		{
			for(temp0=0;temp0<(sizeof(Beacon_Key_uP_adv_data)/sizeof(uint8_t));temp0++)
			{
				adv_data[temp0] = Beacon_Key_uP_adv_data[temp0];
			}


		}
	}

	
		
    LED_RED_ON();
	
	
	//set BLE TX default channel:37.38.39
	SPI_Write_Reg(CH_NO|0X20, ch);
	//BLT FIFO write adv_data . max len:31 byte
	SPI_Write_Buffer(W_TX_PAYLOAD, adv_data, sizeof(adv_data));
	
	//set BLT PDU length:adv_data+6 mac adress.  
	bank_buf[0] = 0x02;//0x42;
	bank_buf[1] = sizeof(adv_data)+6;
	
	//PDU TYPE: 2  non-connectable undirected advertising . tx add:random address
	SPI_Write_Buffer(ADV_HDR_TX, bank_buf, 2);

	Uart_Send_String("BLE_Beacon mode ");
    Uart_Send_Byte(Work_Mode-'0');
    Uart_Send_String("\r\n");
	
    //clear all interrupt
    SPI_Write_Reg(INT_FLAG|0X20, 0xff);
    //BLE Wakeup mode
    BLE_Mode_Wakeup();
    
	while(1)
	{
		//	//Workmode change .
		if((Rx_Tx_Buffer_Cnt == 1))
		{
			Work_Mode = Rx_Buffer[0];
			Rx_Tx_Buffer_Cnt = 0;
			//sleep(power down)
            SPI_Write_Reg(0x50, 0x51); 
            SPI_Write_Reg(0x20, 0x08);
            SPI_Write_Reg(0x50, 0x56); 
            BLE_Mode_Sleep(); 
            //exit loop . 
			break;
		}

		//remote .key press & up data 
		if(Work_Mode == Work_Mode_Remote)
		{   
			if(KEY_GET() == RESET)
			{
				for(temp0=0;temp0<(sizeof(Beacon_Key_Press_adv_data)/sizeof(uint8_t));temp0++)
				{
					adv_data[temp0] = Beacon_Key_Press_adv_data[temp0];
				}
			}
			else
			{
				for(temp0=0;temp0<(sizeof(Beacon_Key_uP_adv_data)/sizeof(uint8_t));temp0++)
				{
					adv_data[temp0] = Beacon_Key_uP_adv_data[temp0];
				}

			}

		}

		

		//BLE IRQ LOW 
		if (!BLE_IRQ_GET())
		{
			//clear interrupt flag
			status = SPI_Read_Reg(INT_FLAG);
			SPI_Write_Reg(INT_FLAG|0X20, status);
			
			
			//Uart_Send_String("BLE_IRQ LOW work status=");
			//Uart_Send_Byte(status);
			//Uart_Send_String("\r\n");
			
			//Tx done process
            if(status == 0xFF)
			{
				BLE_Mode_Sleep();
				BLE_Send_done();
				
				continue;
            }
			

			//BLE sleep process
            if(status & INT_TYPE_SLEEP)//sleep
            {
                LED_GREEN_OFF();
                                
				//BLE channel 
                if (++ch > 39)
                {
                    ch = 37; 
                }
				
                BLE_Get_Clock(&lfclk, &hfclk);
                //wakeup_time = lfclk + (INTERVAL * LFCLK_625US);
                
                wakeup_time = lfclk + BLE_INTERVAL_TIME;//(INTERVAL * LFCLK_1MS);
                //wakeup_time
                bank_buf[0] = 0x00; 
                bank_buf[1] = wakeup_time & 0xff;
                bank_buf[2] = (wakeup_time >> 8) & 0xff;
                bank_buf[3] = (wakeup_time >> 16) & 0xff;
                SPI_Write_Buffer(SLEEP_WAKEUP, bank_buf, 4);

                SPI_Write_Reg(CH_NO|0X20, ch);
                SPI_Write_Reg(0x50, 0x51); 
                switch(ch)
                {
                    case 37:
                        SPI_Write_Reg(0x25, 0x02);
                        break;
                    case 38:
                        SPI_Write_Reg(0x25, 0x1a);
                        break;
                    case 39:
                        SPI_Write_Reg(0x25, 0x50);
                        break;
                }
                SPI_Write_Reg(0x50, 0x56);

   				//BLT FIFO write adv_data . max len:31 byte
                SPI_Write_Buffer(W_TX_PAYLOAD, adv_data, sizeof(adv_data));

            }
            else if (status & INT_TYPE_WAKEUP)	//BLE wakeup process
            {
                LED_GREEN_ON();
                
				BLE_send();
                //BLE work mode:TX mode
                SPI_Write_Reg(MODE_TYPE|0X20, RADIO_MODE_ADV_TX);
				
                tx_start = BLE_START_TIME;//HFCLK_1MS*TX_PRE;
                BLE_Set_StartTime(tx_start);
            }
            else
            {
                //other interrupt BLE Enter sloop
                BLE_Mode_Sleep();
            }

	        ///printf(" %x", status);
		
		}
	}
    
    LED_RED_OFF();
    LED_GREEN_OFF();
	
}
