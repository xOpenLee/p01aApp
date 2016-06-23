#ifndef __serialscreen___
#define  __serialscreen___
#include "stdint.h"
/*֡��һЩ�ֽڶ���*/
#define FH0 0x5A 
#define FH1 0xA5
#define RD_LEN 0x00
#define ADR 0x00

#define Logo_interface                 0x00  /*logo����*/
#define Err_interface                  0x01  /*������ʾ����*/
#define DoorOpened_interface           0x03  /*������ʾ����*/
#define OnlymachieInit_interface       0x04  /*��е�ֳ�ʼ������*/
#define SignInFunction_interface       0x05  /*����ǩ������*/
#define Szt_GpbocAutoCheckIn_interface 0x06  /*������ǩ������*/
#define SellMeal_TimeSet_interface     0x07  /*�۲�ʱ�����ý���*/
#define SellMeal_TimeWait_interface    0x09  /*�۲͵ȴ�����*/
#define Coinset_interface              0x0B  /*Ӳ������*/  
#define MealInput_interface            0x0D  /*�Ų�����ѡ��*/
#define MealNumChoose_interface        0x0F  /*��Ʒ����ѡ��*/ 
#define MealNumChoose1_interface       0x10  /*ѡ��һ��*/
#define MealNumChoose2_interface       0x11  /*ѡ�˶���*/
#define MealNumChoose3_interface       0x12  /*ѡ������*/
#define Acount_interface               0x14  /*�������*/
#define PayWithVip_interface           0x15  /*��Ա������*/
#define SwipingCard_interface          0x16  /*ˢ������*/
#define PayWithCash_interface          0x17  /*�ֽ����*/
#define TicketPrint_interface          0x1A  /*СƱ��ӡ����*/
#define Password_interface             0x1C  /*�����������*/
#define TemperatureSet_interface       0x1E  /*�¶����ý���*/
#define Data_synchronization           0x20  /*����ͬ��*/
#define UserAbonamalRecord_interface   0x24  /*�쳣�û���¼����*/

#define Menu1st_interface              0x26  /*�˵�һ��Ʒ��������*/
#define MealSet1st_interface           0x29  /*�˵�һ��Ʒ���ý���*/
#define Menu2nd_interface              0x2B  /*�˵�����Ʒ��������*/
#define MealSet2nd_interface           0x2E  /*�˵�����Ʒ���ý���*/
#define Menu3rd_interface              0x30  /*�˵�����Ʒ��������*/
#define MealSet3rd_interface           0x33  /*�˵�����Ʒ���ý���*/
#define Menu4th_interface              0x35  /*�˵��Ĳ�Ʒ��������*/
#define MealSet4th_interface           0x38  /*�˵��Ĳ�Ʒ���ý���*/
#define Menu5th_interface              0x3A  /*�˵����Ʒ��������*/
#define MealSet5th_interface           0x3D  /*�˵����Ʒ���ý���*/
#define Menu6th_interface              0x3F  /*�˵�����Ʒ��������*/
#define MealSet6th_interface           0x42  /*�˵�����Ʒ���ý���*/

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

/*ʣ���Ʒ������ַ*/
#define meal1st_left     0x0021 /*��һ�ݲ�Ʒʣ���λ��*/
#define meal2nd_left	   0x0022 /*�ڶ��ݲ�Ʒʣ���λ��*/
#define meal3rd_left     0x0023 /*�����ݲ�Ʒʣ���λ��*/
#define meal4th_left     0x0024 /*���ķݲ�Ʒʣ���λ��*/
//
/*װ��ѡ��,1:����,2:���,3:ȷ��,4:ȡ��,5:����*/
#define mealinput_choose  0x001A

/*������������ַ*/
#define err_num           0x0007

/*ϵͳ����,1:�¶�����;2:��Ʒ����*/
#define admin_set         0x0006

/*���볤���ı���ʾ*/
#define password_show     0x0005 

/*�������������ַ*/
#define password          0x0004 

/*Ʊ�ݴ�ӡ������ַ,1:��;2:��*/
#define bill_print        0x0003 

/*֧����ʽ������ַ,1:�ֽ�֧��;2:���п�֧��;3:����֧ͨ��*/
#define payment_method    0x0002

/*ѡ�ͽ���ѡ�������ַ:��������ѡ��*/
#define mealcnt_choose    0x0001

/*������ѡ�ͽ���*/
#define meal_choose       0x0000

/*��������ʾ*/
#define  payment_coin     0x0500 //Ӳ��֧����� /*�Ѹ�����Ǯ*/
#define  payment_bill     0x0501 //ֽ��֧�����
#define  payment_card     0x0502 //ˢ��֧�����
#define  wait_payfor      0x0503 //����ȴ�ʱ��

/*���ͽ������*/
#define  mealout_totle    0x0504 //��Ʒ��������
#define  mealout_already  0x0505 //��Ʒ�ѳ�������

/*������ʾ*/
#define erro_num          0x050A //�۲�ֹͣ����


