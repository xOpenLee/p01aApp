#ifndef UART_H /* prevent circular inclusions */
#define UART_H /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

#include "xparameters.h"
#include "xuartlite.h"

extern int UartOpen(XUartLite *UartLite, unsigned int DeviceId);
extern unsigned int UartSend(XUartLite *UartLite, u8 *DataBufferPtr, unsigned int NumBytes);
extern unsigned int UartRecv(XUartLite *UartLite, u8 *DataBufferPtr, unsigned int NumBytes);
extern void UartRstFifos(XUartLite *UartLite);
extern int UartIsSending(XUartLite *UartLite);
extern unsigned int UartSendBuffe(XUartLite *UartLite);
extern unsigned int UartReceiveBuffer(XUartLite *UartLite);

#ifdef __cplusplus
}
#endif

#endif			/* end of protection macro */
