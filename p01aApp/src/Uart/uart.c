#include "xparameters.h"
#include "xuartlite.h"
#include "xintc.h"
#include "xil_exception.h"
#include "uart.h"

 static XUartLite g_UartDebugLite;
 static XUartLite g_UartScreenLite;
 static XUartLite g_UartNetLite;


 /*******************************************************************************
 * ��������:SendHandler
 * ��    ��: �����жϻص�����
 *
 * ��    ��:��
 * ��    ��:
 * ��    ��:
 * �޸�����:2016��6��21��
 *******************************************************************************/
 void SendHandler(void *CallBackRef, unsigned int EventData)
 {

 }

 /*******************************************************************************
 * ��������:RecvHandler
 * ��    ��:  �����жϻص�����
 *
 * ��    ��:��
 * ��    ��:
 * ��    ��:
 * �޸�����:2016��6��21��
 *******************************************************************************/
 void RecvHandler(void *CallBackRef, unsigned int EventData)
 {

 }



 /*******************************************************************************
 * ��������:UartDebugConfiguration
 * ��    ��: ���Դ�������
 *
 * ��    ��:��
 * ��    ��:
 * ��    ��:
 * �޸�����:2016��6��21��
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
* ��������:UartDebugRecv
* ��    ��: ���Դ��ڽ���
*
* ��    ��:
	DataBufferPtr�����ջ�����
	NumBytes�� �������ݳ���
* ��    ��:
* ��    ��: ��������ʵ�ʳ���
* �޸�����:2016��6��21��
*******************************************************************************/
unsigned int UartDebugRecv(u8 *DataBufferPtr, unsigned int NumBytes)
{
	if (NULL == DataBufferPtr)
		return 0;

	return  XUartLite_Recv(&g_UartDebugLite, DataBufferPtr, NumBytes);
}

/*******************************************************************************
* ��������:UartDebugSend
* ��    ��: ���Դ��ڷ���
*
* ��    ��:
	DataBufferPtr�����ͻ�����
	NumBytes�� �������ݳ���
* ��    ��:
* ��    ��: ��������ʵ�ʳ���
* �޸�����:2016��6��21��
*******************************************************************************/
unsigned int UartDebugSend(u8 *DataBufferPtr, unsigned int NumBytes)
{
	if (NULL == DataBufferPtr)
		return 0;

	return  XUartLite_Send(&g_UartDebugLite, DataBufferPtr, NumBytes);
}


/*******************************************************************************
* ��������:UartScreenGetCharsInRxBuf
* ��    ��:  ���ջ������ѽ��յ�����
*
* ��    ��:��
* ��    ��:
* ��    ��:
* �޸�����:2016��6��21��
*******************************************************************************/
int UartScreenGetCharsInRxBuf()
{
	return XUartLite_ReceiveBuffer(&g_UartScreenLite);
}


/*******************************************************************************
* ��������:UartScreenConfiguration
* ��    ��: ��Ļ��������
*
* ��    ��:��
* ��    ��:
* ��    ��:
* �޸�����:2016��6��21��
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
* ��������:UartScreenRecv
* ��    ��: ��Ļ���ڽ���
*
* ��    ��:
	DataBufferPtr�����ջ�����
	NumBytes�� �������ݳ���
* ��    ��:
* ��    ��: ��������ʵ�ʳ���
* �޸�����:2016��6��21��
*******************************************************************************/
unsigned int UartScreenRecv(u8 *DataBufferPtr, unsigned int NumBytes)
{
	if (NULL == DataBufferPtr)
		return 0;

	return  XUartLite_Recv(&g_UartScreenLite, DataBufferPtr, NumBytes);
}

/*******************************************************************************
* ��������:UartScreenGetChar
* ��    ��: ��Ļ���ڽ���һ���ֽ�
*
* ��    ��:
	DataBufferPtr�����ջ�����
* ��    ��:
* ��    ��: ��������ʵ�ʳ���
* �޸�����:2016��6��21��
*******************************************************************************/
unsigned int UartScreenGetChar(u8 *DataBufferPtr)
{
	if (NULL == DataBufferPtr)
		return 0;

	return  XUartLite_Recv(&g_UartScreenLite, DataBufferPtr, 1);
}

/*******************************************************************************
* ��������:UartScreenSend
* ��    ��: ��Ļ���ڷ���
*
* ��    ��:
	DataBufferPtr�����ͻ�����
	NumBytes�� �������ݳ���
* ��    ��:
* ��    ��: ��������ʵ�ʳ���
* �޸�����:2016��6��21��
*******************************************************************************/
unsigned int UartScreenSend(u8 *DataBufferPtr, unsigned int NumBytes)
{
	if (NULL == DataBufferPtr)
		return 0;

	return  XUartLite_Send(&g_UartScreenLite, DataBufferPtr, NumBytes);
}



/*******************************************************************************
* ��������:UartNetConfiguration
* ��    ��: ���紮������
*
* ��    ��:��
* ��    ��:
* ��    ��:
* �޸�����:2016��6��21��
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
* ��������:UartNetRecv
* ��    ��: ���紮�ڽ���
*
* ��    ��:
	DataBufferPtr�����ջ�����
	NumBytes�� �������ݳ���
* ��    ��:
* ��    ��: ��������ʵ�ʳ���
* �޸�����:2016��6��21��
*******************************************************************************/
unsigned int UartNetRecv(u8 *DataBufferPtr, unsigned int NumBytes)
{
	if (NULL == DataBufferPtr)
		return 0;

	return  XUartLite_Recv(&g_UartNetLite, DataBufferPtr, NumBytes);
}

/*******************************************************************************
* ��������:UartNetSend
* ��    ��: ���紮�ڷ���
*
* ��    ��:
	DataBufferPtr�����ͻ�����
	NumBytes�� �������ݳ���
* ��    ��:
* ��    ��: ��������ʵ�ʳ���
* �޸�����:2016��6��21��
*******************************************************************************/
unsigned int UartNetSend(u8 *DataBufferPtr, unsigned int NumBytes)
{
	if (NULL == DataBufferPtr)
		return 0;

	return  XUartLite_Send(&g_UartNetLite, DataBufferPtr, NumBytes);
}


/*******************************************************************************
* ��������:UartInit
* ��    ��: ���ڳ�ʼ��
*
* ��    ��:
* ��    ��:
* ��    ��:
* �޸�����:2016��6��21��
*******************************************************************************/
int UartInit(void)
{
	UartScreenConfiguration();
	UartNetConfiguration();
	return 0;
}












