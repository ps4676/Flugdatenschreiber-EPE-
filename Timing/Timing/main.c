/*
 * Timing.c
 *
 * Created: 06.06.2024 15:11:46
 * Author : Samuel Peer
 */ 
//Das Programm zählt eine gewisse Zeit von 0 ausgehend nach oben, wirft einen Interrupt und setzt den Timer zurück.
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "oled_ssd1306.h"

volatile int m_second = 0; //für Timervariablen die in der ISR verwendet werden sollen --> Volatile

void TIMER_2_INIT()
{
	TCCR2A		|=	(1<<WGM21);		//Wave form generation mode 21 = CTC (clear timer compare match)
	TCCR2B		|=	(1<<CS22);		//CS = Clock select --> prescaler = 64
	TIMSK2		|=	(1<<OCIE2A);	//Interrupt Enable
	OCR2A		=	250;			//CTC value für 1kHz --> 16MHz/64 = 250kHz --> 250kHz/250 = 1kHz
	
	
}

ISR(TIMER2_COMPA_vect)
{
	m_second += 1;
	
	
}
int main(void)
{
	oled_init();
	TIMER_2_INIT();
	oled_write("Hallo");
	
	sei();//Set global interrupt, sonst funktioniert keiner der Interrupts!
	
	
    /* Replace with your application code */
    while (1) 
    {
		//if(!PIND&(1<<3))
		//{
		if (m_second>=1000) {m_second = 0;}
		oled_gotoxy(0,0);
		oled_write("%3i",m_second);
    }
	//}
}

