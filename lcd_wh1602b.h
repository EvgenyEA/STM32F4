// C++ class to drive WH1602B-YGK-CTK
#include "header.h"

//******************************************************************************
// Display connection

// GND  1
// +5V  2
// Vo   3													Contrast Adjust
// RS   4						PE8						Register select 			0 - command, 1 - data
// RW   5						PE9						Read/ nWrite signal 	0 - write, 1 - read
// E    6						PE10				  Enable Signal					1 - enable
// DB0  7						PE0						Data 0
// DB1  8						PE1						Data 1
// DB2  9						PE2						Data 2
// DB3  10					PE3						Data 3
// DB4  11					PE4						Data 4
// DB5  12					PE5						Data 5
// DB6  13					PE6						Data 6
// DB7  14					PE7						Data 7
// +4.2 15 LED
// k 16 16


class WH1602B
{
	public:
		WH1602B();
		void InitLCD(uint8_t mode);
		void ClearLCD();
		void SetPosition(uint8_t row, uint8_t column);
		void WriteString(const unsigned char *str); 
	
	private:
		uint8_t Write(uint8_t data, uint8_t data_type);					// data_type - command or in informatin to display
		void SetPort(uint8_t);
		void RS_PIN(uint8_t state);
		void RW_PIN(uint8_t state);
		void E_PIN(uint8_t state);
		uint8_t WaitLCD();
	
		uint8_t display_mode;																		// 0 - 4 wire, 1 - 8 wire	
	  static uint8_t RUSSIAN[64];
	
		static const uint8_t CMD = 0x00;
		static const uint8_t DATA = 0x01;
};

extern WH1602B LCD;

