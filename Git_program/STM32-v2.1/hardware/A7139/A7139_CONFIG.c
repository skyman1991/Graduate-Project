#include "A7139_CONFIG.h"
#include "common.h"
#if CONFIG_DATA_RATE == 2

const u16 CODE A7139Config[]=
{
		0x6221,             //[0x00] System Clock register
		0x0A24,             //[0x01] PLL I register
		0xB805,             //[0x02] PLL II register
		0x0000,             //[0x03] PLL III register
		0x0A20,             //[0x04] PLL IV register
		0x0024,             //[0x05] PLL V register
		0x0000,             //[0x06] PLL VI register
		0x0011,             //[0x07] Crystal register
		0x0000,             //PAGE A
		0x0000,			//PAGE B
		0x18D4,             //[0x0A] RX I register
		0x7009,             //[0x0B] RX II register
		0xC400,             //[0x0C] ADC register
		0x0800,             //[0x0D] Pin Control register
		0x4845,             //[0x0E] Calibration register
		0x20C0              //[0x0F] Mode Control register
};

const u16 CODE A7139Config_PageA[]= 
{
		0xF505,             //[0x08][Page0] TX I register
		0x0000,             //[0x08][Page1] WOR I register
		0x0000,            //[0x08][Page2] WOR II register
		0x1107,             //[0x08][Page3] RF Current register
		0x8170,             //[0x08][Page4] Power Manage register
		0x0201,             //[0x08][Page5] AGC RSSI Threshold register
		0x400F,             //[0x08][Page6] AGC Control register
		0x2AC0,             //[0x08][Page7] AGC Control II register
		0x0045,             //[0x08][Page8] GPIO register
		0xD281,             //[0x08][Page9] CKO register
		0x0004,             //[0x08][Page10] VCO Current register
		0x0825,             //[0x08][Page11] Channel Group I register
		0x0127,             //[0x08][Page12] Channel Group II register
		0x003F,             //[0x08][Page13] FIFO register
		0x155F,             //[0x08][Page14] CODE register
		0x0000              //[0x08][Page15] WCAL register
};

const u16 CODE A7139Config_PageB[]=
{
		0x037F,             //[0x09][Page0] TX II register
		0x8400,             //[0x09][Page1] IF I register
		0x0000,             //[0x09][Page2] IF II register
		0x0000,             //[0x09][Page3] ACK register
		0x0000              //[0x09][Page4] ART register
};

#elif CONFIG_DATA_RATE == 10

const u16 CODE A7139Config[]=		//470MHz, 10kbps (IFBW = 100KHz, Fdev = 37.5KHz), Crystal=12.8MHz
{
		0x1221,		//SYSTEM CLOCK register,
		0x0A24,		//PLL1 register,
		0xB805,		//PLL2 register,	470.001MHz
		0x0000,		//PLL3 register,
		0x0B30,		//PLL4 register,
		0x0024,		//PLL5 register,
		0x0000,		//PLL6 register,
		0x0011,		//CRYSTAL register,
		0x0000,		//PAGEA,
		0x0000,		//PAGEB,
		0x18D4,		//RX1 register, 	IFBW=100KHz, ETH=1	
		0x7009,		//RX2 register, 	by preamble
		0x4400,		//ADC register,	   	
		0x0800,		//PIN CONTROL register,		Use Strobe CMD
		0x4845,		//CALIBRATION register,
		0x20C0		//MODE CONTROL register, 	Use FIFO mode
};