#define  mealtotoal_cost     0x0506  //�ܼ�
#define  current_temprature  0x0507  //ʵʱ�¶���ʾ����
#define  temprature_set      0x0508  //�¶����ñ���
#define  count_dowm          0x0509  //ѡ�͵���ʱ

/*��ѡ��Ʒ����������*/
#define meal_choose_cnt      0x0030  

/*��Ʒװ�����*/
#define row_1st   0x0011 
#define row_2nd   0x0012
#define row_3rd   0x0013
#define floor_num 0x0014
#define meal_num  0x0015

//�˱ұ���
#define coins_in     0x0050 //�˱һ��ڵ�Ӳ������   
#define coins_input  0x0051 //Ӳ�ҷ�������
#define coins_retain 0x0052 //����Ӳ������
#define coins_back	 0x0053 //��ǰ�˱�����
#define coins_key    0x0054 //�˱ҵİ���
#define coins_clear  0x0057 //����ܼ�Ӳ�����ΰ���

#define caedbalence_cancel    0x0055  //ˢ��ȡ������
#define record_clear          0x0056  //�����¼����

//ˢ��������
#define cardbalence_before    0x0060  //ˢ��Ǯ���
#define amountof_consumption  0x0065  //�������ѽ��
#define cardbalence_after     0x006A  //ˢ�������

//ͬ������
#define sync_column1st_name   0x4500
#define sync_column2nd_name   0x4600
#define sync_column3rd_name   0x4700
#define sync_column4th_name   0x4800
#define sync_column1st_number 0x4900
#define sync_column2nd_number 0x4A00
#define sync_column3rd_number 0x4B00
#define sync_column4th_number 0X4C00

//�������Ʒ����
#define menu_name_1st         0x4000
#define menu_name_2nd         0x4100
#define menu_name_3rd         0x4200
#define menu_name_4th         0x4300
//����û�ж��͵���ʾ
#define menu_name_none        0x4D00

//�������Ʒ������ʾ
#define menu_price_1st        0x4410
#define menu_price_2nd        0x4420
#define menu_price_3rd        0x4430
#define menu_price_4th        0x4440

//�۲�ʱ�����ý���
#define set_sellmeal_hour     0x4E00    //�۲�ʱ�����õ�Сʱ����
#define set_sellmeal_minute   0x4E01    //�۲�ʱ�����õķ��ӱ���
#define set_sellmeal_key      0x4E02    //�۲�ʱ�����õİ�������

//�ȴ��۲͵�ʱ����ʾ����
#define wait_sellmeal_hour    0x4E03    //�ȴ��۲���ʾ��Сʱ����
#define wait_sellmeal_minute  0x4E04    //�ȴ��۲���ʾ�ķ��ӱ���
#define wait_sellmeal_second  0x4E05    //�ȴ��۲���ʾ�����ӱ���

//�û������¼����
#define record_column1st_name   0x5000 //��һ������
#define record_column2nd_name   0x5100 //�ڶ�������
#define record_column3rd_name   0x5200 //����������
#define record_column4th_name   0x5300 //����������

#define record_column1st_cnt_t  0x5400 //��һ����Ʒ����
#define record_column2nd_cnt_t  0x5500 //�ڶ�����Ʒ������
#define record_column3rd_cnt_t  0x5600 //��������Ʒ������
#define record_column4th_cnt_t  0x5700 //��������Ʒ������

#define record_column1st_cnt    0x5800 //��һ����Ʒ�ѳ�������
#define record_column2nd_cnt    0x5900 //�ڶ�����Ʒ�ѳ�����
#define record_column3rd_cnt    0x5A00 //��������Ʒ�ѳ�����
#define record_column4th_cnt    0x5B00 //��������Ʒ�ѳ�����

#define record_UserActPayAlready     0x5C00  //�û��Ѹ���
#define record_UserActPayBack        0x5D00  //�û�Ӧ�˱�
#define record_UserActPayBackAlready 0x5E00  //�����û�Ӳ����

#define record_UserDataTime          0x5F00  //����ʱ����ʾ


extern uint8_t record_time[20];
extern uint8_t pageunitil;
extern int16_t CoinTotoal_t;
extern int8_t	selltime_hour,selltime_hour_t,selltime_hour_r;
extern int8_t	selltime_minute, selltime_minute_t,selltime_minute_r;
extern int8_t  selltime_second_r;
extern uint32_t sellsecond_remain;
void ClearUserBuffer(void);
void PageChange(uint8_t page);
void ReadPage(void);
void ScreenControl(uint8_t cmd);
void DispMenu(void);
void DispMenuNone(void);
void DispLeftMeal(void);
void DealSeriAceptData(void);
void VariableChage(uint16_t Variable,uint16_t Value);	
void DisplayAbnormal(uint8_t *abnomal_code);
void VariableChagelong (uint16_t Variable,uint32_t Value);
void DisplayRecordTime(void);
void DisplayTimeCutDown(void);
void SetScreenRtc(void);
void MenuChange(uint8_t MenuNO);
uint32_t GetMealPrice(uint8_t meal_type,uint8_t count);
uint32_t GetMealLastPrice(uint8_t meal_type,uint8_t count);
extern void SerialScreenInit(void);
#endif
