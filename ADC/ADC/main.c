/*
 * ADC.c
 *
 * Created: 06.06.2024 13:34:07
 * Author : Samuel Peer
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "oled_ssd1306.h"

int ADC_VALUE;

void ADC_INIT()
{
	ADMUX	|= ((1<<MUX1)	|  (1<<MUX2));					//use ADC6
	ADMUX	|= (1<<REFS0);									//Referenzspannung AVCC
	ADCSRA  |= ((1<<ADPS0)  |  (1<<ADPS1)	|  (1<<ADPS2)); //Prescaler 128 --> Zeitdiskretisierung
	ADCSRA  |= (1<<ADEN);									//Enable --> ADC einschalten
	ADCSRA  |= (1<<ADSC);									//Start single conversion
	
	while(ADCSRA & (1<<ADSC)) {};							//trash 1st value
}

void GET_ADC_DATA()
{
	ADCSRA  |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC)) {};
	ADC_VALUE = ADCW;
	ADC_VALUE = ADC_VALUE/10;
	ADC_VALUE = 100-ADC_VALUE;
	if(ADC_VALUE<=9)					{oled_gotoxy(5,3);oled_write("   ");}
	if((ADC_VALUE>9) && (ADC_VALUE<=99))	{oled_gotoxy(5,3);oled_write("  ");}
	if(ADC_VALUE==100)					{oled_gotoxy(5,3);}	
	oled_write("2%i",ADC_VALUE);
	
	
}
int main(void)
{
	
	ADC_INIT();
	oled_init();
	oled_gotoxy(2,0);
	oled_write("Potentiometer");
	
	
   
    while (1) 
    {
		GET_ADC_DATA();
    }
}

