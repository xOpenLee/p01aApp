
#include <stdio.h>
#include "platform.h"
#include "serialscreen.h"


#define PROJ_NAME "P01A"
#define PROJ_VERSION "V0.0.1"

/*******************************************************************************
* ��������:SerialScreenInit
* ��    ��: ���������ڳ�ʼ��
* ��    ��:��
* ��    ��:��
* ��    ��:void
* �޸�����:2016��6��21��
*******************************************************************************/
static void PrintVer(char *ver)
{
	//print("#INFO: Proj Name %s %s\n", PROJ_NAME, PROJ_VERSION);
	//printf("#INFO: Built Time %s %s\n", __TIME__, __DATE__);
}

int main()
{
    init_platform();

    print("Hello World\n\r");

    SerialScreenInit();

    cleanup_platform();

    return 0;
}
