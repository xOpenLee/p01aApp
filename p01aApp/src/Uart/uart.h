#ifndef UART_H /* prevent circular inclusions */
#define UART_H /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

#include "xintc.h"


#define UART0_DEBUG   	0  	/* 调试串口 */
#define UART1_SCREEN 	1 	/* 屏幕串口 */
#define UART2_NET 		2 	/* 网络串口 */

/*******************************************************************************
* 函数名称:UartDebugRecv
* 描    述: 调试串口接收
*
* 输    入:
	DataBufferPtr：接收缓冲区
	NumBytes： 接收数据长度
* 输    出:
* 返    回: 接收数据实际长度
* 修改日期:2016年6月21日
*******************************************************************************/
extern unsigned int UartDebugRecv(u8 *DataBufferPtr, unsigned int NumBytes);

/*******************************************************************************
* 函数名称:UartDebugSend
* 描    述: 调试串口发送
*
* 输    入:
	DataBufferPtr：发送缓冲区
	NumBytes： 发送数据长度
* 输    出:
* 返    回: 发送数据实际长度
* 修改日期:2016年6月21日
*******************************************************************************/
extern unsigned int UartDebugSend(u8 *DataBufferPtr, unsigned int NumBytes);

/*******************************************************************************
* 函数名称:UartScreenGetCharsInRxBuf
* 描    述:  接收缓冲区已接收的数据
*
* 输    入:无
* 输    出:
* 返    回:
* 修改日期:2016年6月21日
*******************************************************************************/
int UartScreenGetCharsInRxBuf();

/*******************************************************************************
* 函数名称:UartScreenRecv
* 描    述: 屏幕串口接收
*
* 输    入:
	DataBufferPtr：接收缓冲区
	NumBytes： 接收数据长度
* 输    出:
* 返    回: 接收数据实际长度
* 修改日期:2016年6月21日
*******************************************************************************/
extern unsigned int UartScreenRecv(u8 *DataBufferPtr, unsigned int NumBytes);


/*******************************************************************************
* 函数名称:UartScreenGetChar
* 描    述: 屏幕串口接收一个字节
*
* 输    入:
	DataBufferPtr：接收缓冲区
* 输    出:
* 返    回: 接收数据实际长度
* 修改日期:2016年6月21日
*******************************************************************************/
extern unsigned int UartScreenGetChar(u8 *DataBufferPtr);

/*******************************************************************************
* 函数名称:UartScreenSend
* 描    述: 屏幕串口发送
*
* 输    入:
	DataBufferPtr：发送缓冲区
	NumBytes： 发送数据长度
* 输    出:
* 返    回: 发送数据实际长度
* 修改日期:2016年6月21日
*******************************************************************************/
extern unsigned int UartScreenSend(u8 *DataBufferPtr, unsigned int NumBytes);

/*******************************************************************************
* 函数名称:UartNetRecv
* 描    述: 网络串口接收
*
* 输    入:
	DataBufferPtr：接收缓冲区
	NumBytes： 接收数据长度
* 输    出:
* 返    回: 接收数据实际长度
* 修改日期:2016年6月21日
*******************************************************************************/
extern unsigned int UartNetRecv(u8 *DataBufferPtr, unsigned int NumBytes);

/*******************************************************************************
* 函数名称:UartNetSend
* 描    述: 网络串口发送
*
* 输    入:
	DataBufferPtr：发送缓冲区
	NumBytes： 发送数据长度
* 输    出:
* 返    回: 发送数据实际长度
* 修改日期:2016年6月21日
*******************************************************************************/
extern unsigned int UartNetSend(u8 *DataBufferPtr, unsigned int NumBytes);


/*******************************************************************************
* 函数名称:UartInit
* 描    述: 串口初始化
*
* 输    入:
* 输    出:
* 返    回:
* 修改日期:2016年6月21日
*******************************************************************************/
extern int UartInit(void);

#ifdef __cplusplus
}
#endif

#endif			/* end of protection macro */
