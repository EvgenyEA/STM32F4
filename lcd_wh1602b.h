// Класс управления жидкокристаллическим индикатором WH1602B-YGK-CTK
#include "header.h"

// Общая процедура работы с дисплеем:
// На пины RS, R/W, DB7 – DB0 – нужные сигналы, соответствующие нашей команде.
// Подаем единицу на вывод E.
// Ожидание (по даташиту – не менее 150 нс)
// Подаем на вывод E низкий уровень (0).
//******************************************************************************
// Подключение дисплея
// DB0  = PE0 
// DB1  = PE1
// DB2  = PE2
// DB3  = PE3
// DB4  = PE4
// DB5  = PE5
// DB6  = PE6
// DB7  = PE7
/*******************************************************************************/
// Распиновка дисплея
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
		void WriteString(const unsigned char *str); 					// вывод текста в положение курсора 
		
	
	private:
		uint8_t Write(uint8_t data, uint8_t data_type);	// data - данные для записи, data_type - команда или информация на дисплей
		void SetPort(uint8_t);
		void RS_PIN(uint8_t state);
		void RW_PIN(uint8_t state);
		void E_PIN(uint8_t state);
		uint8_t WaitLCD();
	
		uint8_t display_mode;																				// 0 - четырехпроводный, 1 - восьмипроводный интерфейс	
	  static uint8_t RUSSIAN[64];
	
		static const uint8_t CMD = 0x00;
		static const uint8_t DATA = 0x01;
};

extern WH1602B LCD;

