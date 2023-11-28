// Derivation of initial counter value:

// XTAL = 16MHz → Txtal _clock = 1µs/16
// Prescaler = 1:256 → Tcounter_clock = 256 × 1/16µs = 16 µs
// Counter increments needed = 2000µs / 16µs = 125 increments
// Initial counter value = 1+255 – 125 = 131

#include <avr/io.h>

void delay_fun()
{

    TCNT0 = 131; // Initial value

    TCCR0A = 0x00; //  start in normal mode. Timer counter control register
    TCCR0B = 0x04;

    while ((TIFR0 & 0x01) == 0);

    TCCR0A = 0x00;
    TCCR0B = 0X00;

    TIFR0 = 0x01; // set the TOv0 bit to 1 for next round.
}

int main(void)
{
    DDRB |= (1 << 5);

    while (1){
	    PORTB ^= (1 << 5); 

        // calculating time of 500ms from 2ms
        for(int i = 0; i < 250; i++){
            delay_fun();		
        }  
    }
}
