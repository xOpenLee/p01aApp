#include <stdio.h>
#include "serialscreen.h"
#include "utils.h"
#include "uart.h"
#include "xuartlite.h"
#include "microblaze_sleep.h"

XUartLite g_ScreenUartLite;
struct screen_cmd g_ScreenCmd;

#define Null 0x00


/*������16λ�洢����ַ�ֽ�Ϊ2��8λ����*/
union ScreenRam
{
		int16_t	 	adress ;
		int8_t  	adr[2] ;
}myunion;

/*������16λ�洢����ַ�ֽ�Ϊ2��8λ����*/
union ScreenRamLong
{
		uint32_t	 	adress ;
		int8_t  	adr[4] ;
}myunion_long;


/*дָ���Ĵ���֡*/
const uint8_t RegisterWrite[7]={ 
							FH0 , FH1 , /*֡ͷ2�ֽ� */
							0x04 , /*���� �������������*/
							0x80 , /*ָ����ַд�Ĵ�������*/
							ADR  , /*�Ĵ�����ַ*/
							0x00 ,0x00 /*����*/
							//0x00 , 0x00	/*CRCУ����β*/
							};

/*��ָ���Ĵ���֡*/
const uint8_t RegisterRead[6]={
							FH0 , FH1 , /*֡ͷ2�ֽ� */
							0x03 , /*���� �������������*/
							0x81 ,  /*ָ����ַ���Ĵ�������*/
							ADR  , /*�Ĵ�����ַ*/
							RD_LEN , /*����*/
							//0x00 , 0x00	/*CRCУ����β*/	
							};
	
/*д�����洢��֡*/							
const uint8_t VariableWrite[8]={
							FH0 , FH1 , /*֡ͷ2�ֽ� */
							0x00 , /*���� �������������*/	
							0x82 , /*ָ����ַ��ʼд�����ݴ�(������)�������洢��*/
							0x00 , 0x00 ,	/*�����洢�ռ�2�ֽ�*/
							0x00 , 0x00   /*����*/
							//0x00 , 0x00  	/*CRCУ����β*/
							}; 

/*�������洢��֡*/	
const uint8_t VariableRead[7]={
							FH0 , FH1 , /*֡ͷ2�ֽ� */
							0x04 , /*���� �������������*/
							0x83 , /*�ӱ����洢��ָ����ַ��ʼ����RD_LEN����������*/
							0x00 , 0x00 ,	/*�����洢�ռ�2�ֽ�*/
							RD_LEN , /*����*/
							//0x00 , 0x00  	/*CRCУ����β*/
							};	

const uint8_t ABC[20]={
							FH0 , FH1 , /*֡ͷ2�ֽ� */
							0x05 , /*���� �������������*/	
							0x82 , /*ָ����ַ��ʼд�����ݴ�(������)�������洢��*/
							0x40 , 0x00 ,	/*�����洢�ռ�2�ֽ�*/
							0xBA , 0xA0   /*����*/
							};	
const uint8_t rtc_write[13]={
							FH0 , FH1 , /*֡ͷ2�ֽ� */
							0x0A , /*���� �������������*/	
							0x80 , /*ָ����ַ��ʼд�����ݴ�(������)�������洢��*/
							0x1F , 0x5A ,	/*�����洢�ռ�2�ֽ�*/
							0x00 , 0x00 ,0X00 ,   /*����*/
							0X00 ,/*����*/
							0x00 , 0x00 ,0x00 /*ʱ��*/
							};
#include "stdio.h"

uint8_t *mystrcat(uint8_t *dest, const uint8_t *src, uint8_t length)
{
	int i=0;
	for(i=0;i<length;i++)
	{
		dest[6+i] = src[i];
	}
	return dest;
}


 /*******************************************************************************
 * ��������:VariableChage                                                                    
 * ��    ��:�ı�ָ��������ֵ                                                              
 *                                                                               
 * ��    ��:page                                                                    
 * ��    ��:��                                                                     
 * ��    ��:void                                                               
 * �޸�����:2016��7��13��
 *******************************************************************************/ 							
void VariableChage(uint16_t Variable,uint16_t Value)							
{
	uint8_t temp[8]={0};  //��Ŵ������ݵ���ʱָ��
	memcpy(temp,VariableWrite,sizeof(VariableWrite));
	temp[2]= 5;
	myunion.adress= Variable; 
	temp[4]= myunion.adr[1];
	temp[5]= myunion.adr[0];
	myunion.adress= Value; 
	temp[6]= myunion.adr[1];
	temp[7]= myunion.adr[0];		
	UartSend(&g_ScreenUartLite, temp, sizeof(temp));
}							

 /*******************************************************************************
 * ��������:VariableChagelong                                                                    
 * ��    ��:�ı�ָ��������ֵ                                                              
 *                                                                               
 * ��    ��:page                                                                    
 * ��    ��:��                                                                     
 * ��    ��:void                                                               
 * �޸�����:2016��7��13��
 *******************************************************************************/ 							
