#include "xparameters.h"
#include "xuartlite.h"
#include "xintc.h"
#include "xil_exception.h"
#include "uart.h"

 static XUartLite g_UartDebugLite;
 static XUartLite g_UartScreenLite;
 static XUartLite g_UartNetLite;


 /*******************************************************************************
 * 函数名称:SendHandler
 * 描    述: 发送中断回调函数
 *
 * 输    入:无
 * 输    出:
 * 返    回:
 * 修改日期:2016年6月21日
 *******************************************************************************/
 void SendHandler(void *CallBackRef, unsigned int EventData)
 {

 }

 /*******************************************************************************
 * 函数名称:RecvHandler
 * 描    述:  接收中断回调函数
 *
 * 输    入:无
 * 输    出:
 * 返    回:
 * 修改日期:2016年6月21日
 *******************************************************************************/
 void RecvHandler(void *CallBackRef, unsigned int EventData)
 {

 }



 /*******************************************************************************
 * 函数名称:UartDebugConfiguration
 * 描    述: 调试串口配置
 *
 * 输    入:无
 * 输    出:
 * 返    回:
 * 修改日期:2016年6月21日
 *******************************************************************************/
int UartDebugConfiguration(void)
{

	int Status;

	/*
	 * Initialize the UartLite driver so that it's ready to use.
	 */
	Status = XUartLite_Initialize(&g_UartDebugLite, UART0_DEBUG);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test to ensure that the hardware was built correctly.
	 */
	Status = XUartLite_SelfTest(&g_UartDebugLite);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Connect the UartLite to the interrupt subsystem such that interrupts can
	 * occur. This function is application specific.
	 */
	//Status = SetupInterruptSystem(&g_UartDebugLite);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Setup the handlers for the UartLite that will be called from the
	 * interrupt context when data has been sent and received, specify a
	 * pointer to the UartLite driver instance as the callback reference so
	 * that the handlers are able to access the instance data.
	 */
	XUartLite_SetSendHandler(&g_UartDebugLite, SendHandler, &g_UartDebugLite);
	XUartLite_SetRecvHandler(&g_UartDebugLite, RecvHandler, &g_UartDebugLite);

	/*
	 * Enable the interrupt of the UartLite so that interrupts will occur.
	 */
	XUartLite_EnableInterrupt(&g_UartDebugLite);
}

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
unsigned int UartDebugRecv(u8 *DataBufferPtr, unsigned int NumBytes)
{
	if (NULL == DataBufferPtr)
		return 0;

	return  XUartLite_Recv(&g_UartDebugLite, DataBufferPtr, NumBytes);
}

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
unsigned int UartDebugSend(u8 *DataBufferPtr, unsigned int NumBytes)
{
	if (NULL == DataBufferPtr)
		return 0;

	return  XUartLite_Send(&g_UartDebugLite, DataBufferPtr, NumBytes);
}


/*******************************************************************************
* 函数名称:UartScreenGetCharsInRxBuf
* 描    述:  接收缓冲区已接收的数据
*
* 输    入:无
* 输    出:
* 返    回:
* 修改日期:2016年6月21日
*******************************************************************************/
int UartScreenGetCharsInRxBuf()
{
	return XUartLite_ReceiveBuffer(&g_UartScreenLite);
}


/*******************************************************************************
* 函数名称:UartScreenConfiguration
* 描    述: 屏幕串口配置
*
* 输    入:无
* 输    出:
* 返    回:
* 修改日期:2016年6月21日
*******************************************************************************/
int UartScreenConfiguration(void)
{

	int Status;

	/*
	 * Initialize the UartLite driver so that it's ready to use.
	 */
	Status = XUartLite_Initialize(&g_UartScreenLite, UART1_SCREEN);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test to ensure that the hardware was built correctly.
	 */
	Status = XUartLite_SelfTest(&g_UartScreenLite);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Connect the UartLite to the interrupt subsystem such that interrupts can
	 * occur. This function is application specific.
	 */
	//Status = SetupInterruptSystem(&g_UartScreenLite);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Setup the handlers for the UartLite that will be called from the
	 * interrupt context when data has been sent and received, specify a
	 * pointer to the UartLite driver instance as the callback reference so
	 * that the handlers are able to access the instance data.
	 */
	XUartLite_SetSendHandler(&g_UartScreenLite, SendHandler, &g_UartScreenLite);
	XUartLite_SetRecvHandler(&g_UartScreenLite, RecvHandler, &g_UartScreenLite);

	/*
	 * Enable the interrupt of the UartLite so that interrupts will occur.
	 */
	XUartLite_EnableInterrupt(&g_UartScreenLite);
}

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
unsigned int UartScreenRecv(u8 *DataBufferPtr, unsigned int NumBytes)
{
	if (NULL == DataBufferPtr)
		return 0;

	return  XUartLite_Recv(&g_UartScreenLite, DataBufferPtr, NumBytes);
}

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
unsigned int UartScreenGetChar(u8 *DataBufferPtr)
{
	if (NULL == DataBufferPtr)
		return 0;

	return  XUartLite_Recv(&g_UartScreenLite, DataBufferPtr, 1);
}

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
unsigned int UartScreenSend(u8 *DataBufferPtr, unsigned int NumBytes)
{
	if (NULL == DataBufferPtr)
		return 0;

	return  XUartLite_Send(&g_UartScreenLite, DataBufferPtr, NumBytes);
}



/*******************************************************************************
* 函数名称:UartNetConfiguration
* 描    述: 网络串口配置
*
* 输    入:无
* 输    出:
* 返    回:
* 修改日期:2016年6月21日
*******************************************************************************/
int UartNetConfiguration(void)
{

	int Status;

	/*
	 * Initialize the UartLite driver so that it's ready to use.
	 */
	Status = XUartLite_Initialize(&g_UartNetLite, UART2_NET);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test to ensure that the hardware was built correctly.
	 */
	Status = XUartLite_SelfTest(&g_UartNetLite);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Connect the UartLite to the interrupt subsystem such that interrupts can
	 * occur. This function is application specific.
	 */
	//Status = SetupInterruptSystem(&g_UartNetLite);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Setup the handlers for the UartLite that will be called from the
	 * interrupt context when data has been sent and received, specify a
	 * pointer to the UartLite driver instance as the callback reference so
	 * that the handlers are able to access the instance data.
	 */
	XUartLite_SetSendHandler(&g_UartNetLite, SendHandler, &g_UartNetLite);
	XUartLite_SetRecvHandler(&g_UartNetLite, RecvHandler, &g_UartNetLite);

	/*
	 * Enable the interrupt of the UartLite so that interrupts will occur.
	 */
	XUartLite_EnableInterrupt(&g_UartNetLite);
}

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
unsigned int UartNetRecv(u8 *DataBufferPtr, unsigned int NumBytes)
{
	if (NULL == DataBufferPtr)
		return 0;

	return  XUartLite_Recv(&g_UartNetLite, DataBufferPtr, NumBytes);
}

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
unsigned int UartNetSend(u8 *DataBufferPtr, unsigned int NumBytes)
{
	if (NULL == DataBufferPtr)
		return 0;

	return  XUartLite_Send(&g_UartNetLite, DataBufferPtr, NumBytes);
}


/*******************************************************************************
* 函数名称:UartInit
* 描    述: 串口初始化
*
* 输    入:
* 输    出:
* 返    回:
* 修改日期:2016年6月21日
*******************************************************************************/
int UartInit(void)
{
	UartScreenConfiguration();
	UartNetConfiguration();
	return 0;
}












