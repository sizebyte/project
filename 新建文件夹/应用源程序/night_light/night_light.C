/*****************************************************
	FileName:	night_light
	CHIP	:	PFC161
	IDE		:	0.89 and later

	Data	:	2021/1/6 19:06:02
说明:
	主程序模式选择常量:Const_Work_Mode
	1	:	mode 1	正常模式 : 触摸灵敏，无休眠，可加定时器
	2	:	mode 2	省电模式 : 带睡眠，可唤醒，睡眠前可加定时,比Mode 1更省电
******************************************************/
MainFile_TOP:
#include	"extern.h"
#include	"PT_Lib_1.3.srt"
#include	"User_Function.C"
//---------------------------------------
//-------主程序模式选择------------------
///正常模式 : 触摸灵敏，无休眠，可使用定时器

void	FPPA0 (void)
{
	.ADJUST_IC	SYSCLK=IHRC/4, IHRC=16MHz, VDD=4V,Init_RAM;
		//	WatchDog Disable, RAM 0 ~ 0xF temporary be used
	//	You can add the follow code :
	CLKMD.En_WatchDog	=	1;		// WatchDog Enable
	CLKMD.En_ILRC		=	1;
	MISC	=	0b0010_0000;	//MISC.5请务必设为1(Fast_Wake_Up)
//	$ MISC	Fast_Wake_Up;
	IO_Init();		//IO Initial
	
	//	Insert Initial Code
#if Const_EN_Uart
	Uart_Auto();	//调用此函数,UART自动检测上位机和收发数据,不用上位机请忽略
					//结合Auto_Scan_Twatch()使用
#endif
	Variable_Init();
	En_Interrupt;	//开启全局中断	//用UART时请使用这种写法开中断
//	Dis_Interrupt;	//关闭中断		//用UART时请使用这种写法关中断
	TK_Init_Auto();	//初始化Tk并自动根据预设常量Const_EN_CH_T_Keyx配置寄存器
					//如若中途改变通道请使用T_Key_Scan_Reg寄存器,对应Const_EN_CH_T_Keyx应置1
	while (1)
	{
		.wdreset;
		//-----------------------------------------------------------//
		//mode 1	正常模式 : 无休眠功能
		T_Key_Scan();			//扫描T_Key
		T_Key_Warning();		//处理Tkey计数溢出异常
#if 1
		if(T_Key_Scan_End){		//触摸按键轮询结束		
			T_Key_Process();		//处理Tkey数据并判断触摸状态(如果滑条开启,一同判断滑条状态)
			T_Key_Function();		//触摸按键成立后命令
//			Uart_Auto();	//接上位机自动Uart收发,不用上位机请将Const_EN_Uart置0
		}
		User_other_Func();	
		//------------------------------------------------------------------------------------//
//		...
		wdreset;
#endif
	}
}
