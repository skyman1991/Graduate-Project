#include "common.h"
#include "A7129.h"

 const u8  ID_Tab[8]={0x34,0x75,0xC5,0x8C,0xC7,0x33,0x45,0xE7};   //ID code
u16 RxCnt = 0;
u8 tmpbuf[64];
u32 Err_ByteCnt;
u32 Err_BitCnt;
const u8 BitCount_Tab[16]={0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};

u8  PN9_Tab[]=
{   0xFF,0x83,0xDF,0x17,0x32,0x09,0x4E,0xD1,
    0xE7,0xCD,0x8A,0x91,0xC6,0xD5,0xC4,0xC4,
    0x40,0x21,0x18,0x4E,0x55,0x86,0xF4,0xDC,
    0x8A,0x15,0xA7,0xEC,0x92,0xDF,0x93,0x53,
    0x30,0x18,0xCA,0x34,0xBF,0xA2,0xC7,0x59,
    0x67,0x8F,0xBA,0x0D,0x6D,0xD8,0x2D,0x7D,
    0x54,0x0A,0x57,0x97,0x70,0x39,0xD2,0x7A,
    0xEA,0x24,0x33,0x85,0xED,0x9A,0x1D,0xE0
};	// This table are 64bytes PN9 pseudo random code.


static void A7139_WriteReg(u8 regAddr, u16 regVal)
{
    SCS = 0;
    regAddr |= CMD_Reg_W;
	
    SPIx_WriteByte(regAddr);
    delay_us(10);
    SPIx_WriteWord(regVal);
	  delay_us(10);
    SCS = 1;
}

static u16 A7139_ReadReg(u8 regAddr)
{
    u16 regVal;
    SCS = 0;
    regAddr |= CMD_Reg_R;
    SPIx_WriteByte(regAddr);
    delay_us(10);
    regVal=SPIx_ReadWord();
	  delay_us(10);
    SCS = 1;
    return regVal;
}

static void A7139_WritePageA(u8 address, u16 dataWord)
{
    u16 tmp;
    tmp = address;
    tmp = ((tmp << 12) | A7139Config[CRYSTAL_REG]);
    A7139_WriteReg(CRYSTAL_REG, tmp);
    A7139_WriteReg(PAGEA_REG, dataWord);
}

static void A7139_WritePageB(u8 address, u16 dataWord)
{
    u16 tmp;
    tmp = address;
    tmp = ((tmp << 7) | A7139Config[CRYSTAL_REG]);
    A7139_WriteReg(CRYSTAL_REG, tmp);
    A7139_WriteReg(PAGEB_REG, dataWord);
}

static u16 A7139_ReadPageA(u8 address)
{
    u16 tmp;
    tmp = address;
    tmp = ((tmp << 12) | A7139Config[CRYSTAL_REG]);
    A7139_WriteReg(CRYSTAL_REG, tmp);
    tmp = A7139_ReadReg(PAGEA_REG);
    return tmp;
}

u16 look;
static void A7139_Config(void)
{
	u8 i;
	for(i=0; i<8; i++)
        A7139_WriteReg(i, A7139Config[i]);
	for(i=10; i<16; i++)
        A7139_WriteReg(i, A7139Config[i]);
     for(i=0; i<16; i++)
        A7139_WritePageA(i, A7139Config_PageA[i]);
	for(i=0; i<5; i++)
        A7139_WritePageB(i, A7139Config_PageB[i]);
	look = A7139_ReadReg(SYSTEMCLOCK_REG);
	if(look != A7139Config[SYSTEMCLOCK_REG])
	{
		Err_State();		
	}
}

