
#ifndef	extern_h
#define	extern_h

System_Clock	EQU	4000000	//	Used at UART, PS2, ...
PFC161	=>	0x161
Chip_Name	=>	PFC161
CS_Sel	=>	'PA7';
//---------------------------------------------------------
Variable_Define_Lib	Macro	//�൱�ڶ���һЩȫ�ֱ����ڿ�����ڿ���ʹ����Щ����������Sleep_Run��ʹ�ã�
	//BYTE	Variable;	
EndM
//---------------------------------------------------------
Sleep_Run1	Expand			//ʡ��ģʽ��ʱɨ��TK˯�߻��Ѻ�ע��Sleepģʽ��ʱ����IHRC/64
//------------------------
//--User can add code-----
//------------------------
//
//	Break;					//���ֶ�����Sleep_Mode()
endm
//-----------------
Sleep_Run2	Expand			//ʡ��ģʽ��ʱɨ��TK�ٴν���˯�ߣ�ע��Sleepģʽ��ʱ����IHRC/64
//------------------------
//--User can add code-----
//------------------------
//
//	Break;					//���ֶ�����Sleep_Mode()
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