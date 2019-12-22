#include "epos.h"

Uint32	epos_err_LK;
Uint32	epos_err_LH;
Uint32	epos_err_RK;
Uint32	epos_err_RH;

Uint32 pvt_ip_hip[62]={0,-1288,-2576,-3864,-5152,-6440,-7728,-9016,-10304,-11592,-12880,-14168,-15460,-16500,-16719,-15794,-13519,-9875,-5048,612,6675,12724,18433,23600,28137,32036,35321,38018,40146,41726,42791,43397,43620,43543,43238,42754,42115,41322,40361,39202,37808,36139,34159,31854,29244,26391,23387,20335,17318,14382,11525,8720,5939,3186,501,-2049,-4405,-6549,-8518,-10381,-12195,-13936};
Uint32 pvt_iv_hip[62]={0,-121,-121,-121,-121,-121,-121,-121,-121,-121,-121,-121,-125,-64,29,148,279,401,498,556,574,555,512,455,395,336,280,226,173,123,77,38,6,-19,-38,-53,-67,-82,-99,-119,-143,-171,-201,-231,-257,-276,-285,-286,-279,-271,-265,-262,-260,-256,-246,-231,-211,-192,-178,-172,-168,-156};
Uint32 pvt_it_hip[62]={200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200};

Uint32 pvt_ip_knee[62]={0,758,1516,2274,3032,3790,4548,5306,6064,6822,7580,8338,9097,11095,14125,18863,25770,34811,45337,56192,66019,73638,78345,80018,79005,75872,71145,65157,58070,50021,41299,32437,24169,17251,12249,9374,8455,9040,10570,12539,14578,16447,17972,18987,19337,18932,17812,16183,14358,12652,11251,10154,9197,8183,7013,5778,4733,4172,4274,5011,6178,7552};
Uint32 pvt_iv_knee[62]={0,71,71,71,71,71,71,71,71,71,71,71,159,225,354,542,753,932,1023,990,833,584,297,23,-204,-375,-506,-615,-712,-793,-835,-815,-723,-565,-369,-172,-7,108,171,192,186,162,122,66,-2,-73,-133,-167,-170,-147,-116,-93,-90,-102,-116,-112,-79,-23,	41,93,122,135};
Uint32 pvt_it_knee[62]={200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200};

Uint32 pvt_ip_hip_left[62]={0,-3757,-7513,-11270,-15026,-18783,-22539,-26296,-30052,-33809,-37565,-41322,-41322,-40361,-39202,-37808,-36139,-34159,-31854,-29244,-26391,-23387,-20335,-17318,-14382,-11525,-8720,-5939,-3186,-501,2049,4405,6549,8518,10381,12195,13936,15460,16500,16719,15794,13519,9875,5048,-612,-6675,-12724,-18433,-23600,-28137,-32036,-35321,-38018,-40146,-41726,-42791,-43397,-43620,-43543,-43238,-42754,-42115};
Uint32 pvt_iv_hip_left[62]={-200,-352,-352,-352,-352,-352,-352,-352,-352,-352,-352,-200,82,99,119,143,171,201,231,257,276,285,286,279,271,265,262,260,256,246,231,211,192,178,172,168,156,125,64,-29,-148,-279,-401,-498,-556,-574,-555,-512,-455,-395,-336,-280,-226,-173,-123,-77,-38,-6,19,38,53,67};
Uint32 pvt_it_hip_left[62]={200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200};

Uint32 pvt_ip_knee_left[62]={0,800,1600,2400,3200,4000,4800,5600,6400,7200,8000,8800,9040,10570,12539,14578,16447,17972,18987,19337,18932,17812,16183,14358,12652,11251,10154,9197,8183,7013,5778,4733,4172,4274,5011,6178,7552,9097,11095,14125,18863,25770,34811,45337,56192,66019,73638,78345,80018,79005,75872,71145,65157,58070,50021,41299,32437,24169,17251,12249,9374,8455};
Uint32 pvt_iv_knee_left[62]={0,77,77,77,77,77,77,77,77,77,77,77,108,171,192,186,162,122,66,-2,-73,-133,-167,-170,-147,-116,-93,-90,-102,-116,-112,-79,-23,41,93,122,135,159,225,354,542,753,932,1023,990,833,584,297,23,-204,-375,-506,-615,-712,-793,-835,-815,-723,-565,-369,-172,-7};
Uint32 pvt_it_knee_left[62]={200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200};


