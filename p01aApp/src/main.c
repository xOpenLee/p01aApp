
#include <stdio.h>
#include "platform.h"
#include "serialscreen.h"


#define PROJ_NAME "P01A"
#define PROJ_VERSION "V0.0.1"

/*******************************************************************************
* 函数名称:SerialScreenInit
* 描    述: 串口屏串口初始化
* 输    入:无
* 输    出:无
* 返    回:void
* 修改日期:2016年6月21日
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
