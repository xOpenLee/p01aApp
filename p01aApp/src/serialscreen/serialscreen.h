#ifndef __serialscreen___
#define  __serialscreen___
#include "stdint.h"

#define SCREEN_CMD_DATA_LEN (128)
typedef struct screen_cmd{
	short head;
	unsigned char len;
	unsigned char cmd;
	char data[SCREEN_CMD_DATA_LEN];
	unsigned short addr;
	unsigned char data_len;
	short val[SCREEN_CMD_DATA_LEN];
}SCREEN_CMD;


#define WRITE_CTRL_REG (0x80)
#define READ_CTRL_REG  (0x81)
#define WRITE_DATA_REG (0x82)
#define READ_DATA_REG  (0x83)

/*֡��һЩ�ֽڶ���*/
#define FH0 0x5A 
#define FH1 0xA5
#define RD_LEN 0x00
#define ADR 0x00




/*�Ĵ����ռ䶨��*/
#define Version 0x00  /*DGUS�汾��*/
#define LED_NOW 0X01  /*LED���ȿ��ƼĴ�����0x00~0x40*/
#define BZ_IME  0X02  /*���������п��ƼĴ�������λ10ms*/
#define PIC_ID  0x03  /*2�ֽ� ������ǰ��ʾҳ��ID д���л���ָ��ҳ��(ҳ�����)*/
#define TP_Flag 0x05  /*0x5a=�����������и��£���������������δ����*/
#define TP_Status 0x06  /*0x01=��һ�ΰ��� 0x03һֱ��ѹ�� 0x02=̧�� ����=��Ч*/
#define TP_Position 0x07 /*4�ֽ� ��������ѹ����λ�ã�X_H:L Y_H:L*/
#define TPC_Enable 0x0B /*0x00=���ز����� ����=����*/

#define ScreenEnable  0x01 
#define ScreenDisable 0x00

/*������������ַ*/
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
