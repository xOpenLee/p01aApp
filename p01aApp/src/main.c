
#include <stdio.h>
#include "platform.h"
#include "serialscreen.h"

#define PROJ_NAME "P01A"
#define PROJ_VERSION "V0.0.1"

/*******************************************************************************
* ��������:PrintVer
* ��    ��:  ��ӡ��Ŀ���ơ��汾��Ϣ������ʱ��
* ��    ��:��
* ��    ��:��
* ��    ��:void
* �޸�����:2016��6��21��
*******************************************************************************/
static void PrintVer(void)
{
	xil_printf("#INFO: Proj Name %s %s\n", PROJ_NAME, PROJ_VERSION);
	xil_printf("#INFO: Built Time %s %s\n", __TIME__, __DATE__);
}

int main()
{
    init_platform();

    PrintVer();

    SerialScreenInit();

    cleanup_platform();

    return 0;
}
