#include "common.h"
#include <intrins.h>

/*
  @brief	延时xms函数
 */
/***********************************************************************************
 @brief STC12C延时xms函数
 */
void delay_ms(UINT16 xms)
{
	UINT16 x,y;
	for(x=xms; x>0; x--)
	{
		for(y=1226; y>0; y--)
		{
			_nop_();_nop_();_nop_();_nop_();_nop_();
		}
	}
}

/***********************************************************************************
	@brief 延时xus函数
*/
void delay_us(UINT16 xus)
{
    while (xus--)
    {
        _nop_();
        //_nop_();	12MHz晶振去掉注释
    }
}