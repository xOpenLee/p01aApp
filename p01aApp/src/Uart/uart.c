#include <stdio.h>
#include "xparameters.h"
#include "xuartlite.h"
#include "xstatus.h"
#include "uart.h"

 /*******************************************************************************
 * ��������:UartOpen
 * ��    ��: �򿪴����豸
 *
 * ��    ��:
 	 	 UartLite:��ʵ�����ľ��
 	 	 DeviceId:����ID��
 * ��    ��: UartLite:�Ѵ򿪾��
 * ��    ��: XST_SUCCESS �ɹ�, XST_FAILURE ʧ��.
 * �޸�����:2016��6��21��
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
* ��������:UartSend
* ��    ��: ��������
*
* ��    ��:
	 	 UartLite:�Ѵ򿪾��
	 	 DataBufferPtr: ���͵����ݻ�����
	 	 NumBytes�� ���͵����ݳ���
* ��    ��: NULL
* ��    ��: ���͵��ֽ�������.
* �޸�����:2016��6��21��
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
* ��������:UartRecv
* ��    ��: ��������
*
* ��    ��:
	 	 UartLite:�Ѵ򿪾��
	 	 DataBufferPtr: �������ݻ�����
	 	 NumBytes�� ���ճ���
* ��    ��: NULL
* ��    ��: ʵ�ʽ����ֽ�������.
* �޸�����:2016��6��21��
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
* ��������:UartRstFifos
* ��    ��: ��λ���ڻ���������
*
* ��    ��:
	 	 UartLite:�Ѵ򿪾��
* ��    ��: NULL
* ��    ��: NULL
* �޸�����:2016��6��21��
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
* ��������:UartIsSending
* ��    ��: ��ѯ�����Ƿ����ڷ�������
*
* ��    ��:
	 	 UartLite:�Ѵ򿪾��
* ��    ��: NULL
* ��    ��: ����0���ڷ������ݣ�����Ƿ������ݡ�
* �޸�����:2016��6��21��
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
* ��������:UartIsSendBuffer
* ��    ��: ��ѯ�����Ƿ����ڷ�������
*
* ��    ��:
	 	 UartLite:�Ѵ򿪾��
* ��    ��: NULL
* ��    ��: ���ͻ�����ʣ�����������
* �޸�����:2016��6��21��
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
* ��������:UartIsSendBuffer
* ��    ��: ��ѯ�����Ƿ����ڷ�������
*
* ��    ��:
	 	 UartLite:�Ѵ򿪾��
* ��    ��: NULL
* ��    ��: ���ͻ�����ʣ�����������
* �޸�����:2016��6��21��
*******************************************************************************/

unsigned int UartReceiveBuffer(XUartLite *UartLite)
{
	if(UartLite == NULL) {
		print("#ERR: UartReceiveBuffer UartLite NULL\n");
		return 0;
	}

	return XUartLite_ReceiveBuffer (UartLite);
}




