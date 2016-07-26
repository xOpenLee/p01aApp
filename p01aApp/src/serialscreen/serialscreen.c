#include <stdio.h>
#include "serialscreen.h"
#include "utils.h"
#include "uart.h"
#include "xuartlite.h"
#include "microblaze_sleep.h"

XUartLite g_ScreenUartLite;
struct screen_cmd g_ScreenCmd;

#define Null 0x00


/*将数据16位存储器地址分解为2个8位数据*/
union ScreenRam
{
		int16_t	 	adress ;
		int8_t  	adr[2] ;
}myunion;

/*将数据16位存储器地址分解为2个8位数据*/
union ScreenRamLong
{
		uint32_t	 	adress ;
		int8_t  	adr[4] ;
}myunion_long;


/*写指定寄存器帧*/
const uint8_t RegisterWrite[7]={ 
							FH0 , FH1 , /*帧头2字节 */
							0x04 , /*长度 包括命令和数据*/
							0x80 , /*指定地址写寄存器数据*/
							ADR  , /*寄存器地址*/
							0x00 ,0x00 /*数据*/
							//0x00 , 0x00	/*CRC校验侦尾*/
							};

/*读指定寄存器帧*/
const uint8_t RegisterRead[6]={
							FH0 , FH1 , /*帧头2字节 */
							0x03 , /*长度 包括命令和数据*/
							0x81 ,  /*指定地址读寄存器数据*/
							ADR  , /*寄存器地址*/
							RD_LEN , /*长度*/
							//0x00 , 0x00	/*CRC校验侦尾*/	
							};
	
/*写变量存储区帧*/							
const uint8_t VariableWrite[8]={
							FH0 , FH1 , /*帧头2字节 */
							0x00 , /*长度 包括命令和数据*/	
							0x82 , /*指定地址开始写入数据串(字数据)到变量存储区*/
							0x00 , 0x00 ,	/*变量存储空间2字节*/
							0x00 , 0x00   /*数据*/
							//0x00 , 0x00  	/*CRC校验侦尾*/
							}; 

/*读变量存储区帧*/	
const uint8_t VariableRead[7]={
							FH0 , FH1 , /*帧头2字节 */
							0x04 , /*长度 包括命令和数据*/
							0x83 , /*从变量存储区指定地址开始读入RD_LEN长度字数据*/
							0x00 , 0x00 ,	/*变量存储空间2字节*/
							RD_LEN , /*长度*/
							//0x00 , 0x00  	/*CRC校验侦尾*/
							};	

const uint8_t ABC[20]={
							FH0 , FH1 , /*帧头2字节 */
							0x05 , /*长度 包括命令和数据*/	
							0x82 , /*指定地址开始写入数据串(字数据)到变量存储区*/
							0x40 , 0x00 ,	/*变量存储空间2字节*/
							0xBA , 0xA0   /*数据*/
							};	