/*
*输入：EPOS结构体，串口对象fd1.
*功能：启动EPOS，并且设置最大的跟踪误差，最大的速度、加速度、负加速度，以及快速停止的负加速度设定
*/
void Epos_ParamInit(Epos* epos, int fd1)
{
    Epos_Write(epos, OD_CTRL_WORD, 0x00, 0x0080,fd1);
//    Epos_Delay(EPOS_DELAY2);
    Epos_Write(epos, OD_MAX_FLLW_ERR, 0x00, MAX_F_ERR,fd1);
//    Epos_Delay(EPOS_DELAY1);
    Epos_Write(epos, OD_MAX_P_VELOCITY, 0x00, MAX_P_V,fd1);
//    Epos_Delay(EPOS_DELAY1);
    Epos_Write(epos, OD_P_ACCELERATION, 0x00, epos->acc,fd1);
//    Epos_Delay(EPOS_DELAY1);
    Epos_Write(epos, OD_P_DECELERATION, 0x00, epos->dec,fd1);
//    Epos_Delay(EPOS_DELAY1);
    Epos_Write(epos, OD_QS_DECELERATION, 0x00, QDEC,fd1);
//    Epos_Delay(EPOS_DELAY1);

    printf("Epos_ParamInit\n");
}


/*
*输入：EPOS结构体，CAN设备(节点)序号 CAN_ID，节点的ID：NODE_ID1，串口对象 fd1
*功能：启动EPOS，并且设置最大的跟踪误差，最大的速度、加速度、负加速度，以及快速停止的负加速度设定
*/
void Epos_SInit(Epos* epos1, Uint8 CAN_ID, Uint8 NODE_ID1, int fd1)
{
    epos1->b_init = 0;
    epos1->CAN_Handles = NULL;
    epos1->node_ID = NODE_ID1;
    epos1->b_init = 1;

    epos1->cur_mode = MODE_NONE;
    epos1->opt = 0x001f;
    epos1->acc = MAX_ACC;
    epos1->dec = MAX_DEC;
    epos1->b_need_shutdown = 0;

    Epos_ParamInit(epos1,fd1);

    printf("Epos_SInit\n");
}


/* write parameter to buffer, and to Epos controller through UART

*/
void Epos_Write(Epos* epos,Uint16 Index,Uint8 SubIndex,Uint32 param,int fd1)
{
    epos->buf.msg_id.bit.STDMSGID = 0x600 + epos->node_ID;						//CANOPEN 的 客户端发送命令 SOD报文ID
    epos->buf.low_4byte = 0x22 + ((Uint32)Index << 8) + ((Uint32)SubIndex<< 24);//CAN中的8个数据字节，中的低四个字节定义
    epos->buf.high_4byte = param;		//SDO 携带的实际数据
    epos->buf.DataLen = 8;
    epos->buf.IsExtend = 0;
    epos->buf.IsRemote = 0;

    UART2CAN_write(epos,fd1);

    printf("Epos_Write\n");
}

BOOL Epos_start_Read(Epos* epos,Uint16 Index,Uint8 SubIndex,int fd1)
{
    BOOL ret_val = 0;
    epos->buf.msg_id.bit.STDMSGID = 0x600 + epos->node_ID;
    epos->buf.low_4byte = 0x40 + ((Uint32)Index << 8) + ((Uint32)SubIndex << 24);
    epos->buf.high_4byte = 0x00;
    epos->buf.DataLen = 8;
    epos->buf.IsExtend=0;
    epos->buf.IsRemote=0;
    ret_val = UART2CAN_write(epos,fd1);

    printf("Epos_start_Read\n");
	
    return ret_val;
}

BOOL Epos_end_Read(Epos* epos,Uint32* p_param,int fd1)
{
    UART2CAN_read(epos,fd1);
//*p_param = epos->buf.low_4byte;
    *p_param = epos->buf.high_4byte;		//TOCHECK: 检查字节顺序

//    printf("param=%x\n",*p_param);
    //     printf("Epos_end_Read\n");

}

void Epos_Write_PVT(Epos* epos,Uint16 Index,Uint8 SubIndex,Uint32 param1,Uint32 param2,Uint8 param3,int fd1)
{
    epos->buf.msg_id.bit.STDMSGID = 0x600 + epos->node_ID;
    epos->buf.low_4byte = 0x21 + ((Uint32)Index << 8) + ((Uint32)SubIndex << 24);
    epos->buf.high_4byte = (Uint32)0x08;
    epos->buf.DataLen = 8;
    epos->buf.IsExtend = 0;
    epos->buf.IsRemote = 0;
    UART2CAN_write(epos,fd1);
    Epos_Delay(EPOS_DELAY3);

    epos->buf.msg_id.bit.STDMSGID = 0x600 + epos->node_ID;
    epos->buf.low_4byte = 0x00 + (param1 << 8);
    epos->buf.high_4byte = (param1 >> 24)+(param2 << 8);
    epos->buf.DataLen = 8;
    epos->buf.IsExtend = 0;
    epos->buf.IsRemote = 0;
    UART2CAN_write(epos,fd1);
    Epos_Delay(EPOS_DELAY3);

    epos->buf.msg_id.bit.STDMSGID = 0x600 + epos->node_ID;
    epos->buf.low_4byte = 0x11 + (param3 << 8);
    epos->buf.high_4byte = 0;
    epos->buf.DataLen = 8;
    epos->buf.IsExtend = 0;
    epos->buf.IsRemote = 0;
    UART2CAN_write(epos,fd1);
    Epos_Delay(EPOS_DELAY3);

    printf("Epos_Write_PVT\n");

}



