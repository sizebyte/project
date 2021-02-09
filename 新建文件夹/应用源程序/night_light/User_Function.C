/**************************************************************
	Filename:	User_Function
	Data	:	2021/1/6 19:06:02
	Function:	Users can add their own program features
**************************************************************/
//	En_Interrupt;	//开启全局中断	//用UART时请使用这种写法开中断
//	Dis_Interrupt;	//关闭中断		//用UART时请使用这种写法关中断
//***************************************************//
UserFile_TOP:
//***************************************************//

//User's Variable Define
Variable_Define:
#define NIGHT 0// PB.0  //1：晚上
#define MEUN_MAX_LEVEL 0x08
#define BUFF_TIME0  1 //长按LED缓冲时间
#define BUFF_TIME1  2  //呼吸灯缓冲时间
#define LED        PA.4
//Insert variable define Code
word t16_cnt;//定时器初始值
byte R_4ms_cnt;//4ms时间计数
Word R_long_time;//长按计时
byte R_key_cnt;//按键计数
byte R_double_press_cnt;//双击时间间隔
byte w_led_dudy;//白灯占空比
byte y_led_dudy;//黄灯占空比
byte y_led_dudy_save;
byte w_led_dudy_save;
byte wy_led_dudy_save;
byte R_led_pwm_temp;
byte R_key_meun;
byte R_breathe_cnt;//呼吸时间计数

bit F_4ms_flag;
bit F_long_press;//长按标志
bit F_LED_breathe_flag;//呼吸标志
bit F_overflow_flag;//1：亮度上调 0：亮度下调

void timer16_Init(void);
void pwm2_Init(void);
void pwm3_Init(void);
void T_pwm_updata(void);

//User's variable initialization Settings.
void Variable_Init(void)
{

	//Insert variable Initial Code
	timer16_Init();
    pwm2_Init();
	pwm3_Init();
	w_led_dudy_save =128;
	y_led_dudy_save =128;
	wy_led_dudy_save =128;
	if(NIGHT) //上电检测到黑夜就开启灯。
	{
		R_key_meun =0x01;
        w_led_dudy=128;
		y_led_dudy=128;
		T_pwm_updata();
	}
	Pre_T_Key8_Release=1;
}

//IO设置，部分IO P-Touch已经设置
void	IO_Init(void)
{
	//----------------------------
	PA		=	0b0000_0000;
	PAC		=	0b0111_1111;	//1:输出   0:输入
	PAPH	=	0b0000_0000;	//1:加上拉 0:不加上拉
	PB		=	0b0000_0000;
	PBC		=	0b1111_1110;
	PBPH	=	0b0000_0001;

	PADIER	=	0b0010_0000;	//CS脚及对应T_Key设置为模拟IO(设为0),用上位机时UART_IO设置为数字IO(设为1)
	PBDIER	=	0b0000_0000;	//CS脚及对应T_Key设置为模拟IO(设为0),用上位机时UART_IO设置为数字IO(设为1)

	//TPS = 0b00_00_11_10;	//EMI Enable

	//----------------------------
	//User's Other IO Define
	//----------------------------
}
//***************************************************/
void timer16_Init(void)
{
	$ T16M SYSCLK,/1,BIT15;
	$ INTEGS  BIT_R;
    t16_cnt = 32368;
	stt16   t16_cnt;
	INTEN.T16=1;
	Intrq.T16 = 0;
}
void pwm2_Init(void)
{
	$ TM2S 8BIT,/1,/2;//pwm=31khZ
	TM2C = 0b0010_10_1_0; //PA3输出PWM
	TM2CT = 0;
}
void pwm3_Init(void)
{
	$ TM3S 8BIT,/1,/2;//pwm=31khZ
	TM3C = 0b0010_10_1_0; //PA5输出PWM
	TM3CT = 0;
}
void pwm_disenable(void)
{				
   TM2B= 0;
   TM3B= 0;
   TM2C = 0; 
   TM3C = 0; 
}
void T_pwm_updata(void)
{
   switch(R_key_meun){
					 case 0x00:
                        pwm_disenable();
						break;
					 case 0x01: //黄
						TM2B= 0;
                        TM3B= y_led_dudy;				
						break;
					 case 0x02:
						TM2B= w_led_dudy;
                        TM3B= y_led_dudy;
						break;
					 case 0x04:
						TM2B= w_led_dudy;
                        TM3B= y_led_dudy;
						break;
					 case 0x08:
						TM2B= w_led_dudy;
                        TM3B= 0;
						break;
					 default:
						break;
	}
}
void	T_Key_Warning(void)		//处理Tkey计数溢出异常
{
	if(Intrq.Tk_OV)
	{
		Intrq.Tk_OV	=	0;
		//此处处理TK_OV信号，Intrq.Tk_OV = 1表示TK计数器溢出
		//此时则需要减小外部VC电容
		//或降低PT_Lib.h中对Const_Touch_VRef的设定
	}
}