const uint8_t rtc_write[13]={
							FH0 , FH1 , /*帧头2字节 */
							0x0A , /*长度 包括命令和数据*/	
							0x80 , /*指定地址开始写入数据串(字数据)到变量存储区*/
							0x1F , 0x5A ,	/*变量存储空间2字节*/
							0x00 , 0x00 ,0X00 ,   /*日期*/
							0X00 ,/*星期*/
							0x00 , 0x00 ,0x00 /*时间*/
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
 * 函数名称:VariableChage                                                                    
 * 描    述:改变指定变量的值                                                              
 *                                                                               
 * 输    入:page                                                                    
 * 输    出:无                                                                     
 * 返    回:void                                                               
 * 修改日期:2016年7月13日
 *******************************************************************************/ 							
void VariableChage(uint16_t Variable,uint16_t Value)							
{
	uint8_t temp[8]={0};  //存放串口数据的临时指针
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
 * 函数名称:VariableChagelong                                                                    
 * 描    述:改变指定变量的值                                                              
 *                                                                               
 * 输    入:page                                                                    
 * 输    出:无                                                                     
 * 返    回:void                                                               
 * 修改日期:2016年7月13日
 *******************************************************************************/ 							
void VariableChagelong (uint16_t Variable,uint32_t Value)							
{
	uint8_t temp[10]={0};  //存放串口数据的临时指针
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
 * 函数名称:RegisterChage                                                                   
 * 描    述:改变指定变量的值                                                              
 *                                                                               
 * 输    入:page                                                                    
 * 输    出:无                                                                     
 * 返    回:void                                                               
 * 修改日期:2016年7月13日
 *******************************************************************************/ 							
void RegisterChage(uint8_t Register,uint16_t Value)							
{
	uint8_t temp[8]={0};  //存放串口数据的临时指针
	memcpy(temp,RegisterWrite,sizeof(RegisterWrite));
	temp[3]= Register;
	myunion.adress=Value;
	temp[5]= myunion.adr[1];
	temp[6]= myunion.adr[0];		
	UartSend(&g_ScreenUartLite,temp,sizeof(temp));
}	

 /*******************************************************************************
 * 函数名称:RegisterChage                                                                   
 * 描    述:改变指定变量的值                                                              
 *                                                                               
 * 输    入:page                                                                    
 * 输    出:无                                                                     
 * 返    回:void                                                               
 * 修改日期:2016年7月13日
 *******************************************************************************/ 							
void ScreenControl(uint8_t cmd)							
{
	uint8_t temp[8]={0};  //存放串口数据的临时指针
	memcpy(temp,RegisterWrite,sizeof(RegisterWrite));
	temp[3]= TPC_Enable;
	temp[5]= cmd ;	//0x00 关闭
	UartSend(&g_ScreenUartLite,temp,sizeof(temp));
}	
 

 /*******************************************************************************
 * 函数名称:DisplayAbnormal                                                               
 * 描    述:显示错误码                                                   
 *                                                                               
 * 输    入:abnomal_code 字符串                                                                  
 * 输    出:无                                                                     
 * 返    回:void                                                               
 * 修改日期:2016年7月13日
 *******************************************************************************/ 
void DisplayAbnormal(uint8_t *abnomal_code)
{
	uint8_t i=0;
	uint8_t temp[20]={0};  //存放串口数据的临时数组
	memcpy(temp,VariableWrite,sizeof(VariableWrite));
	temp[2]= 7; //  数据长度为4位
	myunion.adress= erro_num; 
	temp[4]= myunion.adr[1];
	temp[5]= myunion.adr[0];
	for(i=0;i<4;i++) temp[i+6]=abnomal_code[i];
	UartSend(&g_ScreenUartLite, temp,sizeof(temp));
}


 /*******************************************************************************
 * 函数名称:PageChange                                                                     
 * 描    述:发送切换图片命令                                                              
 *                                                                               
 * 输    入:page                                                                    
 * 输    出:无                                                                     
 * 返    回:void                                                               
 * 修改日期:2016年7月13日
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
 * 函数名称:ReadPage                                                                     
 * 描    述:读取当前页,数据处理在DealSeriAceptData中处理                                                           
 *                                                                               
 * 输    入:无                                                                    
 * 输    出:                                                                     
 * 返    回:                                                             
 * 修改日期:2016年7月13日
 *******************************************************************************/ 	
void ReadPage(void)
{
	uint8_t temp[6]={0};
	memcpy(temp,RegisterRead,sizeof(RegisterRead));	
	temp[4]=	PIC_ID;	
	UartSend(&g_ScreenUartLite,temp,sizeof(temp));
}


 /*******************************************************************************
 * 函数名称:RecRegisterValues                                                                   
 * 描    述:获取寄存器的值                                                                                                                          
 * 输    入:寄存器地址,寄存器数据,寄存器数据长度                                                                  
 * 输    出:无                                                                     
 * 返    回:void                                                               
 * 修改日期:2016年7月13日
 *******************************************************************************/ 
uint8_t current_page =0;//当前页面
void RecRegisterValues(uint8_t VariableAdress,uint8_t *VariableData,uint8_t length)
{
	if(VariableAdress==PIC_ID)//读取判断当前的页面的ID
	{
		current_page =VariableData[length-1];
		if(current_page!=pageunitil)
		{
			//PageChange(cmd_page);
		}
	}
}
 /*******************************************************************************
 * 函数名称:DealSeriAceptData                                                                   
 * 描    述:处理从迪文屏幕返回的数据                                                        
 *          如何实现三个连续的数据：0xA5 0XA5 0X5A                                                                           
 * 输    入:无                                                                   
 * 输    出:无                                                                     
 * 返    回:void                                                               
 * 修改日期:2016年7月13日
 *******************************************************************************/ 	
void DealSeriAceptData(void)
 {
	uint8_t i;
	uint8_t temp,temp1,length,checkout;
	uint8_t RegisterAdress=0;
	int16_t VariableAdress=0;
	
	uint8_t Rx3DataBuff[10]={0};/*设置一个数组大小，?以免越界(out of bounds),?可变长度数组*/
	uint8_t RegisterData[5]={0};  //寄存器数据数组
	uint8_t VariableData[5]={0};  //变量数据数组
	uint8_t RegisterLength= 0;   //寄存器数据的长度
	uint8_t VariableLength= 0;   //变量数据的长度

	while(UartReceiveBuffer(&g_ScreenUartLite) >=9) //获取缓冲区大小，直至缓冲区无数据
	{	
		printf("#INFO: >> UartReceiveBuffer\r\n");
		if(UartReceiveBuffer(&g_ScreenUartLite)==1)
		{	
			if(temp==FH0)	//匹配帧头第一个字节
			{ 
loop:			if(UartRecv(&g_ScreenUartLite, &temp1, sizeof(temp1))==1)
				{
					if(temp1==FH1)  //匹配帧头第二个字节：
					{
						if(UartRecv(&g_ScreenUartLite, &length, sizeof(length)) == 1)  //获取命令字节长度
						{
							checkout =1;//置位开始读取命令与数据标志	
						}	
					}
					else if(temp1==FH0)	goto loop; //如果持续出现0xA5则继续判断下一个字节是否为0x5A
				}
			}
		}
		if(checkout==1) //直到获取数据长度，然后读缓存
		{
			checkout =0;  //复位标志
			for(i=0;i<length;i++) UartRecv(&g_ScreenUartLite, Rx3DataBuff+i, sizeof(length));
			if(Rx3DataBuff[0]==0x81)  //读寄存器返回命令
			{
				RegisterAdress =Rx3DataBuff[1];
				for(i=0;i<(length-2);i++)
				RegisterData[i]=Rx3DataBuff[2+i];
				//加入修改相关数据的功能
				RecRegisterValues(RegisterAdress,RegisterData,RegisterLength);
			}
			else if(Rx3DataBuff[0]==0x83) //读数据存储器返回命令
			{
				myunion.adr[1] =Rx3DataBuff[1]; //有可能是小端模式引起的
				myunion.adr[0] =Rx3DataBuff[2];
				VariableAdress =myunion.adress;
				VariableLength =Rx3DataBuff[3];
				for(i=0;i<(length-4);i++)
				VariableData[i]=Rx3DataBuff[4+i];
				//加入修改变量地址数据的功能
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
	printf("\t addr: 0x%02x\r\n", ScreenCmd->addr);
	printf("\t data_len: 0x%02x\r\n", ScreenCmd->data_len);
	printf("\t val:");
	for (i = 0; i < ScreenCmd->data_len; i++)
		printf(" 0x%02x", ScreenCmd->val[i]);
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

static int ProcRecvScreenData(struct screen_cmd *ScreenCmd)
{
	int i = 0;
	if(ScreenCmd == NULL) {
		printf("#ERR: ProcRecvScreenData ScreenCmd NULL.\r\n");
		return -1;
	}

	if(ScreenCmd->cmd == READ_CTRL_REG){
		ScreenCmd->addr = ScreenCmd->data[0];
		ScreenCmd->data_len = ScreenCmd->data[1];
		for (i = 0; i < ScreenCmd->data_len; i++)
			ScreenCmd->val[i] = ScreenCmd->data[i + 2];
	} else if(ScreenCmd->cmd == READ_DATA_REG) {
		ScreenCmd->addr = (ScreenCmd->data[0]<<8)& 0xFF00 | (ScreenCmd->data[1]) & 0xFF;
		ScreenCmd->data_len = ScreenCmd->data[2];
		for (i = 0; i < ScreenCmd->data_len; i++)
			ScreenCmd->val[i] = (ScreenCmd->data[2*i + 3]<<8) & 0xFF00 | (ScreenCmd->data[2*i + 4]) & 0xFF ;
	} else {
		printf("#ERR: ProcRecvScreenData CMD Err.\r\n");
		return -2;
	}

	PrintCmdData(&g_ScreenCmd);

	return 0;
}


void RecvScreenData(void)
{
	unsigned char recv[SCREEN_CMD_DATA_LEN];
	unsigned short ret = 0, i = 0;

	while(1) {
#if 1
		ret = ReadScreenCtrlReg(0x00, 1);
		MB_Sleep(1000);
		ret = UartRecv(&g_ScreenUartLite, &recv, sizeof(recv));
		MB_Sleep(100);
		if( ret >= 5) {

			for(i = 0; i < ret; i++)
				printf("#INFO: UartRecv recv[%d] = 0x%02x\r\n", i , recv[i]);

			if((recv[0] == FH0) && (recv[1] == FH1)) {
				memcpy(&g_ScreenCmd, recv, ret);
				ret = ProcRecvScreenData(&g_ScreenCmd);
				if (ret < 0) {
					printf("#ERR: ProcRecvScreenData Err.\r\n");
				}
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
* 函数名称:SerialScreenInit
* 描    述: 串口屏初始化
*
* 输    入:无
* 输    出:无
* 返    回:void
* 修改日期:2016年7月13日
*******************************************************************************/
void SerialScreenInit(void)
{
	UartOpen(&g_ScreenUartLite, XPAR_AXI_UARTLITE_1_DEVICE_ID);
}

