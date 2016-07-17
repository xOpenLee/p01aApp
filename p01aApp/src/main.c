
#include <stdio.h>
#include "platform.h"
#include "utils.h"
#include "adv_config.h"
#include "serialscreen.h"
#include "sched.h"
//#include "unistd.h"
#define PROJ_NAME "P01A"
#define PROJ_VERSION "V0.0.1"

static void *ThreadFunc(void *arg)
{
	printf("#INFO: ThreadFunc %d\r\n", (int)arg);
//	sleep(1);
}

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
	printf("#INFO: Proj Name %s %s\n", PROJ_NAME, PROJ_VERSION);
	printf("#INFO: Built Time %s %s\n", __TIME__, __DATE__);
}

int main()
{
    init_platform();


    PrintVer();
    SerialScreenInit();
    ad9518_config();
    ad9520_config();
    //PthreadCreate("TstThread",1,ThreadFunc, 1);

    cleanup_platform();

    return 0;
}

