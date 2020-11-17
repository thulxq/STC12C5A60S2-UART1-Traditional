/**
	@brief 		Test STC12C5A60S2 MCU
	@author 	Xinqiong LU (xqlu@mcu.ac.cn)
	@date		2020-11-17
	@page		https://www.mcu.ac.cn/8051/stc/12C5A60S2/demo/template/
	@note
		(1) 这是一个空模板，STC12C5A60S2单片机可以直接用，STC12C5AxxS2系列请做修改
	    (2) 其他的的单片机仅供参考。

 */
/* Include ------------------------------------------------------------------------*/ 
#include "STC12C5A60S2.h"
#include <intrins.h>
#include "common.h"
#include "platform_support.h"

/*数据结构 -----------------------------------------------------------------------*/

/*ROM区数据 ----------------------------------------------------------------------*/
code const char str1[] = "This string is transmitted from STC12C5A60S2!\r\n";
code const char str2[] = "Author: xqlu(at)mcu.ac.cn\r\n";
code const char str3[] = "Create: 2020-11-17 17:24:21\r\n";

/*RAM区数据-----------------------------------------------------------------------*/

/*函数声明-----------------------------------------------------------------------*/

/* 主函数 -----------------------------------------------------------------------*/
void main()
{
	/* 欢迎词 实际使用过程中请删除... */
	// 初始化UART1， 注意platform_support.h中波特率发生器定义，有可能速度不够
	UartInit(115200);			
	Send_rStr_To_UART0(str1);
	Send_rStr_To_UART0(str2);
	
	/* 避免警告,实际使用过程中请删除... */
	delay_us(1);

	while(TRUE)
	{
		//
	}
}

/* 中断服务函数 -----------------------------------------------------------------*/

void UART0_ISR(void) interrupt 4
{
	UINT8 RX_Data;

	/* 只响应“接收”中断，“发送”中断来了就直接抹掉 */
	if(RI)
	{
		RI = 0;				         //串口中断标志不能自己清除，需要手动清除
		RX_Data=SBUF;
		Send_Data_To_UART0(RX_Data);
        if(RX_Data==Self_Define_ISP_Download_Command)    //是自定义下载命令
        {
            delay_ms(100);                             //延时0.1秒就足够了
            soft_reset_to_ISP_Monitor(ISP);         //软复位到系统ISP监控区
        }
	}
	else
		TI = 0;	       //串口发中断是发送“完”缓冲区数据之后产生，这里直接忽略掉
}
