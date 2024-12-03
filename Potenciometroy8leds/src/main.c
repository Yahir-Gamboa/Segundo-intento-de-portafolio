#include <avr/io.h> 
// #define RTHRES 500 esto no se ocupa
//#define POT 500 lo quitamos para poder darle valor que queramos abajo jijijio  
void adc_init()
{
    ADMUX = (1<<REFS0);
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
 uint16_t adc_read(uint8_t ch)
 {
    ch &= 0b00000111;
    ADMUX = (ADMUX & 0b11111000)|ch; 
    ADCSRA |= (1<<ADSC); 
    while(ADCSRA & (1<<ADSC));
    return (ADC);
 }
 int main()
 {
    
    uint16_t avalue;
    DDRB = 0xFF; //led en PB0 
    adc_init(); // incia adc  
    
    while(1)
    {
      avalue = adc_read(0); // lle adc y lo guarda 
      
      // como dijo alejandro 
        if (avalue < 128) PORTB = 0b00000001; // PRIMER LED
        else if (avalue < 256) PORTB = 0b00000011; // SEGUNDO LED
        else if (avalue < 384) PORTB = 0b00000111; // TERCER LED
        else if (avalue < 512) PORTB = 0b00001111; // CUARTO LED
        else if (avalue < 640) PORTB = 0b00011111; // QUINTO LED
        else if (avalue < 768) PORTB = 0b00111111; // SEXTO LED
        else if (avalue < 896) PORTB = 0b01111111; // SEPTIMO LED
        else if (avalue <=983) PORTB = 0b11111111; // OCTAVO LED

        
    }
 }