void VariableChagelong (uint16_t Variable,uint32_t Value)							
{
	uint8_t temp[10]={0};  //��Ŵ������ݵ���ʱָ��
	memcpy(temp,VariableWrite,sizeof(VariableWrite));
	temp[2]= 7;
	myunion.adress= Variable; 
	temp[4]= myunion.adr[1];
	temp[5]= myunion.adr[0];
	myunion_long.adress= Value;
	temp[6]= myunion_long.adr[3];
	temp[7]= myunion_long.adr[2];					
	temp[8]= myunion_long.adr[1];
	temp[9]= myunion_long.adr[0];		
	UartSend(&g_ScreenUartLite,temp,sizeof(temp));
}
 /*******************************************************************************
 * ��������:RegisterChage                                                                   
 * ��    ��:�ı�ָ��������ֵ                                                              
 *                                                                               
 * ��    ��:page                                                                    
 * ��    ��:��                                                                     
 * ��    ��:void                                                               
 * �޸�����:2016��7��13��
 *******************************************************************************/ 							
void RegisterChage(uint8_t Register,uint16_t Value)							
{
	uint8_t temp[8]={0};  //��Ŵ������ݵ���ʱָ��
	memcpy(temp,RegisterWrite,sizeof(RegisterWrite));
	temp[3]= Register;
	myunion.adress=Value;
	temp[5]= myunion.adr[1];
	temp[6]= myunion.adr[0];		
	UartSend(&g_ScreenUartLite,temp,sizeof(temp));
}	

 /*******************************************************************************
 * ��������:RegisterChage                                                                   
 * ��    ��:�ı�ָ��������ֵ                                                              
 *                                                                               
 * ��    ��:page                                                                    
 * ��    ��:��                                                                     
 * ��    ��:void                                                               
 * �޸�����:2016��7��13��
 *******************************************************************************/ 							
void ScreenControl(uint8_t cmd)							
{
	uint8_t temp[8]={0};  //��Ŵ������ݵ���ʱָ��
	memcpy(temp,RegisterWrite,sizeof(RegisterWrite));
	temp[3]= TPC_Enable;
	temp[5]= cmd ;	//0x00 �ر�
	UartSend(&g_ScreenUartLite,temp,sizeof(temp));
}	
 

 /*******************************************************************************
 * ��������:DisplayAbnormal                                                               
 * ��    ��:��ʾ������                                                   
 *                                                                               
 * ��    ��:abnomal_code �ַ���                                                                  
 * ��    ��:��                                                                     
 * ��    ��:void                                                               
 * �޸�����:2016��7��13��
 *******************************************************************************/ 
void DisplayAbnormal(uint8_t *abnomal_code)
{
	uint8_t i=0;
	uint8_t temp[20]={0};  //��Ŵ������ݵ���ʱ����
	memcpy(temp,VariableWrite,sizeof(VariableWrite));
	temp[2]= 7; //  ���ݳ���Ϊ4λ
	myunion.adress= erro_num; 
	temp[4]= myunion.adr[1];
	temp[5]= myunion.adr[0];
	for(i=0;i<4;i++) temp[i+6]=abnomal_code[i];
	UartSend(&g_ScreenUartLite, temp,sizeof(temp));
}


 /*******************************************************************************
 * ��������:PageChange                                                                     
 * ��    ��:�����л�ͼƬ����                                                              
 *                                                                               
 * ��    ��:page                                                                    
 * ��    ��:��                                                                     
 * ��    ��:void                                                               
 * �޸�����:2016��7��13��
 *******************************************************************************/ 	
uint8_t pageunitil= 0;
void PageChange(uint8_t page)
{
	uint8_t temp[7]={0};
	memcpy(temp,RegisterWrite,sizeof(RegisterWrite));	
	temp[4]=	PIC_ID;	
	temp[6]=  page;
	pageunitil = page;
	UartSend(&g_ScreenUartLite,temp,sizeof(temp));
}

 /*******************************************************************************
 * ��������:ReadPage                                                                     
 * ��    ��:��ȡ��ǰҳ,���ݴ�����DealSeriAceptData�д���                                                           
 *                                                                               
 * ��    ��:��                                                                    
 * ��    ��:                                                                     
 * ��    ��:                                                             
 * �޸�����:2016��7��13��
 *******************************************************************************/ 	
