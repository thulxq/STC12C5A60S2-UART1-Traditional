#include "STC12C5A60S2.h"
#include "platform_support.h"
#include "common.h"

/***********************************************************************************
	@brief	软复位函数
 */
void soft_reset_to_ISP_Monitor(rest_mode mode)
{
	if(mode == ISP)
    	IAP_CONTR   =    0x60;   //0110,0000   软复位到系统ISP监控区
	else
			IAP_CONTR   =    0x20;   //0010,0000   软复位到系统AP用户区
}


/***********************************************************************************
	@brief	UART1 baud rate initial setting 
	@note
		需提前计算一下所选晶振能达到的最高速度，波特率不能超过最高速度
		1/传统模式(12T时钟、定时器1设置8位自动重装载模式产生波特率)
		(1) 波特率加倍(SMOD=1)：  Max_Baud = FOSC/12/16
		(2) 波特率不加倍(SMOD=0)：Max_Baud = FOSC/12/32
		例如：11.0592MHz晶振，波特率加倍时，最大波特率=11059200/12/16=57600
		2/定时器1设置为16位自动重装载模式
		(1) 波特率加倍(SMOD=1)：  Max_Baud = FOSC/12/16

      //启用独立波特率发生时计算公式如下：
      AUXR
*/
void UartInit(UINT32 u32Baudrate)    //T1M = 1, SMOD = 1
{
	clr_EA;   
	clr_ET1;
	clr_ES;
	
	//UART0 Mode 1, REN=1, TX=1, 波特率加倍 ////////////////////////////////////////
	SCON = 0x50;     	//8位数据,可变波特率
	set_SMOD;        	//UART0 Double Rate Enable

	// 独立波特率发生器, 1T模式 ///////////////////////////////////////////////////
#ifdef UART1_USED_BRTR_1T
	BRT = (256-FOSC/16/u32Baudrate);
	AUXR |= BIT2;		//独立波特率发生器时钟为Fosc,即1T
	AUXR |= BIT0;		//串口1选择独立波特率发生器为波特率发生器
	AUXR |= BIT4;		//启动独立波特率发生器	
#endif
	
	// 独立波特率发生器，12T模式 /////////////////////////////////////////////////
#ifdef UART1_USED_BRTR_12T
	BRT = (256-FOSC/16/12/u32Baudrate);
	AUXR &= ~BIT2;	//独立波特率发生器时钟为Fosc/12,即12T
	AUXR |= BIT0;		//串口1选择独立波特率发生器为波特率发生器
	AUXR |= BIT4;		//启动独立波特率发生器	
#endif

	// 标准8051模式///////////////////////////////////////////////////////////////
#ifdef UART1_USED_STAND8051
	TMOD &= 0x0f;				// TIM1 模式1
	TMOD |= 0x20;    	
	TL1 = (256-FOSC/16/12/u32Baudrate);			//设置定时器1自动重装数
	TH1 = TL1;
	set_TR1;					// start timer 1
#endif

	// TIM1，8位自动重装载，1T模式 ///////////////////////////////////////////////
#ifdef UART1_USED_TIM1_8BIT_1T
	AUXR &= ~BIT0;				//串口1选择定时器1为波特率发生器
	AUXR |= BIT6;					//TIM1时钟为Fosc,即1T
	TMOD &= 0x0F;					//清除定时器1模式位
	TMOD |= 0x20;					//设定定时器1为8位自动重装方式
	TL1 = (256-FOSC/16/u32Baudrate);			//设置定时器1自动重装数
	TH1 = TL1;						//设定定时初值 	
	set_TR1;							// start timer 1
#endif
	
	// Interrupt configure////////////////////////////////////////////////////////
	set_ES;						// Enable uart0 interrupter
	set_EA;						// enable global interrupter
}

/***********************************BIT4************************************************
	@brief 串口发送字符函数
*/
void Send_Data_To_UART0(UINT8 c)
{
    TI = 0;
    SBUF = c;
    while(TI==0);
}
/***********************************************************************************
	@brief 串口发送字符串函数
*/
void Send_rStr_To_UART0(const UINT8 *ptr)
{
    while(*ptr != '\0')
    {
			Send_Data_To_UART0(*ptr++);
    }
}