void Err_State(void)
{
	int i=0;	
	while(1)
		{
			LED1_REV();
			LED2_REV();
			LED3_REV();
			LED4_REV();
			//for(i=0;i<100;i++)
			//		asd[i]=A7139_ReadReg(0x01);
			delay_ms(1000);
		}
}
static u8 A7139_Cal(void)
{
	u8  fbcf;	//IF Filter
	u8  vbcf;	//VCO Current
	u8  vccf;	//VCO Band
	u16 tmp;
    //IF calibration procedure @STB state
	A7139_WriteReg(MODE_REG, A7139Config[MODE_REG] | 0x0802);			//IF Filter & VCO Current Calibration
     do{
		tmp = A7139_ReadReg(MODE_REG);
     }while(tmp & 0x0802);
    //for check(IF Filter)
     tmp = A7139_ReadReg(CALIBRATION_REG);
     //fb = tmp & 0x0F;
     //fcd = (tmp>>11) & 0x1F;
     fbcf = (tmp>>4) & 0x01;
     if(fbcf)
     {
		Err_State();
     }
	//for check(VCO Current)
     tmp = A7139_ReadPageA(VCB_PAGEA);
	//vcb = tmp & 0x0F;
	vccf = (tmp>>4) & 0x01;
	if(vccf)
	{
        Err_State();
  }
    //RSSI Calibration procedure @STB state
	A7139_WriteReg(ADC_REG, 0x4C00);									//set ADC average=64
     A7139_WritePageA(WOR2_PAGEA, 0xF800);								//set RSSC_D=40us and RS_DLY=80us
	A7139_WritePageA(TX1_PAGEA, A7139Config_PageA[TX1_PAGEA] | 0xE000);	//set RC_DLY=1.5ms
     A7139_WriteReg(MODE_REG, A7139Config[MODE_REG] | 0x1000);			//RSSI Calibration
     do{
		tmp = A7139_ReadReg(MODE_REG);
     }while(tmp & 0x1000);
	A7139_WriteReg(ADC_REG, A7139Config[ADC_REG]);
     A7139_WritePageA(WOR2_PAGEA, A7139Config_PageA[WOR2_PAGEA]);
	A7139_WritePageA(TX1_PAGEA, A7139Config_PageA[TX1_PAGEA]);
    //VCO calibration procedure @STB state
	A7139_WriteReg(MODE_REG, A7139Config[MODE_REG] | 0x0004);		//VCO Band Calibration
	do{
		tmp = A7139_ReadReg(MODE_REG);
	}while(tmp & 0x0004);
		//for check(VCO Band)
	tmp = A7139_ReadReg(CALIBRATION_REG);
	//vb = (tmp >>5) & 0x07;
	vbcf = (tmp >>8) & 0x01;
	if(vbcf)
	{
		Err_State();
	}
	return 0;
}

static void A7139_SetFreq(float rfFreq)
{
	 float  divFreq = rfFreq / 12.800f;  
	 u8  intFreq = (u8)(divFreq); //integer part
	 float  fltFreq = divFreq - intFreq * 1.000f; //fraction part
	 u16 fpFreg	= (u16)(fltFreq * 65536);  //FP register val
	 u16 orgVal;
	 A7139_StrobeCmd(CMD_STBY); //enter stand-by mode
			 //AFC[15:15] = 0
	 orgVal = A7139Config[PLL3_REG] & 0x7FFF;
	 A7139_WriteReg(PLL3_REG,orgVal);
	 		//RFC[15:12] = 0000
	 orgVal = A7139Config[PLL6_REG] & 0x0FFF;
	 A7139_WriteReg(PLL6_REG,orgVal);
	 	//MD1[12:12]=0,1
	 if(rfFreq < 860)	//433-510
		orgVal = A7139Config[PLL4_REG] & 0xEFFF;
	 else	 //868-915
		orgVal = A7139Config[PLL4_REG] | 0x1000;
	 A7139_WriteReg(PLL4_REG,orgVal);
	 		//IP[8:0] = intg
	 orgVal = A7139Config[PLL1_REG] & 0xFF00;
	 A7139_WriteReg(PLL1_REG,orgVal|intFreq);
	 		//FP[15:0] =  fpFreg
	 A7139_WriteReg(PLL2_REG,fpFreg); 
			//FPA[15:0] = 0x0000
	 A7139_WritePageB(IF2_PAGEB,0x0000);	
}

