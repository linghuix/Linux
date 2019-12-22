#include "epos.h"
#include <math.h>

#define pi 3.1415

int main()
{
	//open UART
    int fd;
	Uint8 NODE_ID;
	NODE_ID = 1;
	
    if ((fd = uart_init(2, 1)) < 0){
        printf("open uart error\n");
        return -1;
    }
	
	//LK left knee, LH left hip joint.
    status_LK=0,status_LH=0,status_RK=0,status_RH=0;

	// Epos controller structure 
    Epos	Controller;

    /********初始化EPOS*******/
    Epos_SInit(&Controller, NOT_USED,NODE_ID,fd);          		//set NODE_ID,写入基本设置值到Controller

    Epos_Write(&Controller,OD_CAN_BITRATE,0x00,0x00,fd);    	//set value = 0. set CAN bitrate 1M/s. 

    Epos_Delay(EPOS_DELAY2);
    printf("initial EPOS done!\n\n");


    /********使能EPOS*******/
    Epos_Write(&Controller,OD_OP_MODE,0x00,0xFF,fd);   				// position mode
    Epos_Delay(EPOS_DELAY2);

    Epos_Write(&Controller,OD_Max_Acceleration,0x00,4000,fd); 		//set ACC value
    Epos_Delay(EPOS_DELAY2);

    Epos_Write(&Controller,OD_CTRL_WORD,0x00,0x06,fd);				//Shut down
    Epos_Delay(EPOS_DELAY3);

    Epos_Write(&Controller,OD_CTRL_WORD,0x00,0x0F,fd);				//Switch on
    Epos_Delay(EPOS_DELAY3);

    printf("enable EPOS\n\n");
	

    /********EPOS复零位*******/
    Epos_Write(&Controller,PM_SET_VALUE,0x00,0x00,fd); 				//home position,设为0
    Epos_Delay(EPOS_DELAY3);

    printf("EPOS set 0\n\n");

    Epos_Delay(3000000);


	/********read angels*******/
    Uint32 pos=0;
    int x=0;
    while(1)
    {
        pos = 2000*sin(2*pi*x/50)+2000;						//从2000-4000变化
        Epos_Write(&LK,PM_SET_VALUE,0x00,pos,fd);
        printf("pose:%d\n",pos);
	    Epos_Delay(20000);									//delay 20ms
        x += 1;
        if( x==50 ){x = 0;}
    }

return 0;
}

