
#ifndef	extern_h
#define	extern_h

System_Clock	EQU	4000000	//	Used at UART, PS2, ...
PFC161	=>	0x161
Chip_Name	=>	PFC161
CS_Sel	=>	'PA7';
//---------------------------------------------------------
Variable_Define_Lib	Macro	//相当于定义一些全局变量在库里，可在库里使用这些变量（如在Sleep_Run里使用）
	//BYTE	Variable;	
EndM
//---------------------------------------------------------
Sleep_Run1	Expand			//省电模式定时扫描TK睡眠唤醒后，注意Sleep模式里时钟是IHRC/64
//------------------------
//--User can add code-----
//------------------------
//
//	Break;					//可手动跳出Sleep_Mode()
endm
//-----------------
Sleep_Run2	Expand			//省电模式定时扫描TK再次进入睡眠，注意Sleep模式里时钟是IHRC/64
//------------------------
//--User can add code-----
//------------------------
//
//	Break;					//可手动跳出Sleep_Mode()
endm
//---------------------------------------------------------
#if	defined(ADCC)
	#if defined(ADCR)
		ADCRH	EQU		ADCR
		ADCRL	EQU		0
	#else
		ADCR	EQU		ADCRH
	#endif
#endif

#endif