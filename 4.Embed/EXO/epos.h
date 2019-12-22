#ifndef EPOS_H
#define EPOS_H

#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/types.h>
#include <linux/fb.h>
#include <math.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <termio.h>	//串口驱动
#include <syslog.h>	//Unix类系统日志
#include <pthread.h>//Linux 多线程头
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <semaphore.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <bits/signum.h>
#include <sys/resource.h>
#include <string.h>

//------------------------------------------------------------------------
//define variables
//------------------------------------------------------------------------

typedef char                    int8;
typedef int                     int16;
typedef long                    int32;
typedef unsigned char           Uint8;
typedef unsigned short int      Uint16;
typedef unsigned int            Uint32;
typedef unsigned long long      Uint64;
typedef float                   float32;
typedef long double             float64;
typedef Uint8                   BOOL;
typedef Uint16                  stcCAN;

#define NOT_USED 0

extern	Uint32	epos_err_LK;
extern	Uint32	epos_err_LH;
extern	Uint32	epos_err_RK;
extern	Uint32	epos_err_RH;

Uint32   buffer_size_LK;    // wuhaijie
Uint32   buffer_size_LH;   	// wuhaijie
Uint32   buffer_size_RK;
Uint32   buffer_size_RH;

Uint32	status_LK;			//0为未使能，1为PPM
Uint32	status_LH;
Uint32	status_RK;
Uint32	status_RH;

Uint32 pos_value_LK;
Uint32 pos_value_LH;
Uint32 pos_value_RK;
Uint32 pos_value_RH;

#define NODE_LK	(1)	/* epos 24/5的节点ID */
#define NODE_LH (2)	/* epos 70/10的节点ID */
#define NODE_RK	(3)	/* epos 24/5的节点ID */
#define NODE_RH	(4)	/* epos 70/10的节点ID */

#define PPMODE 0x01
#define MAX_ACC 50000
#define MAX_DEC 80000
#define MODE_NONE 0x00
#define MAX_F_ERR 80000
#define MAX_P_V 20000
#define QDEC 100000

#define PM_SET_VALUE 0x2062


extern	Uint32  pvt_ip_knee[62];
extern	Uint32  pvt_iv_knee[62];
extern  Uint32  pvt_it_knee[62];

extern	Uint32  pvt_ip_hip[62];
extern	Uint32  pvt_iv_hip[62];
extern  Uint32  pvt_it_hip[62];

extern	Uint32  pvt_ip_knee_left[62];
extern	Uint32  pvt_iv_knee_left[62];
extern  Uint32  pvt_it_knee_left[62];

extern	Uint32  pvt_ip_hip_left[62];
extern	Uint32  pvt_iv_hip_left[62];
extern  Uint32  pvt_it_hip_left[62];

// 枚举，类似于define. 参考手册见 EPOS2 Firmware Specification.pdf P110
enum E_OBJ_DICTIONARY
{
    OD_ERR_REG = 0x1001,	//error register, Index 0x1001, Sub-index 0x00, UNSIGNED8

    OD_ERR_HIS = 0x1003,	//error history, Index 0x1003,	number of entries 0x05
        SI_ERR_CNT = 0x00,	//number of errors
        SI_ERR_HIS1 = 0x01,	//error history [1],Index 0x1003,Sub-index 0x01, UNSIGNED32
        SI_ERR_HIS2 = 0x02, //error history [2],Index 0x1003,Sub-index 0x02, UNSIGNED32
        SI_ERR_HIS3 = 0x03, //error history [3],Index 0x1003,Sub-index 0x03, UNSIGNED32
        SI_ERR_HIS4 = 0x04,	//error history [4],Index 0x1003,Sub-index 0x04, UNSIGNED32
        SI_ERR_HIS5 = 0x05,	//error history [5],Index 0x1003,Sub-index 0x05, UNSIGNED32

    OD_STORE = 0x1010,		//Save all Parameters, Subindex 0x01, Type UNSIGNED32

    OD_CAN_BITRATE = 0x2001, //Subindex 0x00, Type UNSIGNED16

    OD_CURRENT_AVG = 0x2027, //Current Actual Value Averaged, Subindex 0x00,Type INTEGER16

    OD_CM_SET = 0x2030,	//Setting value of current regulator in current mode [mA], Sub-index 0x00, INTEGER16

    OD_ANALOG_IN = 0x207C,//analog inputs, number of entries 2
        SI_ANALOG1 = 0x01,	//analog input 1, Index 0x207C, Sub-index 0x01,Type INTEGER16, analog input 1 [mV].
        SI_ANALOG2 = 0x02,	//analog input 2, Index 0x207C, Sub-index 0x02,Type INTEGER16,The voltage measured at analog input 2 [mV].