void	T_Key8_Func(void)
{
	if(T_Key8_Signal==1 && Pre_T_Key8_Release==1)
	{
		Pre_T_Key8_Release	=	0;
		LED = 1;
	//-----------------------------------------//
	//-----------------------------------------//
	}
	elseif(T_Key8_Signal==0 && Pre_T_Key8_Release==0)
	{
		LED = 0;
		Pre_T_Key8_Release	=	1;
		if(!F_long_press){//不是长按
		   R_key_meun=R_key_meun<<1;
		   if(!R_key_meun || R_key_meun > MEUN_MAX_LEVEL){
			   if(R_key_meun>MEUN_MAX_LEVEL) w_led_dudy_save = w_led_dudy;
			   R_key_meun=0x01;			   
	     	}
		   R_key_cnt++;
		   switch(R_key_meun){
			  case 0x01:
				pwm2_Init();
				pwm3_Init();
                w_led_dudy=0x00;
		        y_led_dudy= y_led_dudy_save;
				R_led_pwm_temp= y_led_dudy_save;
	            break;
	            case 0x02: 
                F_LED_breathe_flag=1;
                y_led_dudy_save = y_led_dudy;
			    w_led_dudy=wy_led_dudy_save;
	    	    y_led_dudy=wy_led_dudy_save;
				R_led_pwm_temp= wy_led_dudy_save;
	    	    break;
	            case 0x04: 
	    		F_LED_breathe_flag=0;
	    	    w_led_dudy = wy_led_dudy_save;
	    	    y_led_dudy = wy_led_dudy_save;
				R_led_pwm_temp = wy_led_dudy_save;
	    	    break;
	            case 0x08: //白
	    	    wy_led_dudy_save = w_led_dudy;
	        	w_led_dudy=w_led_dudy_save;
				R_led_pwm_temp= w_led_dudy_save;
		        y_led_dudy=0x00;
	        	break;
	            default:
		        break;
		     }
		}
		else {
		   F_long_press=0;
		   if(F_overflow_flag) F_overflow_flag=0;
		   else F_overflow_flag=1;	   
		}

		
	}
}
void T_LED_breathe(void)
{
	if(F_LED_breathe_flag){
		R_breathe_cnt++;
		if(R_breathe_cnt>BUFF_TIME1){
           R_breathe_cnt=0;
		   if(F_overflow_flag){
			   if(w_led_dudy==255){
                  F_overflow_flag=0;
				  R_led_pwm_temp=254;
			   }
				   //w_led_dudy++;
				  R_led_pwm_temp++;	   
			   
		   }
		   else{
			   if(w_led_dudy<10) F_overflow_flag=1;
			   R_led_pwm_temp--;
		   }
		   w_led_dudy=R_led_pwm_temp;
	       y_led_dudy=R_led_pwm_temp;
		}
	}
}
void T_long_press(void)
{
	if(!Pre_T_Key8_Release  && !F_long_press){
	   R_long_time++;
	   if(R_long_time>350 && R_key_meun>0)  F_long_press=1;//长按 时间1.4S
	}
	else R_long_time=0;
	if(F_LED_breathe_flag ==0 && F_long_press){
		R_breathe_cnt++;
		if(R_breathe_cnt>BUFF_TIME0){
           R_breathe_cnt=0;
		   if(F_overflow_flag && R_led_pwm_temp<255)  R_led_pwm_temp++;			
		   if(F_overflow_flag==0 && R_led_pwm_temp>11) R_led_pwm_temp--;
		  }  
	}
	y_led_dudy = R_led_pwm_temp;
	w_led_dudy = R_led_pwm_temp;
}
 //双击检测
void T_key_press_cnt(void)
{
  if(R_key_cnt>0){
       R_double_press_cnt++;
	   if(R_double_press_cnt==250 && R_key_cnt==2) { //双击关闭设备
	      R_double_press_cnt = 0;
		  R_key_cnt = 0;
          F_LED_breathe_flag =0;
		  w_led_dudy = 0x00;
		  y_led_dudy = 0x00;
		  R_key_meun = 0x00;
        }
	   else if(R_double_press_cnt==0xff){
		 R_double_press_cnt = 0;
		  R_key_cnt = 0;
	   }
    }
}
void scan_light(void)
{
   if(!NIGHT){
	 R_key_cnt = 0;
     F_LED_breathe_flag =0;
	 w_led_dudy = 0x00;
	 w_led_dudy = 0x00;
	 R_key_meun = 0x00;
   }
  else{
		R_key_meun =0x01;
        w_led_dudy=0xff;
		y_led_dudy=0xff;
		T_pwm_updata();
	}
}
void	T_Key_Function(void)	//触摸按键成立后命令
{
	T_Key8_Func();
}

void	User_other_Func(void)
{
	//User's Code
	if(F_4ms_flag){
		F_4ms_flag = 0;
		T_long_press();
        T_LED_breathe();
		T_key_press_cnt();
//		scan_light();
	}

	T_pwm_updata();
}

//-------------------------------------
void	Interrupt (void)
{
	pushaf;

#if Const_EN_Uart
	Auto_Scan_Twatch();	//直接在此调用即可自动扫描Twatch,配合Uart_Auto()使用
						//注意,使用此功能时请勿关闭全局中断,否则无法检测上位机
						//检测到上位机后或低电平唤醒UART后此函数失效,Uart会自动发送数据到上位机,主程序中调用Uart_Auto()即可
#endif
	if (Intrq.T16 && Inten.T16)
	{	//	T16 Trig
		//	User can add code
		Intrq.T16	=	0;
		t16_cnt = 28764;
		stt16   t16_cnt;
		R_4ms_cnt++;
		if(R_4ms_cnt>3)
		{
			F_4ms_flag=1;
			R_4ms_cnt=0;
		}
     	
		
		//...
	}

	popaf;
}
