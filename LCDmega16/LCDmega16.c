
#ifndef F_CPU
#define F_CPU 8000000UL // 16 MHz clock speed
#endif

#define FOSC 8000000//1843200// Clock Speed
#define BAUD 9600//115200//9600
#define MYUBRR FOSC/16/BAUD-1

#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC5
#define EN eS_PORTC7

#include <avr/io.h>
#include <avr/iom16.h>
#include <string.h>
#include <stdio.h>
//#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/wdt.h>
#include <stdlib.h>
#include "lcd.h"

void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );

int main(void)
{
	DDRD = 0b11111000;
	DDRC = 0xFF;
	//DDRA = 0b00000111; // switches set (select, up, down, tag)
	
	USART_Init ( MYUBRR );
	Lcd4_Init();
	
	//PORTA |= ( 1<<PA7 );//SELECT// set to 1
	//PORTA |= ( 1<<PA6 );//DOWN
	//PORTA |= ( 1<<PA5 );//UP
	//PORTA |= ( 1<<PA4 );// PIN ANTENA ENABLE
	
	_delay_ms(1000);
	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("Warehouse Soft.");
	Lcd4_Set_Cursor(2,0);
	Lcd4_Write_String("Initializing...");
	
	_delay_ms(2000);
	
	
	while(1)
	{
		
	}
}

void USART_Init( unsigned int ubrr)
{
	UBRRH = (unsigned char)(ubrr>>8);       // Set baud rate
	UBRRL = (unsigned char)ubrr;            // Set baud rate
	UCSRB = (1<<RXEN)|(1<<TXEN);            // Enable receiver and transmitter
	UCSRC = (1<<URSEL)|(0<<USBS)|(3<<UCSZ0);// Set frame format: 8data, 2stop bit
}

void USART_Transmit( unsigned char data )
{
	while ( !( UCSRA & (1<<UDRE)) );        // Wait for empty transmit buffer
	UDR = data;                             // Put data into buffer, sends the data
}

unsigned char USART_Receive( void )
{
	while ( !(UCSRA & (1<<RXC)) );          // Wait for data to be received
	return UDR;                             // Get and return received data from buffer
}


			