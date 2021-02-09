//-----------------------------------
/*
		*相关更新记录请运行程序后在log窗口查看
		*若有使用此库相关问题，可咨询相关代理商工程人员
		*或加QQ群:710107052询问
*/
//-----------------------------------
//注意:使用此库前请预设以下配置
//-----------------------------------
#ifndef	PT_Lib_h
#define	PT_Lib_h
Lib_H_Top:
PFC161_Set:
//-----------------------------------
\                           ______　   _____
\PA5/INT0/PRSTB/TK9/PWMTM3 ┨1 ● \---/   8┠   PA4/TK6/PWMTM3
\             PA7/CS/TK10  ┨2            7┠   PA3/TK5/PWMTM2
\                VDD/AVDD  ┨3            6┠   PB0/INT1/TK11/PWMTM2
\                GND/AGND  ┨4            5┠   PA6/TK8
\                          ┗━━━━━━━┛
\                       PFC161-S08B(SOP8B-150mil)
//-----------------------------------
Touch_Channel_Selection:
	Const_EN_CH_T_Key8	=>	1	//TK8(PA6)
//-----------------------------------
									//default:100
//-----------------------------------
	//T_Key灵敏度sensitivity设置
Touch_Sensitivity_Set:
	Const_SEN_T_Key8		=>	180
//------------------------------------
	//是否使用长触摸			//主要用于环境值修正参考，有长触摸环境值修正减慢
	Const_En_Long_T_Key8	=>	1
//-------------------------------------
	//实际触摸按键设置
	Const_Touch_Source_CLK	=>	3;	//Touch Pad clock selection,取值0-8
									//0:reserved, 1:reserved, 2:IHRC/4, 3:IHRC/8,
									//4:IHRC/16, 5:IHRC/32, 6:IHRC/64, 7:IHRC/128, 8:ILRC
									//default:3
	Const_Touch_VRef		=>	0;	//0:0.5*VCC, 1:0.4*VCC, 2:0.3*VCC, 3:0.2*VCC
									//CS电容参考电压设定 0.2VCC-0.5VCC
									//对CS电容大小和触摸灵敏度有影响
									//此处提高可降低外部基准电容
									//default:0
	Const_Touch_Discharge	=>	3;	//Discharge time before starting the touch function
									//0:reserved, 1:CLK_32, 2:CLK_64, 3:CLK_128	
									//default:3
//------Touch环境修正及抗干扰设置-----
Touch_Ref_and_Noise_Set:
	Const_T_Key_Smooth_Rank	=>	3	//TK滤波等级(0-6),数值越大滤波越平滑,采样耗时越长
									//default:3
	Const_T_Key_Noise_Margin=>	10	//Tk防噪声裕量(0-60),数值越大代表防噪声越强
									//default:1
	Const_Env_Fix			=>	1	//环境值修正总开关	0 : 关闭 1 : 打开
	Const_Fast_Recover		=>	1	//触摸按键快速恢复开关(按键释放后快速恢复环境值)	1:开启 0:关闭
									//default:0
	Const_Env_Dw_Fix_Cnt	=>	20	//环境值下调修正难度 10 - 10000 值越大修正越慢	值为100代表至少采样100笔偏小资料才开始下调1
									//default:20
	Const_Env_Dw_Fix_Cnt_Long_Touch	=>	50
									//有长触摸功能时环境值下修难度	10-10000，作用同Const_Env_Dw_Fix_Cnt，只是长触摸触发后不再下调
									//default:50
//-------------------------------------
	//防噪声参考按键设置
									//干扰较大时，请至少打开1个参考通道,且按顺序开启，开启顺序Const_T_Key_Noise_Ref_1>Const_T_Key_Noise_Ref_2
									//注意:此处设置的参考通道不产生触摸信号，请勿和使用的触摸通道混用
									//0:0.5*VCC, 1:0.4*VCC, 2:0.3*VCC, 3:0.2*VCC
									//因参考按键通常为隐藏于IC内部或未使用的TK脚，从而计数值都相对较高，为了防止溢出，所以要降低位准，防止溢出
									//一般比Const_Touch_VRef设置的电压低如 0.3*VCC
									//default:3
//-------上位机参数设定---------------
T_Watch_Set:
#define  Uart_EN        0
	Const_EN_Uart		=>	0		//Uart使能, 0:Uart除能	1:Uart置能
									//需要接上位机时请将Const_EN_Uart置能,不用上位机请除能
									//此处除能后其他上位机参数无效
									//default:0
	Const_Uart_Wakeup_Mode=>1		//上位机唤醒方式，0:低电平唤醒(>0.5s) 1:上位机T-Watch唤醒
									//default:1
	Interrupt_Uart		=>	0		//UART中断及传输端口选择
									//0:PA0中断  1:PA5中断	2:PB0中断	default:0
									//注意:仿真时不支持PA5和PB0中断
									//实际IC烧录建议使用PA5
//--------触摸测试开关--------------
//	T_Key_Debug			=>	1		//打开可在Log中看到已打开通道的触摸信号
//	Continuous_Debugging=>	1		//打开可连续输出测量讯号，关闭时仅仅讯号跳变会输出测量讯号到LOG窗口(如触摸)
//	Disable_Debug_Var	=>	1		//当T_Key_Debug为1时，若提示变量内存分配失败(即RAM不足)可打开Disable_Debug_Var 来释放部分RAM解决该问题 default:0
//-------------------------------------------------
Lib_H_Bottom:
#endif	//PT_Lib_h
//***********************************///
//	库内主要函数说明
//***********************************//
//T_Key_Channel_Setting	T_Keyx	//手动T_Key端口设定，x表示常数
//Env_Fix	T_Keyx				//强制修复环境值到当前实际值，x表示常数
//void	TK_Init_Auto(void);		//根据Const_T_Key_VRef和Const_EN_CH_T_Keyx自动初始化T_Key相关寄存器
								//如若中途改变通道请使用T_Key_Scan_Reg寄存器,对应Const_EN_CH_T_Keyx应置1
//void	T_Key_Scan(void);		//T_Key扫描函数(非阻塞式分步骤轮询)
//void	T_Key_Data_Ref_Initial(void);	//初始化第一笔触摸环境修正值
//void	Get_T_Key_Signal(void);	//根据TK扫描结果判断按键是否成立并给出按键信号 T_Key1_Signal - T_Key12_Signal
//void	Uart_Auto(void);		//Uart自动初始化
//void	Sleep_Mode(void);		//睡眠模式,根据Const_Wakeup_CH_T_Keyx和Const_EN_CH_T_Keyx的设定唤醒
//T_Key_Scan_Reg				//TK扫描寄存器(16位) 
//T_Key_Signal					//按键标志寄存器(16位) 
//----------------------------------*/
