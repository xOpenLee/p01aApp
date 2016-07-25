#ifndef __serialscreen___
#define  __serialscreen___
#include "stdint.h"

#define SCREEN_CMD_DATA_LEN (256)
typedef struct screen_cmd{
	short head;
	unsigned char len;
	char cmd;
	char data[SCREEN_CMD_DATA_LEN];
}SCREEN_CMD;


#define WRITE_CTRL_REG (0x80)
#define READ_CTRL_REG  (0x81)
#define WRITE_DATA_REG (0x82)
#define READ_DATA_REG  (0x83)

/*帧的一些字节定义*/
#define FH0 0x5A 
#define FH1 0xA5
#define RD_LEN 0x00
#define ADR 0x00




/*寄存器空间定义*/
#define Version 0x00  /*DGUS版本号*/
#define LED_NOW 0X01  /*LED亮度控制寄存器，0x00~0x40*/
#define BZ_IME  0X02  /*蜂鸣器鸣叫控制寄存器，单位10ms*/
#define PIC_ID  0x03  /*2字节 读：当前显示页面ID 写：切换到指定页面(页面控制)*/
#define TP_Flag 0x05  /*0x5a=触摸屏坐标有更新；其他触摸屏坐标未更新*/
#define TP_Status 0x06  /*0x01=第一次按下 0x03一直按压中 0x02=抬起 其他=无效*/
#define TP_Position 0x07 /*4字节 触摸屏按压坐标位置：X_H:L Y_H:L*/
#define TPC_Enable 0x0B /*0x00=触控不起用 其他=启用*/

#define ScreenEnable  0x01 
#define ScreenDisable 0x00

/*错误代码变量地址*/
#define err_num           0x0007

#define erro_num          0x050A

extern uint8_t record_time[20];
extern uint8_t pageunitil;
extern int16_t CoinTotoal_t;
extern int8_t	selltime_hour,selltime_hour_t,selltime_hour_r;
extern int8_t	selltime_minute, selltime_minute_t,selltime_minute_r;
extern int8_t  selltime_second_r;
extern uint32_t sellsecond_remain;

extern void SerialScreenInit(void);
extern void RecvScreenData(void);

#endif
