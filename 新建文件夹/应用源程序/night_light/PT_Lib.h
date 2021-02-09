//-----------------------------------
/*
		*��ظ��¼�¼�����г������log���ڲ鿴
		*����ʹ�ô˿�������⣬����ѯ��ش����̹�����Ա
		*���QQȺ:710107052ѯ��
*/
//-----------------------------------
//ע��:ʹ�ô˿�ǰ��Ԥ����������
//-----------------------------------
#ifndef	PT_Lib_h
#define	PT_Lib_h
Lib_H_Top:
PFC161_Set:
//-----------------------------------
\                           ______��   _____
\PA5/INT0/PRSTB/TK9/PWMTM3 ��1 �� \---/   8��   PA4/TK6/PWMTM3
\             PA7/CS/TK10  ��2            7��   PA3/TK5/PWMTM2
\                VDD/AVDD  ��3            6��   PB0/INT1/TK11/PWMTM2
\                GND/AGND  ��4            5��   PA6/TK8
\                          ������������������
\                       PFC161-S08B(SOP8B-150mil)
//-----------------------------------
Touch_Channel_Selection:
	Const_EN_CH_T_Key8	=>	1	//TK8(PA6)
//-----------------------------------
									//default:100
//-----------------------------------
	//T_Key������sensitivity����
Touch_Sensitivity_Set:
	Const_SEN_T_Key8		=>	180
//------------------------------------
	//�Ƿ�ʹ�ó�����			//��Ҫ���ڻ���ֵ�����ο����г���������ֵ��������
	Const_En_Long_T_Key8	=>	1
//-------------------------------------
	//ʵ�ʴ�����������
	Const_Touch_Source_CLK	=>	3;	//Touch Pad clock selection,ȡֵ0-8
									//0:reserved, 1:reserved, 2:IHRC/4, 3:IHRC/8,
									//4:IHRC/16, 5:IHRC/32, 6:IHRC/64, 7:IHRC/128, 8:ILRC
									//default:3
	Const_Touch_VRef		=>	0;	//0:0.5*VCC, 1:0.4*VCC, 2:0.3*VCC, 3:0.2*VCC
									//CS���ݲο���ѹ�趨 0.2VCC-0.5VCC
									//��CS���ݴ�С�ʹ�����������Ӱ��
									//�˴���߿ɽ����ⲿ��׼����
									//default:0
	Const_Touch_Discharge	=>	3;	//Discharge time before starting the touch function
									//0:reserved, 1:CLK_32, 2:CLK_64, 3:CLK_128	
									//default:3
//------Touch��������������������-----
Touch_Ref_and_Noise_Set:
	Const_T_Key_Smooth_Rank	=>	3	//TK�˲��ȼ�(0-6),��ֵԽ���˲�Խƽ��,������ʱԽ��
									//default:3
	Const_T_Key_Noise_Margin=>	10	//Tk������ԣ��(0-60),��ֵԽ����������Խǿ
									//default:1
	Const_Env_Fix			=>	1	//����ֵ�����ܿ���	0 : �ر� 1 : ��
	Const_Fast_Recover		=>	1	//�����������ٻָ�����(�����ͷź���ٻָ�����ֵ)	1:���� 0:�ر�
									//default:0
	Const_Env_Dw_Fix_Cnt	=>	20	//����ֵ�µ������Ѷ� 10 - 10000 ֵԽ������Խ��	ֵΪ100�������ٲ���100��ƫС���ϲſ�ʼ�µ�1
									//default:20
	Const_Env_Dw_Fix_Cnt_Long_Touch	=>	50
									//�г���������ʱ����ֵ�����Ѷ�	10-10000������ͬConst_Env_Dw_Fix_Cnt��ֻ�ǳ��������������µ�
									//default:50
//-------------------------------------
	//�������ο���������
									//���Žϴ�ʱ�������ٴ�1���ο�ͨ��,�Ұ�˳����������˳��Const_T_Key_Noise_Ref_1>Const_T_Key_Noise_Ref_2
									//ע��:�˴����õĲο�ͨ�������������źţ������ʹ�õĴ���ͨ������
									//0:0.5*VCC, 1:0.4*VCC, 2:0.3*VCC, 3:0.2*VCC
									//��ο�����ͨ��Ϊ������IC�ڲ���δʹ�õ�TK�ţ��Ӷ�����ֵ����Խϸߣ�Ϊ�˷�ֹ���������Ҫ����λ׼����ֹ���
									//һ���Const_Touch_VRef���õĵ�ѹ���� 0.3*VCC
									//default:3
//-------��λ�������趨---------------
T_Watch_Set:
#define  Uart_EN        0
	Const_EN_Uart		=>	0		//Uartʹ��, 0:Uart����	1:Uart����
									//��Ҫ����λ��ʱ�뽫Const_EN_Uart����,������λ�������
									//�˴����ܺ�������λ��������Ч
									//default:0
	Const_Uart_Wakeup_Mode=>1		//��λ�����ѷ�ʽ��0:�͵�ƽ����(>0.5s) 1:��λ��T-Watch����
									//default:1
	Interrupt_Uart		=>	0		//UART�жϼ�����˿�ѡ��
									//0:PA0�ж�  1:PA5�ж�	2:PB0�ж�	default:0
									//ע��:����ʱ��֧��PA5��PB0�ж�
									//ʵ��IC��¼����ʹ��PA5
//--------�������Կ���--------------
//	T_Key_Debug			=>	1		//�򿪿���Log�п����Ѵ�ͨ���Ĵ����ź�
//	Continuous_Debugging=>	1		//�򿪿������������Ѷ�ţ��ر�ʱ����Ѷ��������������Ѷ�ŵ�LOG����(�紥��)
//	Disable_Debug_Var	=>	1		//��T_Key_DebugΪ1ʱ������ʾ�����ڴ����ʧ��(��RAM����)�ɴ�Disable_Debug_Var ���ͷŲ���RAM��������� default:0
//-------------------------------------------------
Lib_H_Bottom:
#endif	//PT_Lib_h
//***********************************///
//	������Ҫ����˵��
//***********************************//
//T_Key_Channel_Setting	T_Keyx	//�ֶ�T_Key�˿��趨��x��ʾ����
//Env_Fix	T_Keyx				//ǿ���޸�����ֵ����ǰʵ��ֵ��x��ʾ����
//void	TK_Init_Auto(void);		//����Const_T_Key_VRef��Const_EN_CH_T_Keyx�Զ���ʼ��T_Key��ؼĴ���
								//������;�ı�ͨ����ʹ��T_Key_Scan_Reg�Ĵ���,��ӦConst_EN_CH_T_KeyxӦ��1
//void	T_Key_Scan(void);		//T_Keyɨ�躯��(������ʽ�ֲ�����ѯ)
//void	T_Key_Data_Ref_Initial(void);	//��ʼ����һ�ʴ�����������ֵ
//void	Get_T_Key_Signal(void);	//����TKɨ�����жϰ����Ƿ���������������ź� T_Key1_Signal - T_Key12_Signal
//void	Uart_Auto(void);		//Uart�Զ���ʼ��
//void	Sleep_Mode(void);		//˯��ģʽ,����Const_Wakeup_CH_T_Keyx��Const_EN_CH_T_Keyx���趨����
//T_Key_Scan_Reg				//TKɨ��Ĵ���(16λ) 
//T_Key_Signal					//������־�Ĵ���(16λ) 
//----------------------------------*/