static u8 A7139_RCOSC_Cal(void)
{
	  u8  retry = 0xFF;
	  u16 calbrtVal,t_retry=0xFFFF;
	  		//RCOSC_E[4:4] = 1,enable internal RC Oscillator
	  A7139_WritePageA(WOR2_PAGEA, A7139Config_PageA[WOR2_PAGEA] | 0x0010);
	  do{
		  		//ENCAL[0:0] = 1,then start RC OSC Calbrt
		  A7139_WritePageA(WCAL_PAGEA, A7139Config_PageA[WCAL_PAGEA] | 0x0001);
		  do{
		  	  calbrtVal = A7139_ReadPageA(WCAL_PAGEA) & 0x0001;
		  }while(calbrtVal && t_retry--);
		  		//read NUMLH[9:1]
		  calbrtVal = (A7139_ReadPageA(WCAL_PAGEA) & 0x03FF) >> 1;
		  if(calbrtVal>186 && calbrtVal<198)
			   return OK_RCOSC_CAL;
	  }while(retry--);
	  return ERR_RCOSC_CAL;
}

void A7139_StrobeCmd(u8 cmd)
{
    SCS = 0;
    SPIx_WriteByte(cmd);
    SCS = 1;
}

u8 A7139_Init(float rfFreq)
{
	

	SCS = 1;
	SCK = 0;
	MOSI = 1;
  A7139_StrobeCmd(CMD_RF_RST);	  //reset A7139 chip
	delay_ms(10);
	A7139_Config();		  //config A7139 chip
	delay_ms(10);			  //for crystal stabilized
	A7139_SetCID(0x3475C58B);  //set CID code
	delay_ms(1);
	A7139_SetFreq(rfFreq);	  //set Freq
	delay_ms(10);
	A7139_Cal();
  Correct_State();	
	A7139_StrobeCmd(CMD_STBY);
	
	return 1;		  //IF and VCO calibration
}

u8 A7139_SetCID(u32 id)
{
	SCS = 0;
	SPIx_WriteByte(CMD_ID_W);
	SPIx_WriteByte((u8)(id>>24));
	SPIx_WriteByte((u8)(id>>16));
	SPIx_WriteByte((u8)(id>>8));
	SPIx_WriteByte((u8)id);
	SCS = 1;
	return 0;
}

u16 A7139_ReadPID(void)
{
	u16 pid;
	u16 pagAddr = TX2_PAGEB << 7;
	pagAddr|=A7139Config[CRYSTAL_REG] & 0xF7CF;
	A7139_WriteReg(CRYSTAL_REG, pagAddr);
	pid = A7139_ReadReg(PAGEB_REG);
	return pid;
}

u8 A7139_SetDataRate(u8 datRate)
{
		//enter stand by mode
	A7139_StrobeCmd(CMD_STBY);
	delay_ms(20);
			//set xs[0:0] = 0 to disable XTAL
	A7139_WriteReg(CRYSTAL_REG,A7139Config[CRYSTAL_REG] & 0xFFFE );
	switch(datRate)
	{
		case 2:
		{	
					//CSC[2:0]=[001],Fcsck=3.2MHz
					//IFBW[3:2]=[01],100kHz
					//SDR[15:9]=0x18,DCK=2Kps,Fdev = 7.8125kHz
			A7139_WriteReg(SYSTEMCLOCK_REG,0x6621);	
			A7139_WriteReg(RX1_REG,0x18D4); 
			A7139_WritePageA(TX1_PAGEA,0xF505);
		}
		break;
		case 10:
		{
					//CSC[2:0]=[001],Fcsck=6.4MHz
					//IFBW[3:2]=[01],100kHz
					//SDR[15:9]=0x04,DCK=10Kps,Fdev = 37.5kHz
		 	A7139_WriteReg(SYSTEMCLOCK_REG,0x01221);			 		
			A7139_WriteReg(RX1_REG,0x18D4);
			A7139_WritePageA(TX1_PAGEA,0xF706);
		}
		break;
		case 50:
		{
			 		//CSC[2:0]=[011],Fcsck=3.2MHz
					//IFBW[3:2]=[00],50Kps 
					//SDR[15:9]=0x00,DCK=50kHz,Fdev = 18.75kHz
			A7139_WriteReg(SYSTEMCLOCK_REG,0x0023);
			A7139_WriteReg(RX1_REG,0x18D0);
			A7139_WritePageA(TX1_PAGEA,0xF606);
		}
		break;
		case 100:												
		{
					//CSC[2:0]=[001] ,Fcsck=6.4MHz
					//IFBW[3:2]=[01],100kHz
					//SDR[15:9]=0x00,DCK=100Kps
			A7139_WriteReg(SYSTEMCLOCK_REG,0x0021);
			A7139_WriteReg(RX1_REG,0x18D4);
			A7139_WritePageA(TX1_PAGEA,0xF706);
		}
		break;
		case 150:
		{
			//Cause LO is 12.8MHz
			//must use Pll clk gen,complement in detail later
			//also can be implemented by the users themselves
			//IFBW=[10] <=> 150kHz
			//DCK=150K
			//CSC=000,fcsck=9.6MHz
			//SDR=0x00
			//DMOS=1,IFBW=150KHz
		}
		break;
		default:
						// set xs[0:0] = 1 to open XTAL
			A7139_WriteReg(CRYSTAL_REG,A7139Config[CRYSTAL_REG] | 0x0001 );
			delay_ms(20);
			return ERR_PARAM;
	}
					// set xs[0:0] = 1 to enable XTAL
	A7139_WriteReg(CRYSTAL_REG,A7139Config[CRYSTAL_REG] | 0x0001 );
	delay_ms(20);
	return 0;
}