// delay time us
void Epos_Delay(Uint32 time)
{
    usleep(time);
}


BOOL UART2CAN_write(Epos* epos,int fd1)
{
    UART_MSG uartMSG;
    uartMSG.startMark = 0xAA;
    uartMSG.IsExtend = epos->buf.IsExtend;
    uartMSG.IsRemote = epos->buf.IsRemote;
    uartMSG.DataLen = epos->buf.DataLen;
    uartMSG.nodeID = changeIntOrder(epos->buf.msg_id.bit.STDMSGID);
    uartMSG.high_4byte = epos->buf.high_4byte;
    uartMSG.low_4byte = epos->buf.low_4byte;

    write(fd1, &uartMSG, sizeof(uartMSG));

    usleep(30000);


}


BOOL UART2CAN_read(Epos* epos,int fd1)
{
    usleep(30000);
	
    Uint8 buf[16];		//数组元素为一个字节，共16个字节
    Uint32 tmp;
    int lenR;
	
    lenR = read(fd1, buf, 16);
    printf("lenR = %d\n",lenR);


    if(lenR == 16)
    {
        tmp=0;
        tmp|=((Uint32)buf[12])<<24;
        tmp|=((Uint32)buf[13])<<16;
        tmp|=((Uint32)buf[14])<<8;
        tmp|=(Uint32)buf[15];
        epos->buf.low_4byte=tmp;

        tmp=0;
        tmp|=((Uint32)buf[8]);//<<24
        tmp|=((Uint32)buf[9])<<8;
        tmp|=((Uint32)buf[10])<<16;
        tmp|=(Uint32)buf[11]<<24;
        epos->buf.high_4byte=tmp;

    }
    else
    {
        epos->buf.low_4byte=0;
        epos->buf.high_4byte=0;
		
        printf("read epos error\n");
    }
}



/* open the device port, return -1 if fails or fd if successes

parameters:
arg - choose serial devicefile in mini2440 /dev/ttySACX(X=0 1 2 or 3)
baud - Definition of baud rate
*/
int uart_init(int arg, int baud)
{
    char port[20];
    struct termios Opt;

    int fd1;
    int uartbiit[50] =
    {
        B115200, B9600, B19200, B4800, B2400, B1200
    };                                    //Definition of baud rate

    sprintf(port, "/dev/ttySAC%d", arg);  //The serial port device file in mini2440
    //is /dev/ttySACX(X=0 1 2 or 3)

    fd1 = open(port, O_RDWR);             //open the port

    if (fd1 < 0)
    {
        return -1;
    }

    tcgetattr(fd1, &Opt);                 //Initial

    tcflush(fd1, TCIFLUSH);

    cfsetispeed(&Opt, uartbiit[baud]);    //set baud rate

    cfsetospeed(&Opt, uartbiit[baud]);


    Opt.c_cflag |= CS8;                   //set data bits

    Opt.c_cflag &= ~PARENB;               //no check

    Opt.c_oflag &= ~(OPOST);              //choose the initial output

    Opt.c_cflag &= ~CSTOPB;               //one stop bit

    Opt.c_lflag &= ~(ICANON | ISIG | ECHO | IEXTEN);  //set the driver of serial port

    Opt.c_iflag &= ~(INPCK | BRKINT | ICRNL | ISTRIP | IXON);

    Opt.c_cc[VMIN] = 0;                   //The minimum character

    Opt.c_cc[VTIME] = 0;                  //waiting time



    if (tcsetattr(fd1, TCSANOW, &Opt) != 0)  //Initialize the parameters
    {
        perror("SetupSerial!\n");

        close(fd1);

        return -1;
    }

    return fd1;

}


Uint32 changeIntOrder(Uint32 param)
{
    Uint32 a=param;
    Uint32 tmp=0x0;

    tmp|=(a<<24);
    tmp|=((a<<8)&0x00FF0000);
    tmp|=((a>>8)&0x0000FF00);
    tmp|=(a>>24);

    return tmp;
}