void ReadPage(void)
{
	uint8_t temp[6]={0};
	memcpy(temp,RegisterRead,sizeof(RegisterRead));	
	temp[4]=	PIC_ID;	
	UartSend(&g_ScreenUartLite,temp,sizeof(temp));
}


 /*******************************************************************************
 * ��������:RecRegisterValues                                                                   
 * ��    ��:��ȡ�Ĵ�����ֵ                                                                                                                          
 * ��    ��:�Ĵ�����ַ,�Ĵ�������,�Ĵ������ݳ���                                                                  
 * ��    ��:��                                                                     
 * ��    ��:void                                                               
 * �޸�����:2016��7��13��
 *******************************************************************************/ 
uint8_t current_page =0;//��ǰҳ��
void RecRegisterValues(uint8_t VariableAdress,uint8_t *VariableData,uint8_t length)
{
	if(VariableAdress==PIC_ID)//��ȡ�жϵ�ǰ��ҳ���ID
	{
		current_page =VariableData[length-1];
		if(current_page!=pageunitil)
		{
			//PageChange(cmd_page);
		}
	}
}
 /*******************************************************************************
 * ��������:DealSeriAceptData                                                                   
 * ��    ��:����ӵ�����Ļ���ص�����                                                        
 *          ���ʵ���������������ݣ�0xA5 0XA5 0X5A                                                                           
 * ��    ��:��                                                                   
 * ��    ��:��                                                                     
 * ��    ��:void                                                               
 * �޸�����:2016��7��13��
 *******************************************************************************/ 	
void DealSeriAceptData(void)
 {
	uint8_t i;
	uint8_t temp,temp1,length,checkout;
	uint8_t RegisterAdress=0;
	int16_t VariableAdress=0;
	
	uint8_t Rx3DataBuff[10]={0};/*����һ�������С��?����Խ��(out of bounds),?�ɱ䳤������*/
	uint8_t RegisterData[5]={0};  //�Ĵ�����������
	uint8_t VariableData[5]={0};  //������������
	uint8_t RegisterLength= 0;   //�Ĵ������ݵĳ���
	uint8_t VariableLength= 0;   //�������ݵĳ���

	while(UartReceiveBuffer(&g_ScreenUartLite) >=9) //��ȡ��������С��ֱ��������������
	{	
		printf("#INFO: >> UartReceiveBuffer\r\n");
		if(UartReceiveBuffer(&g_ScreenUartLite)==1)
		{	
			if(temp==FH0)	//ƥ��֡ͷ��һ���ֽ�
			{ 
loop:			if(UartRecv(&g_ScreenUartLite, &temp1, sizeof(temp1))==1)
				{
					if(temp1==FH1)  //ƥ��֡ͷ�ڶ����ֽڣ�
					{
						if(UartRecv(&g_ScreenUartLite, &length, sizeof(length)) == 1)  //��ȡ�����ֽڳ���
						{
							checkout =1;//��λ��ʼ��ȡ���������ݱ�־	
						}	
					}
					else if(temp1==FH0)	goto loop; //�����������0xA5������ж���һ���ֽ��Ƿ�Ϊ0x5A
				}
			}
		}
		if(checkout==1) //ֱ����ȡ���ݳ��ȣ�Ȼ�������
		{
			checkout =0;  //��λ��־
			for(i=0;i<length;i++) UartRecv(&g_ScreenUartLite, Rx3DataBuff+i, sizeof(length));
			if(Rx3DataBuff[0]==0x81)  //���Ĵ�����������
			{
				RegisterAdress =Rx3DataBuff[1];
				for(i=0;i<(length-2);i++)
				RegisterData[i]=Rx3DataBuff[2+i];
				//�����޸�������ݵĹ���
				RecRegisterValues(RegisterAdress,RegisterData,RegisterLength);
			}
			else if(Rx3DataBuff[0]==0x83) //�����ݴ洢����������
			{
				myunion.adr[1] =Rx3DataBuff[1]; //�п�����С��ģʽ�����
				myunion.adr[0] =Rx3DataBuff[2];
				VariableAdress =myunion.adress;
				VariableLength =Rx3DataBuff[3];
				for(i=0;i<(length-4);i++)
				VariableData[i]=Rx3DataBuff[4+i];
				//�����޸ı�����ַ���ݵĹ���
				//ChangeVariableValues(VariableAdress,VariableData,VariableLength);
			 }
		 } 
	 }		

}

