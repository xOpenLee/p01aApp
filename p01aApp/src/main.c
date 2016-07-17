
#include <stdio.h>
#include "platform.h"
#include "utils.h"
#include "adv_config.h"
#include "serialscreen.h"

#define PROJ_NAME "P01A"
#define PROJ_VERSION "V0.0.1"

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

    cleanup_platform();

    return 0;
}

