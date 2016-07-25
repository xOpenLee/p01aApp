
#include <stdio.h>
#include "platform.h"
#include "utils.h"
#include "adv_config.h"
#include "serialscreen.h"
#include "sched.h"
#include "unistd.h"
#include "microblaze_sleep.h"
#include "xuartlite.h"
#define PROJ_NAME "P01A"
#define PROJ_VERSION "V0.0.1"

static void *ThreadFunc(void *arg)
{
	printf("#INFO: ThreadFunc %d\r\n", (int)arg);
}

/*******************************************************************************
* 函数名称:PrintVer
* 描    述:  打印项目名称、版本信息、编译时间
* 输    入:无
* 输    出:无
* 返    回:void
* 修改日期:2016年6月21日
*******************************************************************************/
static void PrintVer(void)
{
	printf("#INFO: Proj Name %s %s\r\n", PROJ_NAME, PROJ_VERSION);
	printf("#INFO: Built Time %s %s\r\n", __TIME__, __DATE__);
}

static void ScreenUartTst(void)
{
	extern XUartLite g_ScreenUartLite;
	char recv[256], send[256], i = 0;
	unsigned int ret = 0;
	for(i = 0; i < sizeof(send); i++) {
		recv[i] = 0;
		send[i] = i;
	}
	UartSend(&g_ScreenUartLite,send,sizeof(send));
	while(1) {
		ret = UartRecv(&g_ScreenUartLite, &recv, sizeof(recv));
		MB_Sleep(10);
		if( ret > 1) {
			for(i = 0; i < ret; i++) {
				printf("#INFO: UartRecv recv[%d] = 0x%02x\r\n", i , recv[i]);
			}
		}
	}

}

int main()
{
    init_platform();

    PrintVer();

    SerialScreenInit();

    ad9518_config();

    ad9520_config();

    RecvScreenData();

    cleanup_platform();



    return 0;
}

