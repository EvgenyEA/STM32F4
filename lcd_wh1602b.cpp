#include "lcd_wh1602b.h"
#include "periphery.h"

WH1602B LCD;

// Methods to drive LCD WH1602B
// --------------------- Initialize russian font ------------------------

	uint8_t WH1602B::RUSSIAN[64] =
	{ 
		0x41,	// 0xC0	� 
		0xA0,	// �
		0x42,	// �
		0xA1,	// �
		0xE0,	// �
		0x45,	// �
		0xA3,	// 0��6 �
		0xA4,	// �
		0xA5,	// �
		0xA6,	// �
		0x4B,	// �
		0xA7,	// �
		0x4D,	// �
		0x48,	// �
		0x4F,	// �
		0xA8,	// �
		0x50,	// �			
		0x43,	// �			
		0x54,	// �			
		0xA9,	// �			
		0xAA,	// �	
		0x58,	// �			
		0xE1,	// �
		0xAB,	// �			
		0xAC,	// �								
		0xE2,	// �			
		0xAD,	// �
		0xAE,	// �
		0x62,	// �			
		0xAF,	// �			
		0xB0,	// �			
		0xB1,	// �			

		0x61,	// �	
		0xB2,	// �
		0xB3,	// �
		0xB4,	// �
		0xE3,	// �
		0x65,	// �
		0xB6,	// �
		0xB7,	// �
		0xB8,	// �
		0xB9,	// �
		0xBA,	// �
		0xBB,	// �
		0xBC,	// �
		0xBD,	// �
		0x6F,	// o
		0xBE,	// �
		0x70,	// �
		0x63,	// �
		0xBF,	// �
		0x79,	// �
		0xE4,	// �
		0x78,	// �
		0xE5,	// �
		0xC0,	// �
		0xC1,	// �
		0xE6,	// �
		0xC2,	// �
		0xC3,	// �
		0xC4,	// �
		0xC5,	// �
		0xC6,	// �
		0xC7,	// �
};

// ----------------------------- Constructor -----------------------------------
WH1602B::WH1602B()
{
	display_mode = 1;
}

// ---------------------------- Initialization ---------------------------------
void WH1602B::InitLCD(uint8_t mode)
{
	display_mode = mode;
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;						// IO port E clock enabled
	
	if(mode)
	{
		// PE0 - Data 0
		GPIOE->OTYPER &= ~GPIO_OTYPER_OT0;						// Push-pull mode
		GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED0_0;			// Speed 25 MHz
		GPIOE->PUPDR &= ~ GPIO_PUPDR_PUPD0_Msk;				// NO pull-up, pull-down
		GPIOE->MODER |= GPIO_MODER_MODER0_0;					// Output mode

		// PE1  - Data 1
		GPIOE->OTYPER &= ~GPIO_OTYPER_OT1;						// Push-pull mode
		GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED1_0;			// Speed 25 MHz
		GPIOE->PUPDR &= ~ GPIO_PUPDR_PUPD1_Msk;				// NO pull-up, pull-down
		GPIOE->MODER |= GPIO_MODER_MODER1_0;					// Output mode
		
		// PE2 - Data 2
		GPIOE->OTYPER &= ~GPIO_OTYPER_OT2;						// Push-pull mode
		GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED2_0;			// Speed 25 MHz
		GPIOE->PUPDR &= ~ GPIO_PUPDR_PUPD2_Msk;				// NO pull-up, pull-down
		GPIOE->MODER |= GPIO_MODER_MODER2_0;					// Output mode

		// PE3 - Data 3
		GPIOE->OTYPER &= ~GPIO_OTYPER_OT3;						// Push-pull mode
		GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_0;			// Speed 25 MHz
		GPIOE->PUPDR &= ~ GPIO_PUPDR_PUPD3_Msk;				// NO pull-up, pull-down
		GPIOE->MODER |= GPIO_MODER_MODER3_0;					// Output mode
	}
	
	// PE4 - Data 4
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT4;						// Push-pull mode
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED4_0;			// Speed 25 MHz
	GPIOE->PUPDR &= ~ GPIO_PUPDR_PUPD4_Msk;				// NO pull-up, pull-down
	GPIOE->MODER |= GPIO_MODER_MODER4_0;					// Output mode
	
	// PE5 - Data 5
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT5;						// Push-pull mode
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_0;			// Speed 25 MHz
	GPIOE->PUPDR &= ~ GPIO_PUPDR_PUPD5_Msk;				// NO pull-up, pull-down
	GPIOE->MODER |= GPIO_MODER_MODER5_0;					// Output mode
	
	// PE6 - Data 6
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT6;						// Push-pull mode
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED6_0;			// Speed 25 MHz
	GPIOE->PUPDR &= ~ GPIO_PUPDR_PUPD6_Msk;				// NO pull-up, pull-down
	GPIOE->MODER |= GPIO_MODER_MODER6_0;					// Output mode
	
	// PE7 - Data 7
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT7;						// Push-pull mode
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED7_0;			// Speed 25 MHz
	GPIOE->PUPDR &= ~ GPIO_PUPDR_PUPD7_Msk;				// NO pull-up, pull-down
	GPIOE->MODER |= GPIO_MODER_MODER7_0;					// Output mode
	
  // PE8 - Register select RS
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT8;						// Push-pull mode
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED8_0;			// Speed 25 MHz
	GPIOE->PUPDR &= ~ GPIO_PUPDR_PUPD8_Msk;				// NO pull-up, pull-down
	GPIOE->MODER |= GPIO_MODER_MODER8_0;					// Output mode
	
	// PE9 - Read/nWrite RW
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT9;						// Push-pull mode
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED9_0;			// Speed 25 MHz
	GPIOE->PUPDR &= ~ GPIO_PUPDR_PUPD9_Msk;				// NO pull-up, pull-down
	GPIOE->MODER |= GPIO_MODER_MODER9_0;					// Output mode
	
	// PE10 - Enable E
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT10;						// Push-pull mode
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED10_0;		// Speed 25 MHz
	GPIOE->PUPDR &= ~ GPIO_PUPDR_PUPD10_Msk;			// NO pull-up, pull-down
	GPIOE->MODER |= GPIO_MODER_MODER10_0;					// Output mode

	// Process, to initialize LCD is discribed in documentation
	Tim2DelayMs(30);															// Time Delay after power on
	if(display_mode)
	{
		for(uint8_t n = 0; n < 3; n++)
		{
			Write(0x30, CMD);
			Tim2DelayMs(5);
		}
		Write(0x3C, CMD);																// 0x3C = 00111100, 8 bit, 2 row, font 5�11
		Write(0x01, CMD);																// 0x01 = 00000001, Clear display
		Write(0x06, CMD);																// 0x06 = 00000110, Address increment, display isn't move
		Write(0x0E, CMD);																// 0x0E = 00001110, Dispplay on, cursor on, cursor blinking off
	}
	else
	{
		Write(0x33, CMD);
		Write(0x32, CMD);
		Write(0x2C, CMD);																// 0x2C = 00111100, 8 bit, 2 row, font 5�11
		Write(0x01, CMD);																// 0x01 = 00000001, Clear display
		Write(0x06, CMD);																// 0x06 = 00000110, Address increment, display isn't move
		Write(0x0E, CMD);																// 0x0E = 00001110, Dispplay on, cursor on, cursor blinking off
	}
}

