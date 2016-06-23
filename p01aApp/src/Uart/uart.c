#include <stdio.h>
#include "xparameters.h"
#include "xuartlite.h"
#include "xstatus.h"
#include "uart.h"

 /*******************************************************************************
 * 函数名称:UartOpen
 * 描    述: 打开串口设备
 *
 * 输    入:
 	 	 UartLite:需实例化的句柄
 	 	 DeviceId:串口ID号
 * 输    出: UartLite:已打开句柄
 * 返    回: XST_SUCCESS 成功, XST_FAILURE 失败.
 * 修改日期:2016年6月21日
 *******************************************************************************/
int UartOpen(XUartLite *UartLite, unsigned int DeviceId)
{
	int Status = 0;

	if(UartLite == NULL) {
		print("#ERR: UartOpen UartLite NULL\n");
		return XST_FAILURE;
	}

	Status = XUartLite_Initialize(UartLite, DeviceId);
	if (Status != XST_SUCCESS) {
		print("#ERR: UartOpen XUartLite_Initialize Err\n");
		return XST_FAILURE;
	}

	Status = XUartLite_SelfTest(UartLite);
	if (Status != XST_SUCCESS) {
		print("#ERR: UartOpen XUartLite_SelfTest Err\n");
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}


/*******************************************************************************
* 函数名称:UartSend
* 描    述: 发送数据
*
* 输    入:
	 	 UartLite:已打开句柄
	 	 DataBufferPtr: 发送的数据缓冲区
	 	 NumBytes： 发送的数据长度
* 输    出: NULL
* 返    回: 发送的字节数长度.
* 修改日期:2016年6月21日
*******************************************************************************/
unsigned int UartSend(XUartLite *UartLite, u8 *DataBufferPtr, unsigned int NumBytes)
{
	if(UartLite == NULL) {
		print("#ERR: UartSend UartLite NULL\n");
		return -1;
	}

 	return XUartLite_Send (UartLite, DataBufferPtr, NumBytes);
}

/*******************************************************************************
* 函数名称:UartRecv
* 描    述: 接收数据
*
* 输    入:
	 	 UartLite:已打开句柄
	 	 DataBufferPtr: 接收数据缓冲区
	 	 NumBytes： 接收长度
* 输    出: NULL
* 返    回: 实际接收字节数长度.
* 修改日期:2016年6月21日
*******************************************************************************/
unsigned int UartRecv(XUartLite *UartLite, u8 *DataBufferPtr, unsigned int NumBytes)
{
	if(UartLite == NULL) {
		print("#ERR: UartRecv UartLite NULL\n");
		return 0;
	}

	return XUartLite_Recv (UartLite, DataBufferPtr, NumBytes);
}

/*******************************************************************************
* 函数名称:UartRstFifos
* 描    述: 复位串口缓冲区数据
*
* 输    入:
	 	 UartLite:已打开句柄
* 输    出: NULL
* 返    回: NULL
* 修改日期:2016年6月21日
*******************************************************************************/
void UartRstFifos(XUartLite *UartLite)
{
	if(UartLite == NULL) {
		print("#ERR: UartRstFifos UartLite NULL\n");
		return ;
	}

	XUartLite_ResetFifos(UartLite);
}


/*******************************************************************************
* 函数名称:UartIsSending
* 描    述: 查询串口是否正在发送数据
*
* 输    入:
	 	 UartLite:已打开句柄
* 输    出: NULL
* 返    回: 大于0正在发送数据，否则非发送数据。
* 修改日期:2016年6月21日
*******************************************************************************/
int UartIsSending(XUartLite *UartLite)
{
	if(UartLite == NULL) {
		print("#ERR: UartIsSending UartLite NULL\n");
		return -1;
	}

	return XUartLite_IsSending(UartLite);
}

/*******************************************************************************
* 函数名称:UartIsSendBuffer
* 描    述: 查询串口是否正在发送数据
*
* 输    入:
	 	 UartLite:已打开句柄
* 输    出: NULL
* 返    回: 发送缓冲区剩余的数据量。
* 修改日期:2016年6月21日
*******************************************************************************/
unsigned int UartSendBuffe(XUartLite *UartLite)
{
	if(UartLite == NULL) {
		print("#ERR: UartSendBuffe UartLite NULL\n");
		return 0;
	}

	return XUartLite_SendBuffer(UartLite);
}

/*******************************************************************************
* 函数名称:UartIsSendBuffer
* 描    述: 查询串口是否正在发送数据
*
* 输    入:
	 	 UartLite:已打开句柄
* 输    出: NULL
* 返    回: 发送缓冲区剩余的数据量。
* 修改日期:2016年6月21日
*******************************************************************************/

unsigned int UartReceiveBuffer(XUartLite *UartLite)
{
	if(UartLite == NULL) {
		print("#ERR: UartReceiveBuffer UartLite NULL\n");
		return 0;
	}

	return XUartLite_ReceiveBuffer (UartLite);
}




