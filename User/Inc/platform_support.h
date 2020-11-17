#ifndef INC_PLATFORM_SUPPORT_H
#define INC_PLATFORM_SUPPORT_H

#include "common.h"

/* STC MCU ---------------------------------------------------*/
typedef enum{AP=0,ISP}	rest_mode;	 	//定义软复位模式  

#define Self_Define_ISP_Download_Command  0x20
#define FOSC	11059200		//振荡频率

// UART1波特率发生器定义
#define UART1_USED_BRTR_1T   			// 使用独立波特率发生器, 1T
//#define UART1_USED_BRTR_12T   			// 使用独立波特率发生器,12T
//#define UART1_USED_STAND8051      // 标准8051模式
//#define UART1_USED_TIM1_8BIT_1T		// Timer1模式0,8位重装载1T

/* SFC macrodef ***********************************************/
// BITs operation
#define SET_BIT0        0x01
#define SET_BIT1        0x02
#define SET_BIT2        0x04
#define SET_BIT3        0x08
#define SET_BIT4        0x10
#define SET_BIT5        0x20
#define SET_BIT6        0x40
#define SET_BIT7        0x80
#define SET_BIT8        0x0100
#define SET_BIT9        0x0200
#define SET_BIT10       0x0400
#define SET_BIT11       0x0800
#define SET_BIT12       0x1000
#define SET_BIT13       0x2000
#define SET_BIT14       0x4000
#define SET_BIT15       0x8000

#define CLR_BIT0        0xFE
#define CLR_BIT1        0xFD
#define CLR_BIT2        0xFB
#define CLR_BIT3        0xF7
#define CLR_BIT4        0xEF
#define CLR_BIT5        0xDF
#define CLR_BIT6        0xBF
#define CLR_BIT7        0x7F

#define CLR_BIT8        0xFEFF
#define CLR_BIT9        0xFDFF
#define CLR_BIT10       0xFBFF
#define CLR_BIT11       0xF7FF
#define CLR_BIT12       0xEFFF
#define CLR_BIT13       0xDFFF
#define CLR_BIT14       0xBFFF
#define CLR_BIT15       0x7FFF

//**** PCON	87H *****
#define set_SMOD    PCON    |= SET_BIT7
#define clr_SMOD    PCON    &= ~SET_BIT7

/**** TCON		88H ****/
#define set_TF1			TF1		=		1
#define set_TR1			TR1		=		1
#define set_TF0			TF0		=		1
#define set_TR0			TR0		=		1
#define set_IE1			IE1		=		1
#define set_IT1			IT1		=		1
#define set_IE0			IE0		=		1
#define set_IT0			IT0		=		1

#define clr_TF1			TF1		=		0
#define clr_TR1			TR1		=		0
#define clr_TF0			TF0		=		0
#define clr_TR0			TR0		=		0
#define clr_IE1			IE1		=		0
#define clr_IT1			IT1		=		0
#define clr_IE0			IE0		=		0
#define clr_IT0			IT0		=		0

//**** SCON		98H ****
#define set_FE      FE    = 1
#define set_SM1     SM1   = 1
#define set_SM2     SM2   = 1
#define set_REN     REN   = 1
#define set_TB8     TB8   = 1
#define set_RB8     RB8   = 1
#define set_TI      TI    = 1
#define set_RI      RI    = 1

#define clr_FE      FE    = 0
#define clr_SM1     SM1   = 0
#define clr_SM2     SM2   = 0
#define clr_REN     REN   = 0
#define clr_TB8     TB8   = 0
#define clr_RB8     RB8   = 0
#define clr_TI      TI    = 0
#define clr_RI      RI    = 0

//**** IE			A8H ****
#define set_EA      EA       = 1
#define set_ES      ES       = 1
#define set_ET1     ET1      = 1
#define set_EX1     EX1      = 1
#define set_ET0     ET0      = 1
#define set_EX0     EX0      = 1

#define clr_EA      EA       = 0
#define clr_ES      ES       = 0
#define clr_ET1     ET1      = 0
#define clr_EX1     EX1      = 0
#define clr_ET0     ET0      = 0
#define clr_EX0     EX0      = 0


/* exported function -------------------------------------*/
void soft_reset_to_ISP_Monitor(rest_mode);
void UartInit(UINT32 u32Baudrate);
void Send_Data_To_UART0(UINT8 c);
void Send_rStr_To_UART0(const UINT8 *ptr);
#endif
