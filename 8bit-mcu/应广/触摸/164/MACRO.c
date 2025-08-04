


byte TOUCH_CH = 0;
word TK_Math  = 0;

 //   Touch_X TK,TK_Math,0;--------∏¥÷∆ π”√

Touch_X  MACRO TKX,TK_Math,TK_Mode  
	.ifnb <TKx>
		.ifidni	TKx,TK1
			TKE1 = 0B0000_001_0;
			TKE2 = 0B000_00000;
		.elseifidni TKx,TK2
			TKE1 = 0B0000_010_0;
			TKE2 = 0B000_00000;
		.elseifidni TKx,TK3
			TKE1 = 0B0000_100_0;
			TKE2 = 0B000_00000;
		.elseifidni TKx,TK4
			TKE1 = 0B0001_000_0;
			TKE2 = 0B000_00000;
		.elseifidni TKx,TK5
			TKE1 = 0B0010_000_0;
			TKE2 = 0B000_00000;
		.elseifidni TKx,TK6
			TKE1 = 0B0100_000_0;
			TKE2 = 0B000_00000;
		.elseifidni TKx,TK7
			TKE1 = 0B1000_000_0;
			TKE2 = 0B000_00000;
		.elseifidni TKx,TK8
			TKE1 = 0B0000_000_0;
			TKE2 = 0B000_00001;
		.elseifidni TKx,TK9
			TKE1 = 0B0000_000_0;
			TKE2 = 0B000_00010;
		.elseifidni TKx,TK10
			TKE1 = 0B0000_000_0;
			TKE2 = 0B000_00100;
		.elseifidni TKx,TK11
			TKE1 = 0B0000_000_0;
			TKE2 = 0B000_01000;
		.elseifidni TKx,TK12
			TKE1 = 0B0000_000_0;
			TKE2 = 0B000_10000;
		.else
		.error Touch Channel Setup Error,please check! TK1~TK12
		.endif
	.else
		.error  Touch channel not set! TK1~TK12
	.endif


	.ifnb <TK_Mode>
		
		.if		TK_Mode==0
				tps2 |=0b00_00_0000; 
		.elseif 	TK_Mode==1
				tps2 |=0b01_00_0000;
		.else
			.error Touch mode setting error! 0~1
		.endif
	.else
		.error Touch mode is not set! 0~1
	.endif
	//touch_key_init();
	TS = 0x23;
	$ TCC TK_RUN;
	do
	{
		TOUCH_CH = TCC & 0x70;
		TK_Math		=	0xFFFF;
	}while (TOUCH_CH);
	TK_Math $ 1 = TKCH & 0x0F;
	TK_Math $ 0 = TKCL;


endm