const u16 CODE A7139Config_PageA[]=   //470MHz, 10kbps (IFBW = 100KHz, Fdev = 37.5KHz), Crystal=12.8MHz
{
		0x1706,		//TX1 register, 	Fdev = 37.5kHz
		0x0000,		//WOR1 register,
		0x0000,		//WOR2 register,
		0x1107,		//RFI register, 	Enable Tx Ramp up/down  
		0x8170,		//PM register,		CST=1
		0x0201,		//RTH register,
		0x40CF,		//AGC1 register,	
		0x6FC0,		//AGC2 register, 
		0x0045,		//GIO register, 	GIO2=WTR, GIO1=FSYNC
		0xD281,		//CKO register
		0x0004,		//VCB register,
		0x0825,		//CHG1 register, 	480MHz
		0x0127,		//CHG2 register, 	500MHz
		0x003F,		//FIFO register, 	FEP=63+1=64bytes
		0x155F,		//CODE register, 	Preamble=4bytes, ID=4bytes
		0x0000		//WCAL register,
};

const u16 CODE A7139Config_PageB[]=   //470MHz, 10kbps (IFBW = 100KHz, Fdev = 37.5KHz), Crystal=12.8MHz
{
		0x037F,		//TX2 register,
		0x8400,		//IF1 register, 	Enable Auto-IF, IF=200KHz
		0x0000,		//IF2 register,
		0x0000,		//ACK register,
		0x0000		//ART register,
};

#elif CONFIG_DATA_RATE == 50//DR=50,IFBW=50

const u16 CODE A7139Config[]=
{
		0x0023,             //[0x00] System Clock register
		0x0A24,             //[0x01] PLL I register
		0xB805,             //[0x02] PLL II register
		0x0000,             //[0x03] PLL III register
		0x0A20,             //[0x04] PLL IV register
		0x0024,             //[0x05] PLL V register
		0x0000,             //[0x06] PLL VI register
		0x0001,             //[0x07] Crystal register
		0x0000,		     //[0x08] PAGE A
		0x0000,	          //[0x07] PAGE B
		0x18D0,             //[0x0A] RX I register
		0x7009,             //[0x0B] RX II register
		0x4400,             //[0x0C] ADC register
		0x0800,             //[0x0D] Pin Control register
		0x4845,             //[0x0E] Calibration register
		0x20C0              //[0x0F] Mode Control register
};

const u16 CODE A7139Config_PageA[]= 
{
		0xF606,             //[0x08][Page0] TX I register
		0x0000,             //[0x08][Page1] WOR I register
		0xF800,             //[0x08][Page2] WOR II register
		0x1107,             //[0x08][Page3] RF Current register
		0x0170,             //[0x08][Page4] Power Manage register
		0x0201,             //[0x08][Page5] AGC RSSI Threshold register
		0x400F,             //[0x08][Page6] AGC Control register
		0x2AC0,             //[0x08][Page7] AGC Control II register
		0x0045,             //[0x08][Page8] GPIO register
		0xD281,             //[0x08][Page9] CKO register
		0x0004,             //[0x08][Page10] VCO Current register
		0x0825,             //[0x08][Page11] Channel Group I register
		0x0127,             //[0x08][Page12] Channel Group II register
		0x003F,             //[0x08][Page13] FIFO register
		0x155F,             //[0x08][Page14] CODE register
		0x0000              //[0x08][Page15] WCAL register
};

const u16 CODE A7139Config_PageB[]=
{
		0x037F,             //[0x09][Page0] TX II register
		0x8200,             //[0x09][Page1] IF I register
		0x0000,             //[0x09][Page2] IF II register
		0x0000,             //[0x09][Page3] ACK register
		0x0000              //[0x09][Page4] ART register
};

#elif CONFIG_DATA_RATE == 100//DR=100,IFBW=100

const u16 CODE A7139Config[]=
{
	0x0021,             //[0x00] System Clock register
	0x0A24,             //[0x01] PLL I register
	0xB805,             //[0x02] PLL II register
	0x0000,             //[0x03] PLL III register
	0x0A20,             //[0x04] PLL IV register
	0x0027,             //[0x05] PLL V register
	0x0000,             //[0x06] PLL VI register
	0x0011,             //[0x07] Crystal register
	0x0000,		     //PAGE A
	0x0000,		     //PAGE B
	0x18D4,             //[0x0A] RX I register
	0x7009,             //[0x0B] RX II register
	0xC400,             //[0x0C] ADC register
	0x0800,             //[0x0D] Pin Control register
	0x4845,             //[0x0E] Calibration register
	0x20C0             //[0x0F] Mode Control register
};

