/*
 * XC8Application1.c
 *
 * Created: 31.05.2024 14:01:23
 * Author : Samuel Peer
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "oled_ssd1306.h"
#include <avr/interrupt.h>

void PWM_G_INIT()
{
	TCCR0A |=((1<<WGM00)  | (1<<WGM01)); 
	TCCR0A |=((1<<COM0A0) | (1<<COM0A1));
	TCCR0B |=((1<<CS00)	  | (1<<CS02)); 
	OCR0A = 0;
}
void PWM_R_INIT()
{
	TCCR0A |=((1<<COM0B0)  | (1<<COM0B1));
	OCR0B = 0;
}

void PWM_B_INIT()
{
	TCCR1A |=(1<<WGM10);//WGM = Waveform Generator Mode Fast PWM 8 Bit Modus
	TCCR1B |=(1<<WGM12);
	TCCR1A |=((1<<COM1A0)  | (1<<COM1A1)); //inverting mode - common anode
	TCCR1B |=((1<<CS10)  | (1<<CS12));
	OCR1A = 0;
}

int main(void)
{
	DDRD|=(1<<5); //R
	DDRD|=(1<<6); //G
	DDRB|=(1<<1); //B
	
	PWM_G_INIT();
	PWM_R_INIT();
	PWM_B_INIT();
	
	oled_init();
	oled_font_size(2);
	oled_gotoxy(0,1);
	oled_write("Hello");
	oled_gotoxy(0,6);
	oled_write("World_");
	sei(); //Set interrupts -- globales Flag, damit die interrupts enabled werden --> cli = "clear all interrups"
	OCR0A = 0; //Helligkeit der jeweiligen LED 0 ist LOW und 255 ist HIGH
	OCR0B = 255;
	OCR1A = 22; 
    /* Replace with your application code */
    while (1) 
    {
		PORTD|=(1<<5);
		_delay_ms(500);
		PORTD &= ~(1<<5);
		_delay_ms(500);
    }
}