    OD_CTRL_WORD = 0x6040,		/*controlword, UNSIGNED16,
                                  bit6 Operation mode specific: 0: Abs;  1: rel
                                 */
    OD_STATUS_WORD = 0x6041, //Statusword, Sub-index 0x00, UNSIGNED16

    OD_OP_MODE = 0x6060, 		//Modes of operation, Sub-index 0x00, NTEGER8
    OD_ACTUAL_POS = 0x6064,		//actual position, Sub-index 0x00, INTEGER32,

    OD_MAX_FLLW_ERR = 0x6065,	//Maximal following error, Sub-index 0x00, UNSIGNED32

    OD_CURRENT_VAL = 0x6078,	//Current Actual Value, Index 0x6078, Subindex 0x00,Type INTEGER16
    OD_TARGET_POS =	0x607A,		/*target position, Sub-index 0x00, INTEGER32,
                                  units steps (quadcounts = 4*Encoder Counts / Revolution)*/
    OD_MAX_P_VELOCITY = 0x607F,	//UNSIGNED32, [1, 25000]

    OD_P_VELOCITY =	0x6081,		//Profile velocity, Sub-index 0x00, UNSIGNED32, Unit:rpm
    OD_P_ACCELERATION = 0x6083, //profile acceleration, Sub-index 0x00,UNSIGNED32
    OD_P_DECELERATION = 0x6084,	//profile deceleration, Sub-index 0x00,UNSIGNED32
    OD_QS_DECELERATION =  0x6085, //quick stop deceleration, Sub-index 0x00, UINT32

	OD_Max_Acceleration = 0x60C5,

    OD_TARGET_VELOCITY = 0x60FF,  //target velocity, Sub-index 0x00, INTEGER32
    OD_MOTOR_DATA = 0x6410	//motor data, number of entries 0x06,具体含义参照Sub-index
};


#define EPOS_DELAY1  5000			//50us
#define EPOS_DELAY2  50000
#define EPOS_DELAY3  62500


struct  CANMSGID_BITS {        // bits  description
   Uint16      EXTMSGID_L:16;  // 0:15
   Uint16      EXTMSGID_H:2;   // 16:17
   Uint16      STDMSGID:11;    // 18:28
   Uint16      AAM:1;          // 29, The auto answer mode bit
   Uint16      AME:1;          // 30, The acceptance mask enable bit
   Uint16      IDE:1;          // 31, The identifier extension bit

};


/* Allow access to the bit fields or entire register */
union CANMSGID_REG {
   Uint32                all;
   struct CANMSGID_BITS  bit;
};


typedef struct CANFrame_t
{
    union CANMSGID_REG	msg_id;
    Uint32  low_4byte;
    Uint32  high_4byte;
    Uint8	DataLen;
    BOOL	IsExtend;
    BOOL	IsRemote;
}stcCANFrame;


typedef struct __Epos
{
    stcCAN* CAN_Handles;
    stcCANFrame buf;
    BOOL b_init;			//Epos是否初始化的标志
    Uint8 node_ID;
    Uint8 cur_mode;
    int32 opt;    			//用于保存PPMODE下的opt参数
    int32 acc;
    int32 dec;

    BOOL b_need_shutdown;	//是否需要关断epos对的标志
}Epos;


//UART data structure
typedef struct UART_MSG
{
    Uint8 startMark;
    Uint8 IsExtend;
    Uint8 IsRemote;
    Uint8 DataLen;
    Uint32 nodeID;
    Uint32  low_4byte;
    Uint32  high_4byte;

}UART_MSG;



//------------------------------------------------------------------------
//define functions
//------------------------------------------------------------------------
extern void     Epos_SInit(Epos* epos1,Uint8 CAN_ID,
	Uint8 NODE_ID1, int fd1);

extern void     Epos_Write(Epos* epos, Uint16 Index,
	Uint8 SubIndex, Uint32 param, int fd1);

extern BOOL     Epos_start_Read(Epos* epos,Uint16 Index,
	Uint8 SubIndex, int fd1);

extern BOOL     Epos_end_Read(Epos* epos, Uint32 *p_param, int fd1);

extern void     Epos_Write_PVT(Epos* epos, Uint16 Index, 
	Uint8 SubIndex, Uint32 param1, Uint32 param2, Uint8 param3, int fd1);

extern void     Epos_ParamInit(Epos* epos, int fd1);

extern void		Epos_Delay(Uint32 time);

BOOL            UART2CAN_write(Epos* epos, int fd1);

BOOL            UART2CAN_read(Epos* epos,int fd1);

Uint32          changeIntOrder(Uint32 param);

int             uart_init(int arg, int baud); 								//Initialize the UART

//------------------------------------------------------------------------
#endif // EPOS_H