const u16 CODE A7139Config_PageA[]= 
{
	0xF706,             //[0x08][Page0] TX I register
	0x0000,             //[0x08][Page1] WOR I register
	0xF800,             //[0x08][Page2] WOR II register
	0x1107,             //[0x08][Page3] RF Current register
	0x0170,             //[0x08][Page4] Power Manage register
	0x0201,             //[0x08][Page5] AGC RSSI Threshold register
	0x400F,             //[0x08][Page6] AGC Control register
	0x2AC0,             //[0x08][Page7] AGC Control II register
	0x0C41,             //[0x08][Page8] GPIO register
	0xD281,             //[0x08][Page9] CKO register
	0x0004,             //[0x08][Page10] VCO Current register
	0x0825,             //[0x08][Page11] Channel Group I register
	0x0127,             //[0x08][Page12] Channel Group II register
	0x003F,             //[0x08][Page13] FIFO register
	0x5507,             //[0x08][Page14] CODE register
	0x0000              //[0x08][Page15] WCAL register
};

const u16 CODE A7139Config_PageB[]=
{
	0x035F,             //[0x09][Page0] TX II register
	0x8400,             //[0x09][Page1] IF I register
	0x0000,             //[0x09][Page2] IF II register
	0x0000,             //[0x09][Page3] ACK register
	0x0000              //[0x09][Page4] ART register
};

#elif CONFIG_DATA_RATE == 250
const u16  A7139Config[]=
{
	0x0020,             //[0x00] System Clock register
	0x0A1D,             //[0x01] PLL I register
	0x6004,             //[0x02] PLL II register
	0x0000,             //[0x03] PLL III register
	0x0A20,             //[0x04] PLL IV register
	0x001D,             //[0x05] PLL V register
	0x0000,             //[0x06] PLL VI register
	0x0011,             //[0x07] Crystal register
	0x0000,
	0x0000,
	0x18DC,             //[0x0A] RX I register
	0x7009,             //[0x0B] RX II register
	0x8400,             //[0x0C] ADC register
	0x0800,             //[0x0D] Pin Control register
	0x4845,             //[0x0E] Calibration register
	0x20C0,             //[0x0F] Mode Control register
};

const u16  A7139Config_PageA[]= 
{
	0xF530,             //[0x08][Page0] TX I register
	0x0000,             //[0x08][Page1] WOR I register
	0x0000,             //[0x08][Page2] WOR II register
	0x1107,             //[0x08][Page3] RF Current register
	0x0170,             //[0x08][Page4] Power Manage register
	0x0201,             //[0x08][Page5] AGC RSSI Threshold register
	0x400F,             //[0x08][Page6] AGC Control register
	0x2AC0,             //[0x08][Page7] AGC Control II register
	0x0C41,             //[0x08][Page8] GPIO register
	0xD281,             //[0x08][Page9] CKO register
	0x0004,             //[0x08][Page10] VCO Current register
	0x001E,             //[0x08][Page11] Channel Group I register
	0x041F,             //[0x08][Page12] Channel Group II register
	0x003F,             //[0x08][Page13] FIFO register
	0x155F,             //[0x08][Page14] CODE register
	0x0000,             //[0x08][Page15] WCAL register
};

const u16  A7139Config_PageB[]=
{
	0x035F,             //[0x09][Page0] TX II register
	0x8800,             //[0x09][Page1] IF I register
	0x0000,             //[0x09][Page2] IF II register
	0x00C0,             //[0x09][Page3] ACK register
	0x0000,             //[0x09][Page4] ART register
};
#endif