u8 A7139_SetPackLen(u8 len)
{
	u16 pagVal;
	A7139_StrobeCmd(CMD_STBY);
			//FEP[7:0]
	pagVal = A7139Config_PageA[FIFO_PAGEA] & 0xFF00;
	A7139_WritePageA(FIFO_PAGEA,pagVal|(len-1));
			//FEP[13:8]
	pagVal = A7139Config_PageA[VCB_PAGEA] & 0xC0FF;
	A7139_WritePageA(VCB_PAGEA,pagVal);
	return 0;			
}

u8 A7139_SetCIDLen(u8 len)
{
	switch(len)
	{
		case 2:
			{
				A7139_WritePageA(CODE_PAGEA,A7139Config[CODE_PAGEA] & 0xBFFB);
			}
			break;
		case 4:
			{
				A7139_WritePageA(CODE_PAGEA,A7139Config[CODE_PAGEA] & 0xBFFB);
				A7139_WritePageA(CODE_PAGEA,A7139Config[CODE_PAGEA] | 0x0004);
			}
			break;
		default :
		return ERR_PARAM;
	}
	return 0;
}

void A7139_WriteFIFO(u8 *buf,u8 bufSize)
{
	A7139_StrobeCmd(CMD_TFR);	
     delay_ms(1);
	SCS = 0;
	SPIx_WriteByte(CMD_FIFO_W);
	while(bufSize--)
		SPIx_WriteByte(*buf++);
	SCS = 1;	
}

void A7139_ReadFIFO(u8 *buf,u8 bufSize)
{
	A7139_StrobeCmd(CMD_RFR);
	delay_us(2);
	SCS = 0;
	SPIx_WriteByte(CMD_FIFO_R);
	while(bufSize--)
		*buf++ = SPIx_ReadByte(); 
	SCS = 1;							 
}

u8 A7139_IsBatteryLow(u8 low2_x)
{
	u16 pagVal;
	if(low2_x<0x02 || low2_x>0x07)
		return ERR_PARAM;
	A7139_StrobeCmd(CMD_STBY);
			//BVT[3:1] BDS[0:0]
	pagVal= A7139Config[PM_PAGEA] & 0xFFF0;
	A7139_WritePageA(PM_PAGEA,pagVal | (low2_x << 1) | 0x01);
	delay_us(10); //delay 5us at least 
			//read VBD[7:7]
	return !((A7139_ReadPageA(WOR1_PAGEA) & 0x0080) >> 7);
}
u8 A7139_GetRSSI()
{	
	u8  rssi;
	u16 t_retry = 0xFFFF;
		//entry RX mode
	A7139_StrobeCmd(CMD_RX);	
			//CDM[8:8] = 0
	A7139_WriteReg(ADC_REG,A7139Config[ADC_REG] & 0xFEFF);
			//ADCM[0:0] = 1
	A7139_WriteReg(MODE_REG,A7139_ReadReg(MODE_REG) | 0x0001);
	do
	{
		rssi = A7139_ReadReg(MODE_REG) & 0x0001; //ADCM auto clear when measurement done
			
	}while(t_retry-- && rssi);
	if(t_retry>0)
		rssi=(A7139_ReadReg(ADC_REG) & 0x00FF);  //ADC[7:0] is the value of RSSI
	else
		rssi = ERR_GET_RSSI;
	A7139_StrobeCmd(CMD_STBY);
	return rssi;		
}