// ------------------------ Clear display ----------------------------------
void WH1602B::ClearLCD()
{
	
	Write(0x01, CMD);
	Tim2DelayMs(2);
}

// ----------------------- Wait till LCD is ready ---------------------------
uint8_t WH1602B::WaitLCD()
{
	// DB7 (PE7) - busy flag
	GPIOE->MODER &= ~GPIO_MODER_MODER7;					 	// Input mode
	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR7_0;					// Pull-up
	
	RS_PIN(0);
	RW_PIN(1);
	E_PIN(1);
	Tim14DelayUs(450);
	E_PIN(0);
	
	
	uint8_t counter = 0;
	while(!(GPIOE->IDR & GPIO_IDR_ID7))
	{
		Tim14DelayUs(500);
		counter++;
		if(counter == 10) { break; }
	}
	
	GPIOE->MODER |= GPIO_MODER_MODER7_0;				 	// Input mode
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR7;						// NO Pull-up, no pull-down			
	
	if(counter == 10) { return 1; }
	return 0;
}

// ----------------------- Cursor position ------------------------------
//				col 1 ..................................... col 16
// row 0   00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
// row 1	 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F

void WH1602B::SetPosition(uint8_t row, uint8_t column)
{
	if(row > 1) {row = 1; }
	if(column > 16) {column = 16; } 
	Write((uint8_t) (0x80 | (row > 0 ? 0x40 : 0) | column), CMD);
	Tim14DelayUs(40);
}

// ------------------------ Print string ---------------------------------
void WH1602B::WriteString(const uint8_t *str)
{
	uint8_t symbol;
	uint8_t ptr = 0;
	while (str[ptr] != 0)
	{
		symbol = str[ptr++];
		if(symbol > 0xBF)
		{
			symbol = RUSSIAN[(symbol-0xC0)];
		}
		Write(symbol, DATA);	
	}
}

// -------------------- Write command or data ----------------------------
uint8_t WH1602B::Write(uint8_t data, uint8_t data_type)
{
	if(WaitLCD()) { return 1; }
	if(data_type == CMD) 
	{	
		RS_PIN(0);								// 0 - command
		RW_PIN(0);								// 0 - write
	}
	else
	{
		RS_PIN(1);								// 1 - data
		RW_PIN(0);								// 0 - write
	}
	
	if(display_mode)
	{
		SetPort(data);
		E_PIN(1);
		Tim14DelayUs(45);
		E_PIN(0);
	}
	else
	{
		uint8_t one_half = data & 0x0F;
		uint8_t two_half = (data & 0xF0) >> 4;
		
		SetPort(two_half);
		E_PIN(1);
		Tim14DelayUs(100);
		E_PIN(0);
		
		SetPort(one_half);
		E_PIN(1);
		Tim14DelayUs(100);
		E_PIN(0);
	}
	return 0;
}

// ---------------------- Set port state ---------------------------------
void WH1602B::SetPort(uint8_t state)
{
	uint16_t old_state = GPIOE->ODR;
	
	if(display_mode) { GPIOE->ODR = (state | (old_state & 0xFF00)); }
	else { GPIOE->ODR = ((state << 4) | (old_state & 0xFF0F)); }
}

// ------------------ Set/reset pin RS (PIN PE8) --------------------------
void WH1602B::RS_PIN(uint8_t state)
{
	if(state) { GPIOE->BSRR |= GPIO_BSRR_BS_8; }
	else { GPIOE->BSRR |= GPIO_BSRR_BR_8;	}
}

// ------------------ Set/reset pin RW (PIN PE9) ---------------------------
void WH1602B::RW_PIN(uint8_t state)
{
	if(state) { GPIOE->BSRR |= GPIO_BSRR_BS_9; }
	else { GPIOE->BSRR |= GPIO_BSRR_BR_9;	}
}

// ------------------ Set/reset pin E (PIN PE10) ---------------------------
void WH1602B::E_PIN(uint8_t state)
{
	if(state) { GPIOE->BSRR |= GPIO_BSRR_BS_10; }
	else { GPIOE->BSRR |= GPIO_BSRR_BR_10;	}
}