static int PrintCmdData(struct screen_cmd *ScreenCmd)
{
	unsigned char i = 0;
	if (NULL == ScreenCmd)
		return -1;
	printf("#INFO: Print Cmd Data.\r\n");
	printf("\t head: 0x%04x\r\n", ScreenCmd->head);
	printf("\t len: 0x%x\r\n", ScreenCmd->len);
	printf("\t cmd: 0x%02x\r\n", ScreenCmd->cmd);
	printf("\t data: ");
	for (i = 0; i < ScreenCmd->len - 1; i++)
		printf(" 0x%02x", ScreenCmd->data[i]);
	printf("\r\n");
	return 0;

}

static int SendScreenData(unsigned char cmd, char* data, unsigned char DataLen)
{

	int ret = 0, send_len = 0;
	if ((cmd < WRITE_CTRL_REG) ||  (cmd > READ_DATA_REG)) {
		printf("#ERR: SendScreenData cmd = 0x%x\r\n", cmd);
		return -1;
	}

	if (DataLen > SCREEN_CMD_DATA_LEN) {
		printf("#ERR: SendScreenData data len too long  0x%x\r\n", DataLen);
		return -2;
	}

	g_ScreenCmd.head = 0xA55A;
	g_ScreenCmd.len = DataLen + sizeof(cmd);
	g_ScreenCmd.cmd = cmd;
	memcpy(&g_ScreenCmd.data, data, DataLen);
	send_len = sizeof(g_ScreenCmd.head) + sizeof(g_ScreenCmd.len)
			   + sizeof(g_ScreenCmd.cmd) + DataLen;

	PrintCmdData(&g_ScreenCmd);
	ret = UartSend(&g_ScreenUartLite, &g_ScreenCmd, send_len);
	if (ret != send_len) {
		printf("#ERR: SendScreenData UartSend = %d Err.\r\n", ret);
		return -3;
	}

	return 0;
}

static int ReadScreenCtrlReg(unsigned char RegAddr, unsigned char RegDataLen)
{
	unsigned char send[2] = {0};
	send[0] = RegAddr;
	send[1] = RegDataLen;
	return SendScreenData(READ_CTRL_REG, &send, sizeof(send));
}

static int WriteScreenCtrlReg(unsigned char RegAddr, unsigned char RegData)
{
	unsigned char send[2] = {0};
	send[0] = RegAddr;
	send[1] = RegData;
	return SendScreenData(WRITE_CTRL_REG, &send, sizeof(send));
}


static int WriteScreenDataReg(unsigned short RegAddr,
								unsigned short *data, unsigned char DataLen)
{
	unsigned char send[SCREEN_CMD_DATA_LEN] = {0}, i = 0;
	unsigned short swap = 0;
	if(data == NULL) {
		printf("#ERR: data NULL\r\n");
		return -1;
	}

	memcpy(&send[0], RegAddr, sizeof(RegAddr));
	for(i = 0; i < DataLen; i++) {
		swap = SWAP_16(data[i]);
		memcpy(&send[sizeof(RegAddr) + i*sizeof(swap)], &swap, DataLen);
	}


	return SendScreenData(WRITE_DATA_REG, &send, sizeof(RegAddr) + DataLen);
}


static int ReadScreenDataReg(unsigned short RegAddr, unsigned char DataLen)
{
	unsigned char send[SCREEN_CMD_DATA_LEN] = {0};

	memcpy(&send[0], RegAddr, sizeof(RegAddr));
	send[sizeof(RegAddr)] = DataLen;

	return SendScreenData(WRITE_DATA_REG, &send, sizeof(RegAddr) + sizeof(DataLen));
}



void RecvScreenData(void)
{
	unsigned char recv[SCREEN_CMD_DATA_LEN];
	unsigned short ret = 0, i = 0;

	while(1) {
#if 0
		ret = UartRecv(&g_ScreenUartLite, &recv, sizeof(recv));
		MB_Sleep(10);
		if( ret >= 5) {

			for(i = 0; i < ret; i++)
				printf("#INFO: UartRecv recv[%d] = 0x%02x\r\n", i , recv[i]);

			if((recv[0] == FH0) && (recv[1] == FH1)) {
				memcpy(&g_ScreenCmd, recv, ret);
				PrintCmdData(&g_ScreenCmd);
			}else {
				printf("#ERR: CMD recv err.\r\n");
			}
		}
#else
		for(i = 0; i < 100; i++) {
			ret = WriteScreenDataReg(0x00, &i, sizeof(i));
			MB_Sleep(1000);
		}
#endif
	}
}


/*******************************************************************************
* ��������:SerialScreenInit
* ��    ��: ��������ʼ��
*
* ��    ��:��
* ��    ��:��
* ��    ��:void
* �޸�����:2016��7��13��
*******************************************************************************/
void SerialScreenInit(void)
{
	UartOpen(&g_ScreenUartLite, XPAR_AXI_UARTLITE_1_DEVICE_ID);
}