u8 A7139_WOT(void)
{
	if(A7139_RCOSC_Cal()==ERR_RCOSC_CAL)
		return ERR_RCOSC_CAL;
	A7139_StrobeCmd(CMD_STBY);
		//GIO1=FSYNC, GIO2=WTR	
	A7139_WritePageA(GIO_PAGEA, 0x0045);
		//setup WOT Sleep time
	A7139_WritePageA(WOR1_PAGEA, 0x027f);
		//WMODE=1 select WOT function
	A7139_WriteReg(PIN_REG, A7139Config[PIN_REG] | 0x0400);
		//WORE=1 to enable WOT function		
	A7139_WriteReg(MODE_REG, A7139Config[MODE_REG] | 0x0200);
	//while(1); //注意此处为死循环，代码只为演示之用，用户必须按业务实际逻辑进行需改
	return 0;
}
u8 A7139_WOR_BySync(void)
{
	A7139_StrobeCmd(CMD_STBY);
			//GIO1=FSYNC, GIO2=WTR	
	A7139_WritePageA(GIO_PAGEA, 0x0045);
			//setup WOR Sleep time and Rx time
	A7139_WritePageA(WOR1_PAGEA, 0xFC05);
	if(A7139_RCOSC_Cal()==ERR_RCOSC_CAL)
		return ERR_RCOSC_CAL;
			//enable RC OSC & WOR by sync
	A7139_WritePageA(WOR2_PAGEA, A7139Config_PageA[WOR2_PAGEA] | 0x0010);
			//WORE=1 to enable WOR function
	A7139_WriteReg(MODE_REG, A7139Config[MODE_REG] | 0x0200);
	
	//while(GIO1==0);		//Stay in WOR mode until receiving preamble(preamble ok)
	return 0;
}
u8 A7139_WOR_ByPreamble(void)
{
	A7139_StrobeCmd(CMD_STBY);
	A7139_WritePageA(GIO_PAGEA, 0x004D);	//GIO1=PMDO, GIO2=WTR

	//Real WOR Active Period = (WOR_AC[5:0]+1) x 244us,XTAL and Regulator Settling Time
	//Note : Be aware that Xtal settling time requirement includes initial tolerance, 
	//       temperature drift, aging and crystal loading.
	A7139_WritePageA(WOR1_PAGEA, 0xFC05);	//setup WOR Sleep time and Rx time
			 	//RC Oscillator Calibration
	if(A7139_RCOSC_Cal()==ERR_RCOSC_CAL)
		return ERR_RCOSC_CAL;
	A7139_WritePageA(WOR2_PAGEA, A7139Config_PageA[WOR2_PAGEA] | 0x0030);	//enable RC OSC & WOR by preamble
	
	A7139_WriteReg(MODE_REG, A7139Config[MODE_REG] | 0x0200);				//WORE=1 to enable WOR function
	
	//while(GIO1==0);		//Stay in WOR mode until receiving preamble(preamble ok)
	return 0;
}
void Correct_State(void)
{
			LED1_REV();
			LED2_REV();
			LED3_REV();
			LED4_REV();
			delay_ms(100);
	    LED1_REV();
			LED2_REV();
			LED3_REV();
			LED4_REV();
			delay_ms(100);
	    LED1_REV();
			LED2_REV();
			LED3_REV();
			LED4_REV();
			delay_ms(100);
	    LED1_REV();
			LED2_REV();
			LED3_REV();
			LED4_REV();
}

void Interrupt_Init(void)
{
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);							//使能复用功能时钟

		//GPIOA.0 中断线以及中断初始化配置 上升沿触发 PA0  WK_UP
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6); 
		EXTI_InitStructure.EXTI_Line=EXTI_Line6;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);																	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;						//使能按键KEY1,KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;						//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;									//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  														//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	  A7139_StrobeCmd(CMD_PLL);
		delay_us(2);
		A7139_StrobeCmd(CMD_RX);
		delay_us(2);

}


